
#include "tweaks.h"
/*** Withering ***/
/*** Created by Wonderflug ***/
 

#define SP_NAME "Withering"
#define SPELLTYPE "offensive"      
#define TYPE "magical"
#define save_type "spells"
#define GP WITHER_GP
#define LEVEL WITHER_LEVEL
#define LOCKOUT "cast"
#define WITHER_OBJ "/std/spells/cleric/withering_obj.c"

string help() 
{
  return
        "\n\n"+
        "Spell Name: "+SP_NAME+"\n"+
        "Sphere: Necromancy\n"+
        "Level: "+LEVEL+"\n"+
        "Gp Cost: "+GP+"\n"+
        "Description: \n"+
	"  This spell makes the recipient very susceptible to small wounds "+
	"and bruises.  Cuts and other minor wounds will appear periodically "+
	"by this spell.  In addition, the target will be weakened somewhat. "+
	"The spell will last for "+WITHER_DURATION_LEVEL+
	" rounds per level of the caster.  \n"+
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
  if ( target->query_property("wither_on") )
  {
	tell_object(my_caster, "Your target is already withering away.\n");
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

  tell_object(caster, "You chant, 'xo harmi timus'.\n\n");
  tell_room(environment(caster),(string)caster->query_cap_name()+
	" chants, 'xo harmi timus'.\n\n", ({ caster }));

  ob = clone_object(WITHER_OBJ);
  ob->set_spell(target, (int)caster->query_level()/WITHER_AMOUNT_LEVEL);
  ob->set_get();
  ob->move(target);
  ob->reset_get();
  ob->reset_drop();
  target->add_extra_look(ob);
  target->add_timed_property("wither_on",1,(int)caster->query_level()*
				WITHER_DURATION_LEVEL);
  target->adjust_temp_str(-3);
  tell_room(environment(caster),caster->query_cap_name()+" completes the "+
	"spell and "+target->query_cap_name()+"'s skin starts to grow \n "+
	"sickly, decaying slowly.\n",
	({ caster, target }) );
  tell_object(caster,"You cast Withering at "+target->query_cap_name()+", "+
	"and "+target->query_possessive()+" skin starts to decay.\n");
  tell_object(target,caster->query_cap_name()+" completes the spell, "+
	"and you feel decay enter your body...\n");
}
