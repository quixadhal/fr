#include "path.h"
inherit CITYROOM;

#define NUM 3

setup()
{
set_light(80);
set_short("Landis Way");
set_long("You are on Landis Way before a sturdy gate.  "+
 "The gate is closed at the moment, so you can't get in there. "+
 "There's a mighty temple to the east. The doors to the temple "+
 "are open.\n");
add_exit("south",ROOM+"landis4", "road");
add_exit("east", LATHANDER +"lath1", "door");
add_alias("ducal castle", "castle");
add_alias("ducal", "castle");
add_item("castle",
 "It's a three-story stone keep, surrouded by "+
 "a two-storey stone wall. The gates are closed.\n");
add_alias("bright temple", "temple");
add_item("temple",
 "It's a cylindrically formed bright temple. It's also quite large for "+
 "a small town like Daggerford. It's doors are open.\n");

set_monster(NUM, "city");
set_zone("city");
}
