#include "path.h"

inherit ROOMS+"gen.c";
void setup(){my_setup();
    set_short("Highlo : Forest Hill  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("Forest Hill.  \n\n"
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);
    add_exit("south",ROOMS+"ken5.c","path");
    add_exit("southwest",ROOMS+"ken6.c","path");
    add_exit("west",ROOMS+"ken8.c","path");
}


