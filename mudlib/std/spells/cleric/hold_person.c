
#include "tweaks.h"

#define HOLD_SHADOW "/std/spells/cleric/hold_person_sh.c"

#define SP_NAME "Hold Person"
#define GP_COST HOLD_COST
#define ALREADY_CASTING "cast"
#define save_type "spells"

inherit "/std/spells/patch.c";
object shadow;

void make_spell(object caster, object target, int duration);

string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "Saving Throw: Level\n"+
       "Level: 5th\n"+
       "Gp Cost: "+GP_COST+"\n\n"+
       "Description: \n"+
	"  This spell wraps the target in invisible bonds, preventing "+
	"them from attacking.  The spell lasts one round per three levels of "+
	"the caster.  Clerics of Lolth get 1.5 times the duration."+
	"Strong targets will be able to struggle away slowly.\n\n";
}

int cast_spell(string str, object caster)
{
  int cost;
  int new_count;
  int duration, level, duration_bon;
  int i;
  object target, my_caster;

  str = (string)this_player()->expand_nickname(str);

  if (caster)
	my_caster = caster;
  else 
  {
	my_caster = this_player();
	str = (string)my_caster->expand_nickname(str);
  }


  if (my_caster->query_timed_property(ALREADY_CASTING))
  {
	tell_object(my_caster,"You are already casting a spell.\n");
	return 1;
  }
  if ((int)my_caster->query_gp() < GP_COST )
  {
	tell_object(my_caster,"You are too mentally drained to cast "+
	  "this spell.\n");
	return 1;
  }
  if ( str == (string)my_caster->query_name() )
	tell_object(my_caster,"Holding yourself?  Takes all sorts I "+
	  "guess.\n");

  level = (int)my_caster->query_level();

  duration_bon = 0;
  if ( (string)my_caster->query_guild_name() == "Lolth" )
  {
	duration_bon = level*HOLD_DURATION_BONUS;
	cost = GP_COST/2;
  }
  else cost = GP_COST;

  duration = duration_bon + (level*HOLD_DURATION_LEVEL);

  tell_object(my_caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(my_caster), my_caster->query_cap_name()+
	" begins to cast a spell.\n",
     	my_caster);

  my_caster->add_timed_property(ALREADY_CASTING,3,1);
  my_caster->adjust_gp(-cost);
  call_out("make_spell",3,my_caster,str,duration);
  return 1;
}

void make_spell( object caster, object str, int duration )
{
  object* ob;
  object target;
  int j;
  int check;

  ob = find_match(str, environment(caster));
  if (!sizeof(ob))
  {
        tell_object(caster, "There is nobody of that name here.\n");
        return 1;
  }
  target = ob[0];

/* We'll just dispell EITHER time spell with this. */
  if ( target->query_time_spell() )
  {
	target->dispell_time_spell();
	return 1;
  }

/* Can't hold twice. */
  if ( target->query_hold_spell() || target->query_pacify_spell() )
  {
        tell_object(caster,"Your target is already incapacitated.\n");
        return 1;
  }

/* Saving throw */
/* This should be tweaked a lot prolly. */
  check = random(15) - 5;
  if ( check + (int)target->query_level() > (int)caster->query_level() + 10 )
  {
	tell_object(caster, target->query_cap_name()+" resists the effects "+
	  "of your spell!\n");
	tell_object(target, "You resist the effects of the spell!\n");
	tell_room(environment(caster), target->query_cap_name()+" resists "+
	  "effects of the spell.\n", ({ caster, target }) );
	return 1;
  }

  tell_room(environment(caster), caster->query_cap_name()+
	" chants, 'amri xeno haltem'.\n", 
	caster);
  tell_object(caster, "You chant, 'amri xeno haltem'.\n\nYou wrap "+
	target->query_cap_name()+" in bonds of invisible force.\n");
  tell_object(target, "You feel invisible bonds surround you, stopping "+
	"your every movement.\n"); 
  tell_room(environment(caster), caster->query_cap_name()+
      " finishes a spell with a gesture at "+target->query_cap_name()+
      ", and "+target->query_pronoun()+" starts \nto struggle against "+
      "invisible bonds.\n",
      ({ caster, target}) ); 

  j = cleric_fix_damage(caster, target, duration, "magical");
  target->add_timed_property("hold_person_on", 1, j);
  target->add_timed_property("nocast",1, j);
  target->add_timed_property("noguild",1,j);
  
  shadow = clone_object(HOLD_SHADOW);
  shadow->setup_shadow(target); 
  target->add_extra_look(shadow);

  return GP_COST;
}

