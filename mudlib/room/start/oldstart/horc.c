inherit "/std/room";

void setup()
{
        set_short("Half Orc Pit");

        set_long("This is a little small pit which serves as a home "
                "for you poor races. There is not much here but you "
                "may be lucky. There is a pile of ashes in one corner "
                "with a few old blackened pots arround them. There is a  "
                "single small stool near the fire, upon which is a small "
                "piece of tattered paper folded into a booklet. There is a "
                "large pile of oddments in the opposite corner, god knows what "
                "you will find there. The only exit seems to lead to the "
                "dark, dangerous world.\n");
                                                       
        set_light(80); 

        add_item("Pit", "This is a mud lined pit...good eh?.\n");

        add_item("Ashes", "Hmmm well these are ashes, what did you expect? "
                          "They are cold and grey... a bit like death.\n");
                       
        add_item("Pots","These are old cooking utensiles of no use.\n");

        add_item("Oddments", "This is a large pile with the odd glint here or there, "
                              "but you can't tell much more at the moment.\n");
        add_exit("south", DAGG +"ladyluck.c", "door");       
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
        


