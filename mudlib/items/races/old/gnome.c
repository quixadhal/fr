inherit "/std/races/standard";

void setup() 
{
  set_long("A small Gnome.\n");
  set_name("gnome");
  reset_get();
}

void set_racial_bonuses() 
{
  previous_object()->adjust_bonus_int(2);
  previous_object()->adjust_bonus_str(-1);
  previous_object()->adjust_bonus_con(2);
  previous_object()->adjust_bonus_dex(-3);
}

int query_skill_bonus(int lvl, string skill) 
{
  return 0;
}

string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1)
  return "A funny, bearded gnome.\n";
 return "A female gnome.\n";
}

int query_dark(int i)
{
  if(i<5 || i>150) return 1;
  return 0;
}
