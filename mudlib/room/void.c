inherit "/std/room";

void setup() {
     set_light(40);
     set_short("Convention in the void");
     set_long("This is where you come when you fall out a room and have " +
               "nowhere to go. You are inside a large igloo. Penguin " +
               "waiters (in tuxedos of course) are serving drinks to the " +
               "assembled crowd. A large wombat sits at the end of a " +
               "banquet table, his head resting peacefully in a bowl of " +
               "soup.\n\n");
     add_alias("bowl", "soup");
     add_alias("igloo", "around");
     add_alias("void", "igloo");
     add_alias("penguins", "penguin");
     add_alias("crowd", "penguin");
     add_alias("waiter", "penguin");
     add_item("soup", "It is pink and comfortable-looking\n");
     add_item("wombat", "Perhaps you should tell him to use his spoon.\n");
     add_item("igloo", "It is nice and warm despite the icy decor.\n");
     add_item("penguin", "The penguins are all rather formally dressed.\n");
     add_exit("tavern", "/d/ss/daggerford/ladyluck", "door");
//   add_exit("cleric", "/d/ss/daggerford/tymora", "door");
//   add_exit("fighter", "/d/ss/daggerford/barracks", "door");
}
