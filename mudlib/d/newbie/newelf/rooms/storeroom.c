#include "path.h"
inherit "/std/room";

void setup()
{
    set_short("Hidden Storeroom.\n\n");
    set_light(60);

    add_clone("/baseobs/armours/leather",3);
    add_clone("/baseobs/armours/helmet",2);
    add_clone("/baseobs/armours/med_shield",2);
    add_clone("/baseobs/weapons/bastard_sword",3);
    add_clone("/baseobs/misc/torch.c",3);

    add_exit("north",ROOMS+"elf8.c","path");
    add_exit("south",ROOMS+"elf18.c","hidden");
}
