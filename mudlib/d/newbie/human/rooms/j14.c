#include "path.h"
inherit HAVMAND+"jungle.c";

void setup()
{
    
    set_long("\nIsle of Havmand : Jungle\n\n"
    "Bright green ferns are growing here, which seems a bit strange. You "
    "don't remember seeing them anywhere else, but it makes "
    "a nice change from just the trees. Maybe they like the slightly lighter "
    "conditions nearer the edge of the jungle. "
    "\n\n");
    add_item( ({"fern","ferns"}),"The ferns have bright green fronds and "
    "look slightly delicate, but they are still impossible to get past "
    "in places. "
    "\n");

}
void init()
{
    add_exit("north",HAVMAND+"j13.c","path");
    add_exit("south",HAVMAND+"j15.c","path");
    add_exit("west",HAVMAND+"t08.c","path");

    ::init();
}


