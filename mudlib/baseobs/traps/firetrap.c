inherit "/std/spells/trap.c";

void setup()
{
   ::setup();
   set_trap("/std/spells/wizard/fireball.c",2,50,500,"A small rune encrusted box, pulsing with red light.\n");
}
