inherit "/std/room";
object booklet;

void setup()
{
        set_short("Living Room.");

        set_long("This is a well lived living room which you know "
                "well because this was your home when you were younger. "
                "There is a large bench covering the whole of one side "
                "of the room, and an assortment of various other stools etc. "
                "There is one exit down to the dangerous outside world, "
                "as well as stairs up and doorways to the east and west.\n");

        set_light(100); 

        add_item("bench", "This is a pretty boring bench, old and worn. "
                "You recognise it as the one you nearly broke when you "
                "younger.\n");

        add_item("stool", "This 3 legged stool is a basic stool...you see "
                "the drow trademanships mark on one of the legs.\n");

       add_exit("down", DAGG + "ladyluck.c", "door");
       add_exit("east", "/w/leafstar/drow2.c", "door");
       add_exit("west", "/w/leafstar/drow3.c", "door");
       add_exit("up", "/w/leafstar/drow4.c", "stair");

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

