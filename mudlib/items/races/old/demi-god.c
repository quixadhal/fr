inherit "/std/races/standard";

string *inedible;

void setup() {
  set_long("A Demi-God is the second most powerful being in FR-MUD.\n");
  set_name("lord");
  /*new light handling */
  set_light_limits(LIGHT_BOUNDS_LOW, LIGHT_BOUNDS_HIGH);
  reset_get();
}

void set_racial_bonuses() {
  previous_object()->adjust_bonus_int(15);
  previous_object()->adjust_bonus_dex(15);
  previous_object()->adjust_bonus_str(15);
  previous_object()->adjust_bonus_wis(15);
  previous_object()->adjust_bonus_con(15);
  inedible = ({ "skull", "teeth" });
}

int query_skill_bonus(int lvl, string skill) {
  return 50;
}

string query_desc(object ob) {
  switch((int)ob->query_gender())
  {
    case 1 : return "You stand in awe at the sight of a Almighty Demi-God.\n";
    case 2 : return "You are stunned by the beauty of a Demi-Goddess.\n";
    case 3 : return "This Demi-God is Bisexual... wow!\n";
    default:return "This Demi-God has no sex whatsoever.\n";
  }
}

int query_eat(string type) {
  return (member_array(type, inedible) == -1); 
}
