#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("The Elven Forest  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("The Elven Forest.  \n\n"
      " The sound of the city close by makes it even harder to "
      "leave the city, knowing that you may never return. You "
      "sit for a short while and weep about having to leave, but"
      " you understand that you can't live at home forever. You "
      "were even starting to get a little stir crazy staying at home."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);

    add_exit("east",ROOMS+"Eldev.c","path");
    add_exit("north",ROOMS+"storeroom.c","hidden");
    add_exit("northwest",ROOMS+"aaroc_center.c","path");
    add_exit("up",ROOMS+"treetop18.c","hidden");
    add_clone(CHAR+"sprite.c",1);
}

