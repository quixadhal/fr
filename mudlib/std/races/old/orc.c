inherit "/std/races/standard";

void setup() 
{
  set_long("An Orc is a carnivorous demi-human.\n");
  set_name("orc");
  reset_get();
}

void set_racial_bonuses() 
{
  previous_object()->adjust_bonus_int(-4);
  previous_object()->adjust_bonus_str(3);
  previous_object()->adjust_bonus_wis(-2);
  previous_object()->adjust_bonus_con(2);
  previous_object()->adjust_bonus_dex(1);
}

int query_skill_bonus(int lvl, string skill) 
{
  if (skill == "fighting.meelee")
    return 20;
  if (skill == "fighting.melee.sharp")
    return 30;
  return 0;
}

string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1)
  return "An ugly male orc.\n";
 return "A disgusting female orc.\n";
}

int query_dark(int i)
{
  if(i<5 || i>90) return 1;
  return 0;
}
