#include "path.h"
inherit "/std/outside";

void setup()
{
add_property("no_undead",1);
set_light(LIGHT);
set_short("Island of Maroek:  Forest\n");
set_long("Island of Maroek:  Forest Path\n\n"
 "The forest is hot and humid.  The wildlife appears to be keeping its distance, though"
", because the forest is almost dead quiet.  You can just see a path to your south, though.  "
"You also note that a large square can be seen faintly through the foilage to the south, "
"as well.  "
    "\n\n");

add_clone(CHAR+"owl.c",2);
add_exit("north",ROOMS+"half14.c","path");
add_exit("northeast",ROOMS+"half15.c","path");
add_exit("south",ROOMS+"half4.c","path");
add_exit("east",ROOMS+"half11.c","path");
}


