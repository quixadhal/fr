inherit "/std/races/standard";

void setup() 
{
  set_long("A half-orc looks like a very ugly human with sharp teeth.\n");
  set_name("half-orc");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_int(-3);
  previous_object()->adjust_bonus_str(2);
  previous_object()->adjust_bonus_wis(-2);
  previous_object()->adjust_bonus_con(2);
  previous_object()->adjust_bonus_dex(1);
}

int query_skill_bonus(int lvl, string skill) 
{
  if (skill == "fighting.meelee")
    return 20;
  if (skill == "fighting.melee.sharp")
    return 20;
  return 0;
}

string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1)
  return "An ugly half-orc.\n";
 return "A disgusting female half-orc.\n";
}

int query_dark(int i)
{
  if(i<10 || i>110) return 1;
  return 0;
}
