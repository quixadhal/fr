inherit "/std/races/standard";

void setup() {
  set_long("This has been set up as a monster race.\n");
   set_name("troll");
  reset_get();
} /* setup() */

void start_player() {
  previous_object()->adjust_bonus_con(3);
  previous_object()->adjust_bonus_int(-3);
  previous_object()->adjust_bonus_str(3);
  previous_object()->adjust_bonus_wis(-3);
} /* start_player() */

int query_skill_bonus(int lvl, string skill) {
  return 0;
} /* query_skill_bonus() */

string query_desc(object ob) {
  return "An ugly looking troll.\n";
} /* query_desc() */

int query_dark(int i)
{
  if(i<0 || i>80) return 1;
  return 0;
}
