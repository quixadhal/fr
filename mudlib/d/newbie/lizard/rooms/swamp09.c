#include "path.h"
inherit ROOM+"baseroom";

void setup()
{
    my_setup();
    set_short("Realm of the Lizard :  Swamp");

    set_long("Realm of the Lizard : Swamp.\n\n"
      "You are standing waist deep in a dark murky swamp. "
      "The water is a disgusting green, covered with a thin sticky film that clings to you. "
      "The water is poisonous, the once thriving forest lays in ruins from its poison.\n\n");
    set_light(80);
    add_exit("east",ROOMS"swamp11.c","path");
    add_exit("northeast",ROOMS"swamp10.c","path");
    add_exit("north",ROOMS"swamp08.c","path");
    add_exit("northwest",ROOMS"swamp06.c","path");
    add_exit("west",ROOMS"swamp07.c","path");
    // add_exit("southwest",ROOMS".c","path");
}
