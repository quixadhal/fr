#include "path.h"

inherit "/std/outside";
void setup()
{
    set_short("Highlo : Forest Hill  \n");
    set_light(LIGHT);
    add_property("no_undead",1);
    set_long("Forest Hill.  \n\n"
      "  This is the center of the cheerful town of Highlo. "
      "Your keen Kender eyes can see the buildings cleverly "
      "hidden nearby. The guild lies to your north, the tave"
      "rn lies to the northeast, the shop sits to the northw"
      "est, a chapel is to the west, and south heads out"
      " of town."
      "\n\n");


    add_item(({"tree","trees","forest"}),TREE);
    add_sound(({"birds","wildlife","bird","songs"}),BIRDS);
    add_feel(({"ground","dirt","floor"}),GROUND);
    add_exit("north",ROOMS+"guild.c","path");
    add_exit("northeast",ROOMS+"tavern.c","path");
    add_exit("northwest",ROOMS+"shop.c","path");
    add_exit("west",ROOMS+"raiseroom.c","path");
add_exit("east",ROOMS+"ken1.c","path");
add_exit("south",ROOMS+"ken2.c","path");
}


