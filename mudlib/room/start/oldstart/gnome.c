inherit "/std/room";
object booklet;

void setup()
{
        set_short("Gnome Household.");

        set_long("This is a small shack which serves as a living room, "
                "bedroom and kitchen all in one. You recognise the room "
                "when you realise it was where you were brought up. There "
                "is a small pile of ashes in the centre of the shack, "
                "and various blankets and such like stacked neatly whereever "
                "space was found. Among these items are blankets, sacks "
                "and god knows what else. There is one exit down to the large, "
                "dangerous world which becons you.\n");
                                                       
        set_light(100); 

        add_item("shack", "This is a smallish shack well made but still "
                "very little protection against the harsh winters which "
                "are so common in this area. The walls are made of interweaved "
                "hay.\n");

        add_item("ashes", "These are the remnants of the last meal you had as "
                "a full family. There is a glint in the ashes which puzzles "
                "you.\n");

        add_item("blankets", "These are your standard old fashiond blankets.\n");
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


