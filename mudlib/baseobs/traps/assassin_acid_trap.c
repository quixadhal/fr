#include "path.h"
inherit "/baseobs/traps/atrap.c";
void setup()
{
   ::setup();
   set_short("unarmed acid trap");
   add_alias("acid trap");
   add_alias("acid");
}
