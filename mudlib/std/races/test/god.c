inherit "/std/races/standard";

string *inedible;

void setup() {
  set_long("A God is the ruler of a MUD.\n");
  set_name("god");
  reset_get();
}

void start_player() {
  previous_object()->adjust_bonus_int(97);
  previous_object()->adjust_bonus_dex(97);
  previous_object()->adjust_bonus_str(97);
  previous_object()->adjust_bonus_wis(97);
  previous_object()->adjust_bonus_con(97);
  inedible = ({ "skull", "teeth" });
}

int query_skill_bonus(int lvl, string skill) {
  return 100;
}

string query_desc(object ob) {
  switch((int)ob->query_gender())
  {
    case 1 : return "You stand in awe at the sight of a God.\n";
    case 2 : return "You are stunned by the unearthly beauty of a Goddess.\n";
    case 3 : return "You see a strange bisexual God.\n";
    default: return "You see a God with no apparent sex.\n";
  }
}

int query_eat(string type) {
  return (member_array(type, inedible) == -1); 
}

int query_dark(int i) { return 0; }
