inherit "/std/room";
object booklet;

void setup()
{
        set_short("Human entry room.");

        set_long("  This looks like the living room of a small cottage, "
                "it has a low ceiling and lots of timber supports which "
                "give it the old look which reminds you that you are home. "
                "There is an old wood burning fire on one wall and it "
                "radiates heat all over the room. The mantlepiece of the  "
                "fire is covered with small trinkets and brass objects, you "
                "also see some worn furniture and doors leading outwards. "
                "There is also an exit down and you get the feeling once "
                "you go down you wont come back here again.\n");
                                                       
        set_light(100); 

        add_item("Furniture", "The furniture consists of a few old chairs, "
                "a stool and a well worn table.\n");

        add_item("Fire", "This fire is very hot and is burning very well.\n");

        add_item("Trinkets", " They are small brass objects of no use at "
                "all.\n");   
                
        add_alias("furniture", "Furniture");
        add_alias("fire", "Fire");
        add_alias("trinkets", "Trinkets");

        add_exit("down", DAGG +"ladyluck", "door");
        add_exit("south", "/w/leafstar/human2.c", "door");
        add_exit("west", "/w/leafstar/human3.c", "door");
}
void reset(){
        if(!booklet){
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
       }
}

void dest_me()
{
if (booklet)
booklet->dest_me();
::dest_me();
}

