
#include "tweaks.h"
inherit SPELLS+"baseres.c";

void create()
{
    SP_NAME = "Major Death Resistance";
    TYPE = "death";
    save_type = "magical";
    chant_message = "marj mortis rissas";
  ::create();  }



