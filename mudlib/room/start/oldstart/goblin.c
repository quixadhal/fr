inherit "/std/room";
#define RACE "goblin"

void setup() {
     set_light(40);
     set_short("Home sweet home");
     set_long("This is the sweet "+RACE+" home you've grown up in.  You are "+
              "now a grown "+RACE+" and should be ready to venture into the "+
              "big world and make a name for yourself.\n");
     add_item("room", "It's nice an comfortable.  Actually a very typical "+
              RACE+"room.\n");
     add_exit("leave", DAGG +"wall1", "door");
}
