#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("The Elven Forest  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("The Elven Forest.  \n\n"
      "The forest around you is bright, and welcoming. The wind "
      "blows the leaves making them whisper nonsense to the sky "
      "leaving you left out of the conversation."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);

    add_exit("north",ROOMS+"elf9.c","path");
    add_exit("southwest",ROOMS+"elf3.c","path");
    add_clone(CHAR+"rabbit.c",1);
    add_clone(CHAR+"forlarren.c",1);
    add_clone(CHAR+"deer.c",1);
}

