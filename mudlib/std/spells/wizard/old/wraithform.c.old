
#include "tweaks.h"

#define SP_NAME "Wraithform"
#define GP_COST WRAITHFORM_GP_COST
#define ALREADY_CASTING "cast"
#define save_type "spells"
#define WRAITH_OVERUSE_PROPERTY "wraith_overuse"

/* (level+int)*this compared against the current value: fail = killed */
#define WRAITH_OVERUSE_CHECK 3
/* this - caster's int  is the increase in wraith_overuse per casting */
#define WRAITH_OVERUSE_ADJ_MAX 50
/* multiple of normal duration that the overuse property lasts for */
#define WRAITH_OVERUSE_DURATION 5
/* base+(level*caster's level) is the duration, necro's get add'l level*bonus */


object shadow;

void make_spell(object caster);

string help() {
       return
       "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "School: Necromancy\n"
       "Level: 3rd\n"
       "Gp Cost: "+GP_COST+"\n"
       "Description: \n"
	"  This spell vapourises your mortal form, making you into nothing "
	"more than a vapourous cloud.  Only your body is transformed, so "
	"all of your equipment is dropped behind.  Of course, vapour cannot "
	"be attacked, neither by spell, nor by blade, and vapour is also "
	"harmless itself.  The cloud itself resembles a pale human outline, "
	"and hence the name, Wraithform.\n"
	"  The duration increases with level, but beware of using this "
	"spell too often, for it is said that those who do end up wraiths "
	"themselves, for eternity..\n\n";
}

int cast_spell(string str, object caster)
{
  int cost;
  int new_count;
  int duration, level, duration_bon;
  int i;
  object my_caster;
  object wraith;
  object* ob;

  str = (string)this_player()->expand_nickname(str);

  if (caster)
	my_caster = caster;
  else my_caster = this_player();

  if (my_caster->query_timed_property(ALREADY_CASTING))
  {
	write("You are already casting a spell.\n");
	return 1;
  }
  if ((int)my_caster->query_gp() < GP_COST )
  {
	write("You are too mentally drained to cast this spell.\n");
	return 1;
  }
  if ( str != (string)my_caster->query_name() )
  {
	write("You may only cast this spell on yourself.\n");
	return 1;
  }
  if ( my_caster->query_wraith_spell() )
  {
	write("You are already vapour!  What more do you want??\n");
	return 1;
  }
  level = (int)my_caster->query_level();
  new_count = (int)my_caster->query_timed_property(WRAITH_OVERUSE_PROPERTY);

  if ( new_count > (level+(int)my_caster->query_int())*WRAITH_OVERUSE_CHECK)
  {
	write("You start to cast the spell, but immediately you realize "
	  "something is going horribly, utterly wrong.  The magic goes out "
	  "of control, and you feel your life force disintegrate as "
	  "surely as your body disintegrates into a cloud of mist.  An "
	  "evil presence fills the wraith-like cloud your body has become, "
	  "consuming the last of your life essence.\n\nYou die.\n");
	tell_room(environment(my_caster),
	  " starts to cast a spell, then screams horribly as his body "
	  "dissapates into a shadowy cloud of mist, leaving just a ghost "
	  "behind.  Two glowing red eyes appear in the cloud, and the "
	  "cloud takes on form, until you realize a wraith has been born.\n",
	  my_caster);
	wraith = clone_object(WRAITH_MONSTER);
	wraith->move(environment(my_caster));
	ob = all_inventory(my_caster);
	wraith->give_caster_stats(my_caster);
	for (i=0;i<sizeof(ob);i++)
		ob[i]->move(wraith);
	wraith->init_equip();
	my_caster->remove_timed_property(WRAITH_OVERUSE_PROPERTY);
	my_caster->do_death();
	return 1;
  }

  new_count += WRAITH_OVERUSE_ADJ_MAX - (int)my_caster->query_int();

  duration_bon = 0;
  if ( (string)my_caster->query_guild_name() == "necromancer" )
  {
	if (level < 15)
	{
		write("You are too low-level to cast this spell.\n");
		return 1;
	}
	duration_bon = level*WRAITH_DURATION_BONUS;
	cost = GP_COST/2;
  }
  else 
  {
	if (level < 20)
	{
		write("You are too low-level to cast this spell.\n");
		return 1;
	}
	cost = GP_COST;
  }
  duration = duration_bon + 
	WRAITH_DURATION_BASE+(level*WRAITH_DURATION_LEVEL);

  write("You start to cast "+SP_NAME+".\n");
  say(my_caster->query_cap_name()+" begins to cast a spell.\n",
     previous_object());

  my_caster->add_timed_property(ALREADY_CASTING,3,1);
  my_caster->add_timed_property(WRAITH_PROPERTY, 1, duration);
  my_caster->add_timed_property(WRAITH_OVERUSE_PROPERTY,
	new_count, duration*WRAITH_OVERUSE_DURATION);
  my_caster->add_static_property("dead",1);
  my_caster->adjust_gp(-cost);
  call_out("make_spell",1,my_caster);
  return 1;
}

void make_spell( object caster )
{
  object* ob;
  int j;

  say((string)caster->query_cap_name()+
	" chants, 'corpus formis vaporis'.\n", 
	caster);
    
  tell_object(caster, "You chant, 'corpus formis vaporis'.\n");
  tell_object(caster, "Your body dissolves into vapour, your equipment "
	"falling in a clutter to the ground, and you assume the form of a "
	"wraith.\n"); 
  say((string)caster->query_cap_name()+
      " finishes a spell and dissolves into a cloud of vapour, equipment"
      " falling in a clutter to the ground.  A wraithlike shadow moves "
      "off from where "+(string)caster->query_cap_name()+
      " was.\n",caster); 

  ob = all_inventory(caster);
  for (j=0;j<sizeof(ob);j++)
	caster->drop_ob(ob[j]->query_name());
  
  shadow = clone_object(WRAITH_SHADOW);
  shadow->setup_shadow(caster); 
  caster->add_extra_look(shadow);

  return GP_COST;
}

