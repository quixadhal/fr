inherit "/std/room";

void setup()
{
        set_short("Kitchen");

        set_long("  You appear to be in a kitchen, it has various cooking "
                "utensils scattered across a large wooden table. There is "
                "a large wood burining stove in the corner and a pile of "
                "wood stacked next ot it. There is a small sink on the "
                "east wall, above the sink is a small window. There is a "
                "big cupboard on the west wall which looks like it is used "
                "for storing food.\n");
                                                       
        set_light(100); 

        add_item("Cupboard", "The doors to the cupboard are closed maybe "
                "you could search it.\n");

        add_item("Stove", "This looks like any ordinary stove. The door "
                "is closed.\n");

        add_item("Sink", "This sink looks very dirty and you would think "
                "someone would clean the pans.\n");
        
        add_item("Wood", "The wood is just ordinary rough cut firewood.\n");
        
        add_item("Window", "The view from the window is a large expanse of "
                "open fields.\n");

        add_item("Utensils", "These are just a collection of normal cooking "
                "utensils.\n");

        add_alias("utensils", "Utensils");
        add_alias("stove", "Stove"); 
        add_alias("cupboard", "Cupboard"); 
        add_alias("sink", "Sink"); 
        add_alias("wood", "Wood"); 
        add_alias("window", "Window"); 
        add_exit("north","/w/leafstar/human1.c","door");
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
        booklet->set_long("This is a help Booklet. Upon reading it you "
                "see various helpful commands......\n "
                "1) Type help or help <topic> for general help.\n "
                "2) Score brings up your score.\n "
                "3) Skills brings up your current skill levels.\n "
                "4) To Communicate try Chat, tell, say or Shout.\n "
                "5) Who brings up a list of current mudders.\n "
                "6) Wield <weapon>, wear <armour> are needed to equip yourself.\n "
                "7) Search or Search <item> will search an area or specific item.\n "
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
