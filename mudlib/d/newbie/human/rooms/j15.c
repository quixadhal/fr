#include "path.h"
inherit HAVMAND+"jungle.c";

void setup()
{
    
    set_long("\nIsle of Havmand : Jungle\n\n"
    "The trees are really thick here and its almost impossible to see through "
    "them, let alone make yourself a path. The track through the village is "
    "to the west and you can go north if you want to, but any other "
    "direction would be impossible. "
    "\n\n");

}
void init()
{
    add_exit("west",HAVMAND+"t09.c","path");
    add_exit("north",HAVMAND+"j14.c","path");

    ::init();
}


