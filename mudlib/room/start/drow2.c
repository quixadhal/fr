#include "path.h"
inherit "/std/room";
object booklet;

void setup()
{
        set_short("Drow Kitchen.");

        set_long("This is the well worn kitchen of your family home. "+
                "There is a large wood burning stove with a pile of "+
                "wood at one side of it. There is a large cupboard which "+
                "is closed. There is a table in the centre of the room, upon which "+
                "you remember having many a good home cooked meal. There "+
                "is a single door to the east.\n");

        set_light(50); 

        add_item("stove", "This is an old fashioned stove which looks like it "+
                "hasn't been used for many years. There is a mouldy loaf "+
                "still in there..youre forgetful mother must've forgotton it.\n");

        add_item("wood", "The wood is good solid, slow burning wood, which is actually "+
                "past it's best because it is slightly damp.\n");

        add_item("cupboard", "This is a large cupboard used to store food in.\n");

        add_item("table", "This is a large square table where you regulary ate.\n");

        add_item("loaf", "You don't even like the sight of the oven let alone mouldy bread.\n");


        add_exit("west", PATH+"drow", "door");
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

void dest_me ()
  {
  if (booklet) 
    booklet->dest_me();
  } /* dest_me */
