inherit "/std/races/standard";

void setup() {
  set_long("The human race.  The standard by which all the races are set, "
           "this is race can be considered the norm.\n");
   set_name("human");
}

string query_desc(object ob) {
  if ((int)ob->query_gender() == 1)
    return "A strapping young human lad.\n";
  return "A strapping young human lass.\n";
}

int query_dark(int light) {
  return (light < 20) || (light > 200);
}
