#include "path.h"
inherit "/std/outside";

void setup()
{
add_property("no_undead",1);
set_light(LIGHT);
set_short("Island of Maroek:  Forest\n");
set_long("Island of Maroek:  Forest Path\n\n"
"In this section of the forest, the trees' leaves have become a little more sparse, "
"allowing more light to filter to the ground.  The path forks in almost every direction "
"at this section of the forest.  "
    "\n\n");

add_clone(CHAR+"recluse.c",2);
add_exit("northeast",ROOMS+"half18.c","path");
add_exit("south",ROOMS+"half10.c","path");
add_exit("northwest",ROOMS+"half17.c","path");
add_exit("southwest",ROOMS+"half9.c","path");
}


