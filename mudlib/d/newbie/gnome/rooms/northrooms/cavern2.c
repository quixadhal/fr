inherit "/std/room";
#include "path.h"

void setup ()   {
    set_short("Macedonia:  Cavern of Plantipus\n");
    set_light(20);
add_property("no_undead",1);
add_property("no_undead",1);
    set_long("Macedonia:  Cavern of Plantipus\n\n"
      "You are within the cavern of Plantipus.  To the East, there is a faint sound, which you "
      "cannot quite make out from here.  The atmosphere is one of dankness and decay throughout the "
      "cave.  You almost miss a small branch off to the North, where you hear a sound of running "
      "water.  "
      "\n\n");
    add_item(({"stalagmites","stalagtites"}),"These stalagmites and stalagtites are made of "
      "hardened calcium deposits over thousands of years.  They are gray in color and are dripping "
      "water in their growth.\n");
    add_item("water","Water is dripping all around you, and you are already quite soaked from it.\n");
    //     * senses *
    add_smell(({"here","cave","air","area","mouth"}),"The air here is damp and stale smelling.\n");
    add_sound(({"water","stream","underground","river","underground river"}),"You can just "
      "hear the small sound of water running to the North.\n");
    add_feel(({"here","cave","area","stalagtite","stalagmite"}),"The entire area has a cold, "
      "damp, slimey feeling to it.  You quickly find yourself not wanting to touch more than you "
      "have to in here.\n");
    add_clone(NPC+"rat.c",random(4));
    add_exit("north",NORTHRMS +"cavern3.c","path");
    add_exit("south",NORTHRMS +"cavern1.c","path");
    add_exit("east",NORTHRMS +"cavern5.c","path");
}
