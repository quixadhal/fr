//by Taggert.
#include "path.h";

inherit "/std/room";
void setup()
{
    set_short("Galastriia : Center of town. \n");
    set_light(LIGHT);
    set_long("\nYou stand in the center of town, a beautiful place. It "
      "teems with elven life. Here and there you even see animals running"
      " around. \n\n");

    add_exit("south",ROOMS+"shop.c","door");
    add_exit("southeast",ROOMS+"elf18.c","path");
    add_exit("north",ROOMS+"raiseroom.c","door");
    add_exit("west",ROOMS+"inn.c","door");
    add_exit("southwest",ROOMS+"guild.c","door");
    add_clone(NPCS+"elf_kid.c",3);
}
