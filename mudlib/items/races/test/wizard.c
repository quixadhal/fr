inherit "/std/races/standard";

void setup() {
  set_long("Wizards are the ones who work to create areas in a domain, but "+
           "that has no operational area yet.\n");
   set_name("wizard");
}

string query_desc(object ob) {
  return "is a Wizard.\n";
}

int query_dark(int i) { return 0; }
