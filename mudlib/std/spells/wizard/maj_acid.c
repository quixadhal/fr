
#include "tweaks.h"
inherit SPELLS+"baseres.c";

void create()
{
    SP_NAME = "Major Acid Resistance";
    TYPE = "acid";
    save_type = "magical";
    chant_message = "marj corozles rissas";
  ::create();  }



