// Ranger guild ob .. hacked from Timion guild ob
// TEMP - Radix, Jan 1996

inherit "/std/guild";

int query_skill_cost(string skill)
{
 return 0;  /* Need a list of possible skills first.  Awaiting Dank */
}
int query_legal_race(string str)
{
   switch("race")
   {
      case "orc":
      case "goblin": 
      return 0;
   }
   return 1;
}
int query_legal_armour(string type)
{
   switch(type)
   {
      case "fullplate":
      return 0;
   }
   return 1;
}

void setup() 
  {
  set_name("ranger");
  set_short("Ranger");
  set_long(
      "Fleet of foot and abnormally wise, Rangers are one with the "
      "forest and its inhabitants.  Kind of heart but extremely "
      "antisocial, Rangers are proficient with most weapons and "
      "armours and have many skills in hunting and tracking their "
      "foes.  Pity the enemy found in a Ranger's homeland "
      "forest, for he shall regret ever crossing his path.\n");
  reset_get();
  add_guild_command("fix", 1);
  add_guild_command("track",1);
   add_guild_command("slip",1);
   add_guild_command("hide",1);
   add_guild_command("sneak",1);
   add_guild_command("scout",1);
   add_guild_command("disappear",1);
   add_guild_command("hunt",1);
  set_main_skill("wis");
}

int query_advance_cost() { return  500; }
int query_xp_cost()      { return 2000; }
int query_dice()         { return 10;   }
int query_thac0_step()   { return 6;    }
int query_extr_str()    { return 1;    }

/* What the hell is this?
 
void init()
{
 this_player()->adjust_tmp_tohit_bon(this_player()->query_tmp_tohit_bon());
 this_player()->adjust_tmp_damage_bon(this_player()->query_tmp_damage_bon());
 this_player()->adjust_tmp_ac_bon(this_player()->query_tmp_ac_bon());
 ::init();
}
*/
