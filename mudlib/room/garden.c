inherit "/std/room";

void setup() {
  set_light(70);
  set_short("Statue garden");
  set_long(
"This is a nice garden.  Scattered amongst the garden you notice amazingly "+
"acurate statues of people. All the statues seem to share the same "+
"problem: They have lost to the LAG-monster, and are linkdead.\n");

  add_exit("tavern", "/d/ss/daggerford/ladyluck", "door");

  add_item("garden",
           "It is a lovely garden, nice little walk ways drifting off into "+
           "the distance.  Lovely little sheltered groves and grotos.\n");
  add_item("statue",
           "Very life like statues of people.  Amazing what they can do "+
           "these days.\n");
}
