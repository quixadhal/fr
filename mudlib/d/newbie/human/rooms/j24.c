#include "path.h"
inherit HAVMAND+"jungle.c";

void setup()
{
    
    set_long("\nIsle of Havmand : Jungle\n\n"
    "You are still deep in the jungle, but you notice that the track seems "
    "to slope slightly. The trees still look the same, but its almost as "
    "if you can sense a change ahead. You start to walk faster... "
    "\n\n");

}
void init()
{
    add_exit("north",HAVMAND+"j25.c","path");
    add_exit("southeast",HAVMAND+"j23.c","path");

    ::init();
}


