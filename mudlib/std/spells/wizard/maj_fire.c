
#include "tweaks.h"
inherit SPELLS+"baseres.c";

void create()
{
    SP_NAME = "Major Fire Resistance";
    chant_message = "marj pyros rissas";
    TYPE = "fire";
    save_type = "magical";
  ::create();  }



