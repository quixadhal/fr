#include "path.h"
inherit "/std/room";
object booklet;

void setup()
{
        set_short("Lizard man hut.");

        set_long("This is a little small hut which served as a home "+
                "for you, outside you see a wet dark and damp swamp. "+
                "The hut you are in is damp and the cool swamp air "+
                "drifts in through the window. There is a small table "+
                "in the center of the hut, upon which is a dirty"+
                "piece of tattered paper folded into a booklet. There "+
                "is a pile of oddments and pots which look strange. "+
                "The only exit seems to lead to the real world.\n");
                                                       
        set_light(70); 
        add_item("table", "Hmmm well this is a table, what did you expect? "+
                          "It is cold and damp.\n");
        add_item("pots","These are old cooking utensiles of no use.\n");
        add_item("oddments", "This is a large pile with the odd glint here or there, "+
                              "but you can't tell much more at the moment.\n");
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

  boo = clone_object("/items/weapon/trident");
  boo->move(this_object());

  /* You can use boo for all the equipment..*/
  boo = clone_object("/items/armour/cloak");
  boo->move(this_object());
  return;
}          
