inherit "/std/room";

void setup()
{
        set_short("The Pit.");

        set_long("This is a  large dark pit which is full of various "+
                "bits and bobs....all owned by Leafstar. Among the debris are "+
                "many empty bottles of K, a number of empty cans of Skol and the "+
                "beer barrels from the cellar. There is also various equipment "+
                "such as a Sword of Vengence (still glowing), and other minor "+
                "bits of Weapons and Equipment. This is where Leafstar sits and sobs "+ 
                "when he gets depressed. There is one exit - Up to the Cellar.\n");

        set_light(50); /* gives a dingy/loomy feel to the place */

        add_item("pit", "This is a dark deep hole dug personally by leafstar, "+
                "which looks freshly dug. It is clean but still smells because "+
                "of all the rubbish in the soil into which it was dug.\n");
                
        add_item("bottles", "These empty bottle's of k are all good and fine.. "+
                "but they would be better full.\n");
                
        add_item("barrels", "Like the empty bottle's of K cider these are also "+
                "empty...unlucky.....*grin*.\n");

        add_item("sword", "This sword is bolted down....as it is not allowed.\n");

        add_item("debris", "The debris is dirty, smelly and uninteresting.\n");

        add_exit("cellar", "/w/leafstar/cellar.c", "door");
}
