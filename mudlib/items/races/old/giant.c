inherit "/std/races/standard";

void setup() {
  set_long("This has been set up as a monster race.\n");
   set_name("giant");
  reset_get();
}

void set_racial_bonuses() {
  previous_object()->adjust_bonus_con(6);
  previous_object()->adjust_bonus_int(-5);
  previous_object()->adjust_bonus_str(8);
  previous_object()->adjust_bonus_wis(-5);
}

int query_skill_bonus(int lvl, string skill) {
  return 0;
}

string query_desc(object ob) {
  return "A nasty looking Frost Giant";
}
