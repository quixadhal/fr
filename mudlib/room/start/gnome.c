#include "path.h"
inherit "/std/room";
object booklet;

void setup()
{
        set_short("Gnome Household.");

        set_long("This is a small shack which serves as a living room, "+
                "bedroom and kitchen all in one. You recognise the room "+
                "when you realise it was where you were brought up. There "+
                "is a small pile of ashes in the centre of the shack, "+
                "and various blankets and such like stacked neatly whereever "+
                "space was found. Among these items are blankets, sacks "+
               "and god knows what else. There is one exit down to the large, "+
                "dangerous world which becons you.\n");
                                                       
        set_light(100); 

        add_item("shack", "This is a smallish shack well made but still "+
                "very little protection against the harsh winters which "+
               "are so common in this area. The walls are made of interweaved "+
                "hay.\n");

        add_item("ashes", "These are the remnants of the last meal you had as "+
                "a full family. There is a glint in the ashes which puzzles "+
                "you.\n");

        add_item("blankets", "These are your standard old fashiond blankets.\n");
        add_exit("leave", "/d/ss/daggerford/ladyluck", "door"); 
   add_property("no_guild",1);
}

void reset()
{
  if(!sizeof(find_match("booklet", this_object())))
  {
    booklet = clone_object(BOOK);
    booklet->move(this_object());
  }
} /* void reset */

void dest_me()
{
if (booklet)
booklet->dest_me();
::dest_me();
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

