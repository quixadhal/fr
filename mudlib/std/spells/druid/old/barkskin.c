/*** Barkskin ***/
/*** By Wonderflug ***/

#include "tweaks.h"

#define SP_NAME "Stoneskin"
#define GP_COST BARKSKIN_GP
#define SPELLTYPE "offensive"

string help() {
       return
       "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "Sphere: \n"
       "Level: 2nd\n"
       "Gp Cost: "+GP_COST+"\n"
       "Description: \n"
       "  This spell causes the druid's skin to become very tough and hard, "
       "like tree bark.  Damage from attacks will be reduced while the "
       "Barkskin is in effect, and in addition a -1 to AC will be given. "
       "However, since the skin will be heavier, a -1 to dexterity will be "
       "incurred as well.  The spell lasts 5 rounds per level of the "
       "caster.\n\n";
}

int cast_spell(string str, object caster)
{
  int i;
  object* obs;
  object target, my_caster;

  if (caster)
        my_caster = caster;
  else
  {
        my_caster = this_player();
        str = (string)my_caster->expand_nickname(str);
  }


  if (my_caster->query_spell_effect(SPELLTYPE))
  {
        tell_object(my_caster,"You are already casting a spell.\n");
        return 1;
  }

  obs = find_match( str, environment(my_caster) );
  if (!(obs))
  {
        tell_object(my_caster, "There is nobody of that name here.\n");
        return 1;
  }
  target = obs[0];

  if ( target->query_stoneskin_spell() || target->query_mirror_spell() ||
        target->query_armour_spell() || target->query_wraithform() )

  {
        tell_object(my_caster,"Magic around your target disrupts your "
          "spell.\n");
        return 1;
  }

  tell_object(my_caster, "You start to cast "+SP_NAME+".\n");
  tell_room(environment(my_caster), my_caster->query_cap_name()+
        " begins to cast a spell.\n",
        my_caster);

  my_caster->add_spell_effect(4, SPELLTYPE, SP_NAME, this_object(),
	"hb_spell", ({ target }) );
  return 1;
}

void hb_spell( object caster, mixed* params, int time )
{
  object shadow;
  object target;

  switch( time )
  {
    case 4:
	tell_object(caster, "You go into a deep meditative trance, drawing "
	  "in power from the earth.\n");
	tell_room(environment(caster), caster->query_cap_name()+
	  " goes into a deep trance.\n", caster);
	return 0;
    case 3:
	tell_object(caster, "You awaken from the trance, wrapped in a "
	  "sheath of power.\n");
	tell_room(environment(caster), caster->query_cap_name()+
	  " awakens from the trance, and "+caster->query_possessive()+
	  " eyes seem to glow slightly.\n", caster);
	return 0;
    case 2:
	tell_object(caster, "You weave the forces of nature into a "
	  "rippling sheath of healthy, living tree bark.\n");
	tell_room(environment(caster), "A huge sheet of tough, rippling "
	  "tree bark forms in front of "+caster->query_cap_name()+
	  ".\n", caster );
	return 0;
    default:
	break;
  }

  target = params[0];

  if ( caster->adjust_gp(-GP_COST) < 0 )
  {
	tell_object(caster, "You don't have the energy to complete the "
	  "spell.\n");
	tell_room(environment(caster), caster->query_cap_name()+" sways "
	  "tiredly.\n", caster);
	tell_room(environment(caster), "The sheath of bark falls limply "
	  "to the ground and disintegrates.\n");
	return 0;
  }

  if ( target->query_skin_spell() || target->query_mirror_spell() ||
        target->query_armour_spell() || target->query_wraithform() )

  {
        tell_object(caster,"Magic around your target disrupts your "
          "spell.\n");
	tell_object(target, "The sheath of bark descends around you "
	  "but slowly fades to nothingness before it touches you.\n");
	tell_room(environment(caster), "The sheath of bark descends "
	  "around "+target->query_cap_name()+" but disintegrates into "
	  "nothingness.\n", ({ caster, target }) );
        return 1;
  }


  if ( target == caster )
  {
    tell_object(caster, "You wrap yourself in the sheet of bark and feel "
	"protected.\n");
    tell_room(environment(caster), caster->query_cap_name()+" wraps "+
	caster->query_possessive()+"self in the sheet of bark, and it "
	"eerily molds to "+caster->query_possessive()+" skin.\n", caster);
  }
  else
  {
    tell_object(caster, "You wrap the sheet of bark around "+
	target->query_cap_name()+", in a protective shell.\n");
    tell_object(target, "The sheath of bark enfolds you and molds "
	"onto your skin.\n");
    tell_room(environment(caster), "The sheath of bark enfolds "+
	target->query_cap_name()+" and molds to "+target->query_possessive()+
	" skin.\n", ({ caster, target }) );
  }

  target->add_timed_property("barkskin_on",1,
	BARKSKIN_DURATION_BASE+
	  (BARKSKIN_DURATION_LEVEL*(int)caster->query_level()) );
  target->adjust_tmp_dex(-1);
  target->adjust_tmp_ac_bon(1);

  shadow = clone_object(BARKSKIN_SHADOW);
  shadow->setup_shadow(target);
  target->add_extra_look(shadow);

  return GP_COST;
}

