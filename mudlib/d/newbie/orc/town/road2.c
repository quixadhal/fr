#include "path.h"
inherit CASTLE+"baseroom.c";

void setup ()   { my_setup();
    set_short("Realm of the Orc:  Road");
    set_light(40);
    set_long("\n   Realm of the Orc:  Road.\n\n"
      "     This road continues to the west and east.  To the east "
      "you "
      "see a gate, to the west the road leads to a intersection. "
      "\n\n");
    add_exit("west","/d/sf/areas/roads/of_road/road2.c","road");
    add_exit("east",TOWN+"road1.c","road");


}

