
#include "tweaks.h"
inherit SPELLS+"areabas.c";

void create()
{
    SP_NAME = "fireball";
    GP_COST = 6;
    TYPE = "fire";
    SIZE_OF_DICE =  6;
    save_type = "fire";
    maxlevel = 10;
    chant_message = "Majos areos pyros";
    ::create();
}


