inherit "/std/room";
object booklet;

void setup()
{
    set_short("Dwarfen Home.");

    set_long("The room you see is a small low roofed room. "
            "There are 3 exits, West, East and Down. The exit down "
            "apparently leads to the big dangerous World outside. "
            "There is a lot of mess on the floor, and it looks like the "
            "home has been ransacked by those Greenies. There is a bench on "
            "one side of the room with a low table sat near it. The only other "
            "obvious things of value are a small cupboard and an old painting.\n");
     
                                                       
    set_light(100); 

    add_item("mess", "This is basicly alot of old garbage...what the orcs "
            "didn't take when they raided the house.\n");

    add_item("floor", "This is soil covered beneath all the grime and "
            "is rather unintereseting.\n");

    add_item("bench", "This is a standard bench.\n");
        
    add_item("table", "This is a standard small table.\n");
        
    add_item("cupboard", "This is closed and seems to have been missed "
            "by the greenies when they attacked the home.\n");

    add_item("painting", "This is merely painted on the walland seems "
            "more like a painting in blood, of a "
            "old drawf with a dagger in his heart. You realise that "
            "the painting was painted by Torgoch, leader of the major "
            "ork scouting parties round here.\n");


    add_exit("west", "/w/leafstar/dwarf2.c", "door");
    add_exit("east", "/w/leafstar/dwarf3.c", "door");
    add_exit("down", DAGG +"ladyluck.c", "door");

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
