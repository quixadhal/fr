/*** Thorn Foot -- Druids Spell ***/
/*** By Wonderflug ***/

#include "tweaks.h"

inherit "/std/spells/patch.c";

mixed find_one_match(string find,mixed in);
int cleric_fix_damage(object caster,object victim,int damage,string save);

#define SP_NAME "Thorn Foot"
#define GP_COST THORN_GP
#define SPELLTYPE "offensive"

string help() 
{
  return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "Sphere: Druids\n"+
       "Level: 2nd\n"+
       "Gp Cost: "+GP_COST+"\n"+
	"Saving Throw: None\n\n"+
        "Description: \n"+
	"     This spell will place a thorn unerringly into an opponent's "+
	"foot.  The bethorned victim will suffer damage when trying to move "+
	"until such a time as they remove the affliction at great pain to "+
	"themselves.  Won't have much effect on an NPC.\n\n";
}

mixed spell(string str, object caster);

int cast_spell(string str,object cast)
{
  int skill;
  mixed ret;
  object caster;

  caster = cast ? cast : this_player();

  if(interactive(caster))
	  str = (string)caster->expand_nickname(str);

  ret = spell(str, caster);
  if (stringp(ret))
  {
	notify_fail(ret);
	return 0;
  }

  tell_object(caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(caster),caster->query_cap_name()+" begins to cast "+
	"a spell.\n",
	caster);
  return 1;
}

mixed spell(string str, object caster)
{
  mixed ob;

  if ((int)caster->query_spell_effect(SPELLTYPE))
    return "You are already casting an "+SPELLTYPE+" spell.\n";

  ob = find_one_match(str, environment(caster));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;

  caster->add_spell_effect(3, SPELLTYPE, SP_NAME,
    this_object(), "hb_spell", ({ ob }));
  return 1;
}

int hb_spell(object caster, mixed *params, int time)
{
  object thorn;

  switch( time )
  {
    case 3:
	tell_object(caster, "You draw in power from the world for your "+
	  "enchantment.\n");
	tell_room(environment(caster), caster->query_cap_name()+" goes into "+
	  "an odd trance-like state.\n", caster);
	return 0;
    case 2:
	tell_object(caster, "A very sharp looking thorn appears in the air "+
	  "before you.\n");
	tell_room(environment(caster), "A very sharp looking thorn appears "+
	  "in the air before "+caster->query_cap_name()+".\n", caster );
	return 0;
    default:
	break;
  }
  if (!params[0] || environment(params[0]) != environment(caster) )
  {
	tell_object(caster, "Your spell failed.. there is no one of "+
	  "that name here.\n");
	tell_room(environment(caster), caster->query_cap_name()+" comes "+
	  "out of the trance, points a finger, and the thorn lodges itself "+
	  "into a nearby rock.\n", caster);
	return 0;
  }
  if ((int)caster->adjust_gp(-GP_COST)<0)
  {
	tell_object(caster, "You don't have enough power to guide the "+
	  "thorn to your target.\n");
	tell_room(environment(caster), caster->query_cap_name()+" sways "+
	  "tiredly and the thorn drops harmlessly to the ground.\n", caster);
    	return 0;
  }

  tell_object(caster, "You come out of the trance and guide the thorn to "+
	params[0]->query_cap_name()+"'s foot.\n");
  tell_object(params[0], caster->query_cap_name()+" comes out of the trance "+
	"and points at you.\n\nThe thorn comes streaking toward you and "+
	"lodges itself deeply into your foot!\n\nYou scream in pain.\n");
  tell_room(environment(caster), "The thorn suddenly streaks toward "+
	params[0]->query_cap_name()+" and lodges itself in "+
	params[0]->query_possessive()+" foot.\n\n"+params[0]->query_cap_name()+
	" howls in pain.\n", params[0] );

  params[0]->adjust_hp(-random(MAXDAM));
  thorn = clone_object(THORN);
  thorn->move(params[0]);
  thorn->reset_drop();
  thorn->reset_get();
  thorn->set_spell(params[0]);

  return GP_COST;
}
