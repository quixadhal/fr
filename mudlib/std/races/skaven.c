inherit "/std/races/standard";
#include "light_defs.inc"

void setup() {
  set_long("The skaven are a dangerous and deviouse race.\n");
  set_name("skaven");
  set_light_limits(-50, 200);
  reset_get();
}

void set_racial_bonuses() {
  previous_object()->adjust_bonus_int(-1);
  previous_object()->adjust_bonus_dex(1);
}

int query_skill_bonus(int lvl, string skill) {
  return 0;
}

string query_desc(object ob) {
 if((int)ob->query_gender() == 1)
    return ("A dirty male skaven.\n");
  return("A dirty female skaven.\n");
}
