inherit "/std/races/standard";

void setup() 
{
  set_long("A green-scaled lizard-man.\n");
  set_name("lizard-man");
  reset_get();
}

void start_player() 
{
  previous_object()->adjust_bonus_dex(2);
  previous_object()->adjust_bonus_str(1);
  previous_object()->adjust_bonus_int(-2);
  previous_object()->adjust_bonus_wis(-1);
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
   case 1 : return("A lizard-man.\n");
   case 2 : return("A lizard-woman.\n");
   case 3 : return("A bisexual lizard-man.\n");
   default: return("An asexual lizard-man.\n");
 }
}

int query_dark(int i)
{
 if(i<40 || i >200) return 1;
 return 0;
}

