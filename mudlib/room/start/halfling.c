#include "path.h"
inherit "/std/room";
object booklet;

void setup()
{
        set_short("Halfling Mountain home.");

        set_long("This is a small home which serves as a living room, "+
                "bedroom and kitchen all in one. There "+
                "is a small pile of ashes in the centre of the room, "+
                "and various blankets and such like stacked neatly whereever "+
                "space was found. Among these items are pans, sacks "+
                "and god knows what else. There is one tunnelleading out to the large, "+
                "dangerous world which becons you.\n");
                                                       
        set_light(100); 

        add_item("home", "This is a smallish home well designed to "+
                "offer protection against the harsh winters which "+
                "are so common in this area. The walls are carved out of "+
                "the rock and muddy hillside.\n");

        add_item("ashes", "These are the remnants of the last meal you had as "+
                "a full family. There is a glint in the ashes which puzzles "+
                "you.\n");

        add_item("blankets", "These are your standard old fashiond blankets.\n");
   add_exit("leave", "/d/ss/daggerford/ladyluck", "door");
   add_property("no_undead",1);
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
