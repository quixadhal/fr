//by Taggert.
#include "path.h"


inherit "/std/room";

void setup()
{
    set_short("Elf House. \n");
    set_light(60);
    set_long("You wake to find yourself in the home of your birth."
      " You remember your childhood here, and all the fun times that "
      "you had as a child. But today is the day that you were told was"
      " your time to go make your place in the world. You have some "
      "items in here that your father gave you to start your journey."
      " The only thing is finding them. \n");


    add_exit("leave",ROOMS+"aaroc_center.c","door");
    add_exit("north",ROOMS+"start2.c","door");
    add_exit("south",ROOMS+"start3.c","door");
    add_exit("southeast",ROOMS+"elf18.c","hidden");
}
