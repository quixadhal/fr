#include "path.h"
inherit "/std/room";

void setup()
{
        set_short("Living Room.");

        set_long("This is a well lived living room which you know "+
                "well because this was your home when you were younger. "+
                "There is a large bench covering the whole of one side "+
                "of the room, and an assortment of various other stools etc. "+
                "There is one exit down to the dangerous outside world, "+
                "as well as stairs up and doorways to the east and west.\n");

        set_light(100); 

        add_item("bench", "This is a pretty boring bench, old and worn. "+
                "You recognise it as the one you nearly sat on when you "+
                "younger.\n");

        add_item("stool", "This 3 legged stool is a basic stool...you see "+
                "one the elfen trademanships mark on one of the legs.\n");

       add_exit("leave", "/d/ss/daggerford/ladyluck.c", "door");
       add_exit("east", PATH+"elf2", "door");
       add_exit("west", PATH+"elf3", "door");
   add_property("no_undead",1);
}

void add_equipment()
  {
  object boo;

  boo = clone_object("/items/weapon/short_sword");
  boo->move(this_object());

  /* You can use boo for all the equipment..*/
  boo = clone_object("/items/armour/cloak");
  boo->move(this_object());
  return;
}         

