inherit "/std/races/standard";
#include "light_defs.inc"

void setup() {
  set_long("This has been set up as a monster race.\n");
   set_name("troll");
  set_light_limits(LIGHT_TROLL_LOW, LIGHT_TROLL_HIGH);
  reset_get();
} /* setup() */

void set_racial_bonuses() {
  previous_object()->adjust_bonus_con(3);
  previous_object()->adjust_bonus_int(-3);
  previous_object()->adjust_bonus_str(3);
  previous_object()->adjust_bonus_wis(-3);
} /* set_racial_bonuses() */

int query_skill_bonus(int lvl, string skill) {
  return 0;
} /* query_skill_bonus() */

string query_desc(object ob) {
  return "An ugly looking troll.\n";
} /* query_desc() */
