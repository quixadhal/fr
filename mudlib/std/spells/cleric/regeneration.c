
#include "tweaks.h"
/*** Regeneration ***/
/*** Created by Wonderflug ***/
 

#define SP_NAME "Regeneration"
#define SPELLTYPE "defensive"      
#define TYPE "magical"
#define save_type "spells"
#define GP REGEN_GP
#define LEVEL REGEN_LEVEL
#define LOCKOUT "cast"
#define REGEN_OBJ "/std/spells/cleric/regeneration_obj.c"

string help() 
{
  return
        "\n\n"+
        "Spell Name: "+SP_NAME+"\n"+
        "Sphere: Healing\n"+
        "Level: "+LEVEL+"\n"+
        "Gp Cost: "+GP+"\n"+
        "Description: \n"+
	"  This spell makes the recipient recover from wounds much much "+
	"faster.  Poisoned or other special wounds cannot be regenerated "+
	"by this spell.  The spell will last for "+REGEN_DURATION_LEVEL+
	" rounds per level of the caster.  \n"+
	"  Overuse of this spell has known to be permanently damaging.  "+
	"Much like trolls born with the ability to regenerate innate, "+
	"the recipient will become very susceptible to attacks from fire. "+
	"Even once the spell has worn off, it is believed some residue is "+
	"left over.  One notable archmage who used the spell regularly was "+
	"known, after several years' use, to actually catch fire from "+
	"the smallest campfire sparks.\n";
        "\n";
}


int cast_spell(string str, object caster)
{
  object my_caster;
  object* obs;
  object target;

  if (caster)
	my_caster = caster;
  else my_caster = this_player();
  
  if((my_caster->query_timed_property(LOCKOUT)) || 
	((int)my_caster->query_level()< 2*LEVEL) )
  {
       tell_object(my_caster,"You are already casting a spell.\n");
       return 1;
  }
  if( (int)my_caster->query_gp() < GP )
  { 
       tell_object(my_caster, "You are too mentally drained to cast.\n");
       return 1;
  }

  obs = (object*)find_match( str, environment(my_caster));
  if (sizeof(obs) < 1)
  {
	tell_object(my_caster, "Your target is not here.\n");
	return 1;
  }
  target = obs[0];
  if ( target->query_armour_spell() || target->query_mirror_spell() ||
	target->query_property("regen_on") )
  {
	tell_object(my_caster, "Magic surrounding your target disrupts "+
	  "your spell.\n");
	return 1;
  }

  tell_object(my_caster,"You start to cast "+SP_NAME+".\n\n");
  tell_room(environment(my_caster),(string)my_caster->query_cap_name()+
	" starts to cast a spell.\n", my_caster);

  my_caster->adjust_gp(-GP);
  my_caster->add_timed_property(LOCKOUT,1,3);
  call_out("make_spell",1,my_caster,target);   
  return 1;
}

int cast(string str)
{
   return(cast_spell(str,this_player()) );
}

void make_spell(object caster, object target)
{
  object ob;

  tell_object(caster, "You chant, 'in mani timus'.\n\n");
  tell_room(environment(caster),(string)caster->query_cap_name()+
	" chants, 'in mani timus'.\n\n", ({ caster }));

  ob = clone_object(REGEN_OBJ);
  ob->set_spell(target, (int)caster->query_level()/REGEN_AMOUNT_LEVEL);
  ob->set_get();
  ob->move(target);
  ob->reset_get();
  ob->reset_drop();
  target->add_extra_look(ob);
  target->add_timed_property("regen_on",1,(int)caster->query_level()*
				REGEN_DURATION_LEVEL);

/* Fire resistance hit.  Every three times it drops 1% */
  if ( (int)target->query_property("regen_fire_counter") == 2 )
  {
	target->add_property("fire",(int)target->query_property("fire")-1);
	target->add_property("regen_fire_counter", 0);
	tell_object(target, "You feel more susceptible to fire.\n");
  }
  else target->add_property("regen_fire_counter", 
	  (int)target->query_property("regen_fire_counter") + 1 );

  tell_room(environment(caster),caster->query_cap_name()+" completes the "+
	"spell and "+target->query_cap_name()+"'s skin starts to glow \nwith "+
	"health.\n",
	({ caster, target }) );
  tell_object(caster,"You cast Regeneration at "+target->query_cap_name()+", "+
	"and "+target->query_possessive()+" skin glows with health.\n");
  tell_object(target,caster->query_cap_name()+" completes the spell, "+
	"and you feel health flow through \nyou, and your skin starts to "+
	"glow.\n");
}
