#include "path.h"
inherit HAVMAND+"jungle.c";

void setup()
{
    
    set_long("\nIsle of Havmand : Jungle\n\n"
    "This bit of jungle is very close to the pirate camp, so you will want "
    "be very quiet. They don't like strangers hanging around, and the pirate "
    "chief has his shelter just east of here. "
    "\n\n");

}
void init()
{
    add_exit("east",HAVMAND+"p01.c","path");
    add_exit("west",HAVMAND+"j19.c","path");

    ::init();
}


