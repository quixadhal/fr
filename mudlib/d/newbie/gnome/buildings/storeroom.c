#include "path.h"
inherit "/std/storeroom";

inherit STOCK+"restock.c";

void setup()
{
	set_short("Darklor's Smithy");
     set_long("This is the storeroom for Darklor's Smithy.  There "
		"are weapons and armors lining the walls.\n\n");

   add_exit("out",ROOM+"dwarf32.c","out");
   set_light(60);
}

void reset() {

   call_out("after_reset", 0);
}

void after_reset() {

   restock(2,"chainmails",ARMOR+"dwarven_chain.c");
   restock(4,"pairs of gauntlets",ARMOR+"dwarven_gauntlets.c");
   restock(2,"leathers",ARMOR+"leather.c");
   restock(3,"helmets",ARMOR+"dwarven_helm.c");
   restock(5,"short swords",WEAPON+"short_sword.c");
   restock(4,"knives",WEAPON+"knife.c");
   restock(4,"gloves",ARMOR+"gloves.c");
   restock(10,"daggers",WEAPON+"dagger.c");
}
