inherit "/std/races/standard";

void setup() 
{
  set_long("The Elves are a noble race of swift forest-people.\n");
  set_name("elf");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_int(1);
  previous_object()->adjust_bonus_dex(2);
  previous_object()->adjust_bonus_str(-1);
  previous_object()->adjust_bonus_con(-2);
}

int query_skill_bonus(int lvl, string skill) 
{
  return 0;
}

string query_desc(object ob) 
{
 if((int)ob->query_gender() == 1) 
   return("An elfin man.\n");
 return("An elfin lady.\n");
}

int query_dark(int i)
{
  if(i<5 || i>180) return 1;
  return 0;
}
