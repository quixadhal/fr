
#include "tweaks.h"
inherit SPELLS+"baseres.c";

void create()
{
    SP_NAME = "Major Air Resistance";
    TYPE = "air";
    save_type = "magical";
    chant_message = "marj zephyrus rissas";
  ::create();  }



