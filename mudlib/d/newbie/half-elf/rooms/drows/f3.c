//Ljen nov -96

inherit"/std/room";
#include "path.h"
object drow, rat;

void setup()
{
   set_light(50);

   set_short("Drow tunnel");

   set_long(" The tunnel is narrower here, seems like it is not often"
            " used anymore. But the sound is getting louder and more"
	    " painful. You heart aces when thinking of what could cause"
	    " such pain and misery in a voice of a living creature."
	    " There is a small path leading northeast, but you are"
            " starting to wonder if it not is best to turn back.. \n");

   add_item("wall", "You can't see much, but it seems like they are of"
            " some kind of black rock. Water is dripping slowly down.\n");


   add_clone(NPC+"drow.c", 1);

   add_clone(NPC+"rat.c", 1);

   add_exit("northwest", DROWS+"e2.c", "path");

   add_exit("northeast", DROWS+"g2.c", "path");


}

