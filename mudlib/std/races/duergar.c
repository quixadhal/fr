inherit "/std/races/standard";
#include "light_defs.inc"

void setup() 
{
  set_long("A stout dark complexioned dwarf.\n");
  set_name("duergar");
  set_light_limits(LIGHT_DUERGAR_LOW, LIGHT_DUERGAR_HIGH);
  reset_get();
}

/* This is makeing a mess for me. */
void set_racial_bonuses() 
{
  previous_object()->adjust_bonus_int(-2);
  previous_object()->adjust_bonus_str(1);
  previous_object()->adjust_bonus_wis(2);
  previous_object()->adjust_bonus_con(2);
  previous_object()->adjust_bonus_dex(-2);
   previous_object()->adjust_bonus_cha(-1);
}

int query_skill_bonus(int lvl, string skill) 
{
  return 0;
}

/*
string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1)
  return "A stout dark complexioned dwarven male.\n";
 return "A black bearded dwarven female.\n";
}
*/
