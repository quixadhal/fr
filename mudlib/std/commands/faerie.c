#include "/std/commands/tweaks.h"
#define AC_PENALTY 15

void make_spell(object doer, object victim);

string help()
{
    return
    "\n\n"
    "Command Name: Faerie Fire\n"
    "Syntax: faerie <target>\n"
    "GP COST: 10\n"
    "Description: \n"
    "     Faerie fire lets you engulf somebody in sparkling flames, "
    "making him an easier target to melee attack.\n\n";
}

int faerie(string str, object doer) 
{ 
    object *vlist;
    object victim;

    if (!str)
    {
	write("Who is your target?\n");
	return 1;
    }
   if(!doer) doer = TP;

    vlist = find_match(str, environment(doer));

    if(!sizeof(vlist)) {
	write("Try someone that is here.\n");
	return 1;  }

    victim=vlist[0];

    if(victim->query_hide_shadow()) {
	write("Try someone that is here.\n");
	return 1; } 

    if(doer->query_property("pacify_on")) {
	write("Something prevents you from doing this\n");
	return 1; }

    if(victim->query_dead()) {
	write("That would not have any effect on a ghost\n");
	return 1;  }

    if(victim->query_property("pacify_on"))  {
	write("This one's way too harmless already.\n");
	return 1;  }

    if(victim == doer)  {
	write("Not a bright thing to do.\n");
	return 1;  } 

    if(victim->query_static_property("faerie_on"))  {
	write("Your target is already under "
	  "the effect of faerie fire.\n\n");
	return 1;  }

    if(doer->query_timed_property("FAERIE")) {
	write("You will have to wait before being able to do this "
	  "again.\n");
	return 1;  }

    if((doer->query_race() == "elf" ||
	doer->query_race() == "half-elf") &&
      environment(doer)->query_light() < 10)  {
	write("You are not able to find your target in this "
	  "darkness.\n");
	return 1;  }

    if((doer->query_race() == "drow" ||
	doer->query_race() == "half-drow") &&
      environment(doer)->query_light() > 80) {
	write("The light is so bright that you cannot "
	  "locate your target.\n\n");
	return 1; }


    doer->adjust_gp(-10);
    call_out("make_spell", 0, doer, victim);
    if(!doer->query_hide_shadow())  victim->attack_by(doer);

    return 1;
}


void make_spell(object doer, object victim)
{
    int duration;
    duration = (doer->query_int()+doer->query_level())*2;

    tell_object(doer,"\n     As you raise a finger and point in "
      +victim->query_cap_name()+"'s direction, flames spring and engulf "
      +victim->query_objective()+".\n");

    if(!doer->query_hide_shadow())
	tell_object(victim, "\n     "+doer->query_cap_name()+" raises a finger "
	  "in your direction, and you are suddenly engulfed in sparkling "
	  "flames!\n");
    else
	tell_object(victim, "     You are suddenly engulfed in sparkling "
	  "flames!\n");

    tell_room(environment(victim), "\n     "+victim->query_cap_name()+
      "'s body is suddenly engulfed in sparkling flames!!\n", 
      ({doer, victim}));

    victim->adjust_tmp_ac_bon(-AC_PENALTY);
    victim->add_extra_look(this_object());
    victim->add_static_property("faerie_on", 1);
    doer->add_timed_property("FAERIE", 1, 900);

    call_out("wear_off",duration, victim);
}

void wear_off(object victim)
{
    if(victim)
    {
	victim->adjust_tmp_ac_bon(AC_PENALTY);
	tell_object(victim, "The flames around you die.\n");
	victim->remove_extra_look(this_object());
	victim->remove_static_property("faerie_on");
    }
}

string extra_look()
{
    return "Is surrounded by a sparkling flames that make him an easy "
    "target.\n";
}
