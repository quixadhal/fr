#include "path.h"
inherit "/std/outside";

void setup()
{
add_property("no_undead",1);
set_light(LIGHT);
set_short("Island of Maroek:  Forest\n");
set_long("Island of Maroek:  Forest Path\n\n"
"You are on a narrow path through the forest.  Dense foilage looms over you on either "
"side of the path, blocking your view of every direction separate from the path.  "
    "\n\n");

add_clone(CHAR+"wolf.c",2);
add_exit("southwest",ROOMS+"half14.c","path");
add_exit("north",ROOMS+"half21.c","path");
}


