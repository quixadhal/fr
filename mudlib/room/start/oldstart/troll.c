inherit "/std/room";
object booklet;

void setup()
{

set_short("Trolls Cave");
        set_long("This is a large cave with a largish entrance to the "+
                "North and and a smaller seemingly disused entrance to "+
                "the South. In the room is a Pile of bones, a small  "+
                "fire and a mouldy head. There are no stools strong "+
                "enough to hold you which explains why there aren't any. "+
                "By the fire is a small taterred booklet, possibly the "+
                "next fire lighter. There is a pile of blankets in one "+
                "but apart from that the room seems bare.\n");
                
        set_light(100); 

        add_item("Cave", "This is a stone carved cave.\n");

        add_item("Bones", "These seem to be of Goblioid type, possibly an orc's.\n");

        add_item("Head" ,"Hmm, well it's a human head but it's green...must've gone "+
                 "off. Looks tasty you think.\n");

        add_item("Blankets", "These are large and worn, but may keep you warm..\n");

        add_alias("cave", "Cave");
        add_alias("lair", "Cave");
        add_alias("bones", "Bones");
        add_alias("head", "Head");
        add_alias("blankets", "Blankets");
        add_exit("south", "??????????", "door");
       add_exit("north", "/w/leafstar/troll2.c", "door");

}
void reset(){
        if(!booklet){
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
       }
}

void dest_me()
{
if (booklet)
booklet->dest_me();
::dest_me();
}
