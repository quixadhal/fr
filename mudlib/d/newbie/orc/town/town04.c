#include "path.h"
inherit "/std/outside";

void setup() {
set_short("Realm of the Orc:  West End of Town");
set_light(40);
   set_long("\n   Realm of the Orc:  West End of Town.\n\n"
            "     This is the westernmost end of the village.  To your "
            "north you can see a small store and there is a tavern to "
        "the south. To the west you see a large gate. "
            "The road east leads to the village center.  "
                "\n\n");
add_property("no_undead",1);
  add_clone(CHAR+"darkorc.c",1);
add_exit("west",TOWN+"town10.c","road");
add_exit("south",TOWN +"town08.c","road");
add_exit("north",TOWN +"town01.c","road");
add_exit("east",TOWN +"town05.c","road");
}
