inherit "/std/races/standard";

void setup() 
{
  set_long("A small and ugly demi-human.\n");
  set_name("goblin");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_int(-4);
  previous_object()->adjust_bonus_wis(-4);
  previous_object()->adjust_bonus_con(2);
  previous_object()->adjust_bonus_dex(4);
}

int query_skill_bonus(int lvl, string skill) 
{
  return 0;
}

string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1)
  return "A dirty-looking male goblin\n";
 return "A dirty-looking female goblin\n";
}

int query_dark(int i)
{
  if(i<0 || i>90) return 1;
  return 0;
}
