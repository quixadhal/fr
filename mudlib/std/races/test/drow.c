inherit "/std/races/standard";

void setup()
{
  set_long("The drow are a dangerous and devious race.\n");
  set_name("drow");
  reset_get();
}

void start_player()
{
  previous_object()->adjust_bonus_int(2);
  previous_object()->adjust_bonus_dex(2);
  previous_object()->adjust_bonus_con(-1);
}

int query_skill_bonus(int lvl, string skill)
{
  return 0;
}

string query_desc(object ob)
{
 if((int)ob->query_gender() == 1)
   return("A devious dark elven male.\n");
 return("A beautiful yet devious dark elven female.\n");
}

int query_dark(int i) 
{
  if(i<0 || i>90) return 1;
  return 0;
}
