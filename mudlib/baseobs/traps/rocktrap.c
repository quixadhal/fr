//Coded by:  Dyno
//Example Code from /baseobs/traps

inherit "/std/spells/trap.c";


void setup()
{
     ::setup();
     set_trap("/std/spells/wizard/crumble_wall.c",2,50,500,"A bunch of rocks in "
        "an easy to release net."
        "\n\n");
}
