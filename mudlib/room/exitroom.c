inherit "/std/room";

void setup()
{
   set_short("Empty room");
   set_long("An empty boring room.\n");
   add_exit("ladyluck","/d/ss/daggerford/ladyluck","portal");
   add_exit("banefall","/d/bf/banefall/wizway","portal");
}
