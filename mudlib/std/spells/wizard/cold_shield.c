
inherit "/std/spells/wizard/shield_spell.c";


void create() {
   SP_NAME      = "Shield of cold";
   GP_COST      = 10;
   SP_LEVEL     = 8;
   TYPE         = "fire";
   SUB_TYPE     = "cold";
   chant_message= "frozzen armoum protestus";
   ::create();
}
