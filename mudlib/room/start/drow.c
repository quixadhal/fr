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

        set_light(50); 

        add_item("bench", "This is a pretty boring bench, old and worn. "+
                "You recognise it as the one you nearly broke when you "+
                 "were younger.\n");

        add_item("stool", "This 3 legged stool is a basic stool...you see "+
                "the drow trademanships mark on one of the legs.\n");

   add_exit("leave", "/d/bf/banefall/city/tavern", "door");
   add_exit("east", PATH+ "drow2", "door");
   add_exit("west", PATH+"drow3", "door");
   add_exit("up", PATH+"drow4", "door");
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
