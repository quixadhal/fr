#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("Hidden Path");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("Hidden Path. \n\n"
      "  You have stumbled onto the hiding place of the evil bard Llyr. "
      "It is a dark area, with moss covered trees and mostly dead grass. "
      "You notice that there is some basic stuff for living in the forest."
      " Nothing really of interest though. You feel the evil that is "
      "deeply imbedded into this part of the forest. All the evil makes "
      "your skin itch, and all you want is to leave this area."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);

    add_exit("south",ROOMS+"hp9.c","hidden");
    add_clone(NPCS+"bard.c",1);
    add_clone(CHAR+"spider.c",1);
    add_clone(CHAR+"rabbit.c",1);
    add_clone(CHAR+"deer.c",1);
    add_clone(CHAR+"forlarren.c");
}

