inherit "/std/races/standard";

void setup() 
{
  set_long("A half-elf is part elf, part human.\n");
  set_name("half-elf");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_dex(1);
  previous_object()->adjust_bonus_con(-1);
}

int query_skill_bonus(int lvl, string skill) 
{
  if (skill == "dex.stealth")
    return 20;
  return 0;
}

string query_desc(object ob) 
{
 switch((int)ob->query_gender())
 {
   case 1 : return("A half-elfin man.\n");
   case 2 : return("A half-elfin lady.\n");
   case 3 : return("A bisexual half-elf.\n");
   default: return("An non-sexual half-elf.\n");
 }
}
 
int query_dark(int i)
{
  if(i<20 || i>190) return 1;
  return 0;
}
