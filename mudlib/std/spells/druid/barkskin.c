/*** Barkskin ***/
/*** By Wonderflug ***/

#include "tweaks.h"

inherit "/std/spells/base.c";

void setup()
{
  set_spell_name("Barkskin");
  set_spell_level(2);
  set_sphere("druid");

  set_target_type("one");
  set_range(0);

  set_help_desc("This spell causes the druid's skin to become very tough "
    "and hard, like tree bark.  Damage from attacks will be reduced while the "
    "Barkskin is in effect, and in addition a -1 to AC will be given. "
    "However, since the skin will be heavier, a -1 to dexterity will be "
    "incurred as well.  The spell lasts 5 rounds per level of the caster.");

  set_gp_cost(BARKSKIN_GP);
  set_casting_time(4);
  set_rounds( ({ "round1", "round2", "round3", "round4" }) );
}

int round1(object caster, mixed target, mixed out_range, int time, int quiet)
{
  tell_object(caster, "You go into a deep meditative trance, drawing "
    "in power from the earth.\n");
  tell_room(environment(caster), caster->query_cap_name()+
    " goes into a deep trance.\n", caster);
  return 0;
}

int round2(object caster, mixed target, mixed out_range, int time, int quiet)
{
  tell_object(caster, "You awaken from the trance, wrapped in a "
    "sheath of power.\n");
  tell_room(environment(caster), caster->query_cap_name()+
    " awakens from the trance, and "+caster->query_possessive()+
    " eyes seem to glow slightly.\n", caster);
  return 0;
}

int round3(object caster, mixed target, mixed out_range, int time, int quiet)
{
  tell_object(caster, "You weave the forces of nature into a "
    "rippling sheath of healthy, living tree bark.\n");
  tell_room(environment(caster), "A huge sheet of tough, rippling "
    "tree bark forms in front of "+caster->query_cap_name()+
    ".\n", caster );
  return 0;
}

int round4(object caster, mixed target, mixed out_range, int time, int quiet)
{
  object shadow;

  if ( !target )
  {
    tell_object(caster, 
      "Your spell failed ... there is nobody of that name here.\n");
    tell_room(environment(caster), "The sheath of bark falls limply "
      "to the ground and disintegrates.\n");
    return -1;
  }

  if ( target->query_stoneskin_spell() || target->query_mirror_spell() ||
        target->query_armour_spell() || target->query_wraithform() )
  {
    tell_object(caster,"Magic around your target disrupts your spell.\n");
    tell_object(target, "The sheath of bark descends around you "
      "but slowly fades to nothingness before it touches you.\n");
    tell_room(environment(caster), "The sheath of bark descends "
      "around "+target->query_cap_name()+" but disintegrates into "
      "nothingness.\n", ({ caster, target }) );
    return -1;
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

  target->add_timed_property("barkskin_on",1, BARKSKIN_DURATION_BASE+
    (BARKSKIN_DURATION_LEVEL*(int)caster->query_level()) ); 
  target->adjust_tmp_dex(-1);
  target->adjust_tmp_ac_bon(1);

  shadow = clone_object(BARKSKIN_SHADOW);
  shadow->setup_shadow(target);
  target->add_extra_look(shadow);

  return 0;
}

