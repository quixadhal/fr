inherit "/std/races/standard";

string *inedible;

void setup() {
  set_long("The Sysadm is the least liked race on the mud. Somehow"+
	   "the mud often get shut down when he is on.\n");
  set_name("lord");
  set_short("Sysadm");
  reset_get();
}

void start_player() {
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
     return "You wet your pants when you see this creature.\n";
}

int query_eat(string type) {
  return (member_array(type, inedible) == -1); 
}

int query_dark(int i) { return 0; }

string query_short() {
return "Bastard Operator From Hell";
}
string query_cap_name() {
return "Bastard Operator From Hell";
}
string query_name() {
return "Bastard Operator From Hell";
}

