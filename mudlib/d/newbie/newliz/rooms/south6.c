#include "path.h"

inherit "/std/outside";
void setup()
{
set_short("Lizard's Island:  Beach\n");
set_light(LIGHT);
add_property("no_undead",1);
set_long("Lizard's Island:  Beach\n\n"
"     This is the start of the lower arch of the Crescent Island.  Looking into "
"the distance, you can just see the hazy outline of where the beach arcs and "
"heads off the East.  However, the only paths open to you, at this time, "
"are to the North, West, and Southeast.  The beach itself runs further along "
"the path to the Southweast and North.  The path going to the West appears "
"to lead into a heavily foilated area of the jungle which stands precariously "
"close to the beach.  "
    "\n\n");

add_item("shells","These shells are common all over the island and are frail to "
"the touch.\n");
add_item("sun","The sun beats down from above.  It feels good to a lizard, such "
"as yourself.\n");
add_feel(({"sand","floor","ground"}),"The ground is very hot, and the sand hot "
"to the touch of your feet.\n");

add_exit("west",ROOMS+"south5.c","path");
add_exit("southeast",ROOMS+"south8.c","path");
add_exit("north",ROOMS+"south4.c","path");
}


