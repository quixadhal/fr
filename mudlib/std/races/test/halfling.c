inherit "/std/races/standard";

void setup() 
{
  set_long("A halfling is a short, plump demi-human.\n");
  set_name("halfling");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_wis(-2);
  previous_object()->adjust_bonus_dex(2);
  previous_object()->adjust_bonus_str(-2);
  previous_object()->adjust_bonus_con(2);
}

int query_skill_bonus(int lvl, string skill) 
{
  return 0;
}

string query_desc(object ob) 
{
if((int)ob->query_gender() == 1)
   return("A short halfling lad.\n");
 return("A short halfling lass.\n");
}

int query_dark(int i)
{
  if(i<20 || i>180) return 1;
  return 0;
}
