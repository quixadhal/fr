#include "path.h"
inherit "/std/room.c";

void setup()
{
add_property("no_undead",1);
set_light(LIGHT);
set_short("Island of Maroek:  Halfling Square");
set_long("Island of Maroek:  Halfling Square\n"
"This square is the center of the meager halfling town on this island.  Although "
"this entire area is within a giant tree, there is still enough dirt on the ground "
"and light in the sky to make it seem like the whole place is outdoors. "
    "\n\n");

add_clone(CHAR+"pippin.c",1);
add_exit("south",ROOMS+"guild.c","door");
add_exit("north",ROOMS+"half4.c","path");
add_exit("east",ROOMS+"road.c","path");


}
