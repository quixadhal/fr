#include "path.h"
inherit "/std/storeroom";

inherit ROOM+"restock.c";

setup() {
	set_short("Zundrin's Equipment Shop");
	set_long("This is the storeroom for Zundrin's Equipment "
		"shop.  There are several items on the shelves here.  "
		"\n\n");

   add_exit("out",ROOM+"dwarf30.c","out");
   set_light(60);
}

void reset() {

   call_out("after_reset", 0);
}

void after_reset() {

	restock(10,"torches",MISC+"torch.c");
	restock(4,"buckets",MISC+"wood_bucket.c");
	restock(5,"picks",MISC+"pick.c");
	restock(3,"leathers",ARMOR+"leather.c");
   restock(4,"Coils of rope", MISC + "rope.c");
}
