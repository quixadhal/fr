#include "path.h"
inherit HAVMAND+"jungle.c";

void setup()
{
    
    set_long("\nIsle of Havmand : Jungle\n\n"
    "You are on a path which is sloping gently downward. It is damper "
    "underfoot as well, and you think you can hear water trickling somewhere "
    "nearby. More of the trees seem to have moss and lichen growing on them "
    "here than before. "
    "\n\n");
    add_sound(({"water","trickling"}),"Water is definately trickling down "
    "somewhere nearby, but you can't see it anywhere here. "
    "\n");
    add_item("moss","The moss is thicker and grows more vigorously here "
    "than in other parts of the jungle. "
    "\n");

}
void init()
{
    add_exit("north",HAVMAND+"j16.c","path");
    add_exit("southwest",HAVMAND+"j31.c","path");

    ::init();
}


