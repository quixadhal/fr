#include "path.h"
inherit "/baseobs/traps/atrap.c";
void setup()
{
   ::setup();
   mytrap = TRAP+"coldtrap";
   set_short("unarmed cold trap");
   add_alias("cold trap");
   add_alias("cold");
}
