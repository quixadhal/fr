#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("The Elven Forest  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("The Elven Forest.  \n\n"
      " Here you see many small trees. They are broad leafed trees, and "
      "you realize that they are not native here. The only person that "
      "could have brought them here, as far as you know, is Edgar, the "
      "innkeeper. He once told you that he had planted a small grove out"
      " here, but it had never bloomed. He had seemed disappointed at this"
      " because it was the only seeds he had."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);

    add_exit("southwest",ROOMS+"elf13.c","path");
    add_exit("northwest",ROOMS+"elf15.c","path");
    add_exit("northeast",ROOMS+"elf16.c","path");
    add_clone(CHAR+"boar.c",1);
    add_clone(CHAR+"forlarren.c",1);
    add_clone(CHAR+"rabbit.c",1);
}

