#include <standard.h>
#include <cmd.h>
inherit CMD_BASE;

void setup()
{
    position = 0;
}

static int cmd(string str, object me) {
    int i, adjust, check1, check2;
    string pname;
    object *who, player;
    mapping stats;

    if(!str)
	return 0;
    if(!me->query_lord())
	return 0;
    check1 = sscanf(str, "%s %d", pname, adjust);
    if(check1 != 2) {
	check2 = sscanf(str, "%s", pname);
	if(check2 != 1) {
	    notify_fail("Usage: correctac <player>|<player> <amount>\n");
	    return 0;
	}
    }
    who = users();
    for(i=0;i<sizeof(who);i++)
	if(who[i]->query_name() == pname) 
	    player = who[i];
    if(!player) {
	notify_fail("There is no one logged in with that name.\n");
	return 0;
    }

    if(check2) {
	if(player->query_guild_name() != "shifter") {
	    notify_fail("You must enter an amount to adjust if "
	      "the player is not in the shifter guild.\n");
	    return 0;
	}
	stats = player->query_property("shifter_stats");
	if(!sizeof(stats)) {
	    notify_fail("This shifter apparently has not tried to "
	      "shift yet and therefore does not need to have "
	      "an ac correction.\n");
	    return 0;
	}
	player->set_ac(100-stats[7]);
	tell_object(me, "Ok.\n");
	return 1;
    }
    player->set_ac(adjust);
    tell_object(me, "Ok.\n");
    return 1;
}

string query_short_help() {
    return "This command allows the user to adjust the ac "
    "of a player by 100-amount or if no amount is entered "
    "and the player is in the shifter guild the amount is "
    "corrected to what it originally was before the first "
    "time the player ever tried to shift.";
}

string query_usage() {
    return "correctac <player>|<player> <amount>";
}
