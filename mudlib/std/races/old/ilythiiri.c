inherit "/std/races/standard";

void setup()
{
  set_long("The Ilythiiri are the forerunners of the drow.\n");
  set_name("Ilythiiri");
  reset_get();
}

void set_racial_bonuses()
{
  previous_object()->adjust_bonus_wis(2);
  previous_object()->adjust_bonus_int(4);
  previous_object()->adjust_bonus_dex(2);
  previous_object()->adjust_bonus_str(-2);
  previous_object()->adjust_bonus_con(-2);
  previous_object()->adjust_bonus_cha(-4);
}

int query_skill_bonus(int lvl, string skill)
{
  return 0;
}

string query_desc(object ob)
{
 if((int)ob->query_gender() == 1)
   return("An Ilythiiri male elf, dangerous and yet devious.\n");
 return("A beautiful Ilythiiri female.\n");
}

int query_dark(int i) 
{
 if(i<0 || i>90) return 1;
 return 0;
}
