inherit "/std/room";


void setup()
{
        set_short("Half-Elfen Kitchen.");

        set_long("This is the well used kitchen of your family home. "+
                "There is a large wood burning stove with a pile of "+
                "wood at one side of it. There is a large cupboard which "+
                "is closed. There is a table in the centre of the room. "+
                "You notice a small booklet on the table. There "+
                "is a single door to the east.\n");

        set_light(70); 

        add_item("stove", "This is an old fashioned stove which looks like it "+
                "hasn't been used for many years. This is as clean as your "+
                "mother left it still though.\n");

        add_item("wood", "The wood is solid, slow burning wood, which is actually "+
                "past it's best because it is slightly damp.\n");

        add_item("cupboard", "This is a large cupboard used to store food in.\n");

        add_item("table", "This is a large square table where you regulary ate.\n");
        add_exit("down", DAGG +"ladyluck.c", "door"); 
}                                
    void reset()
{
        object booklet;
        if(sizeof(find_match("booklet", this_object())))
        return;
        booklet = clone_object("/std/object");
        booklet->set_name("booklet");
        booklet->set_main_plural("booklets");
        booklet->set_short("booklet");
        booklet->set_long("This is a help Booklet. Upon reading it you "+
                "see various helpful commands......\n "+
                "1) Type help or help <topic> for general help.\n "+
                "2) Score brings up your score.\n "+
                "3) Skills brings up your current skill levels.\n "+
                "4) To Communicate try Chat, tell, say or Shout.\n "+
                "5) Who brings up a list of current mudders.\n "+
                "6) Wield <weapon>, wear <armour> are needed to equip yourself.\n "+
                "7) Search or Search <item> will search an area or specific item.\n "+
                "This is about it...enjoy the MUD.\n");
        booklet->set_weight(5);
        booklet->set_value(0);
        booklet->move(this_object());
        } /* if (!booklet) */
  } /* void reset */
void dest_me ()
  {
  if (booklet) 
    booklet->dest_me();
  } /* dest_me */
                                                   
        




