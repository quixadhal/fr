#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("The Elven Forest  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("The Elven Forest.  \n\n"
      "You walk deeper into the forest, finding that there appear to "
      "be more animals everywhere you go. The animals are young here "
      "and seem to avoid other life a lot less "
      "than their older counterparts."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);

    add_exit("south",ROOMS+"elf1.c","path");
    add_exit("north",ROOMS+"elf4.c","path");
    add_exit("northwest",ROOMS+"elf5.c","path");
    add_clone(CHAR+"rabbit.c",1);
    add_clone(CHAR+"forlarren.c",1);
}


