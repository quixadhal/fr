inherit "/std/races/standard";
inherit "/secure/patrons";

void setup() {
  set_long("Patrons are the creators of the mud.\n");
  set_name("patron");
}

string query_desc(object ob) {
  return "The immortal Patron of "+query_patronage(query_name())+".\n";
}

int query_dark(int i) { return 0; }
