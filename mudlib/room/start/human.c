#include "path.h"
inherit "/std/room";

void setup()
{
        set_short("Human entry room.");

        set_long("  This looks like the living room of a small cottage, "+
                "it has a low ceiling and lots of timber supports which "+
                "give it the old look which reminds you that you are home. "+
                "There is an old wood burning fire on one wall and it "+
                "radiates heat all over the room. The mantlepiece of the  "+
                "fire is covered with small trinkets and brass objects, you "+
                "also see some worn furniture and doors leading outwards. "+
                "There is also an exit down and you get the feeling once "+
                "you go down you wont come back here again.\n");
                                                       
        set_light(100); 

        add_item("Furniture", "The furniture consists of a few old chairs, "+
                "a stool and a well worn table.\n");

        add_item("Fire", "This fire is very hot and is burning very well.\n");

        add_item("Trinkets", " They are small brass objects of no use at "+
                "all.\n");   
                
        add_alias("furniture", "Furniture");
        add_alias("fire", "Fire");
        add_alias("trinkets", "Trinkets");

        add_exit("leave", "/d/ss/daggerford/ladyluck", "door");
        add_exit("south", PATH+"human2.c", "door");
        add_exit("west", PATH+"human3.c", "door");
   add_property("no_undead",1);
}

void add_equipment()
  {
  object boo;

  boo = clone_object("/items/weapon/dagger");
  boo->move(this_object());
  
  /* You can use boo for all the equipment..*/
  boo = clone_object("/items/armour/cloak");
  boo->move(this_object());
  return;
}

