
inherit "/std/guilds/rogue";
 
void setup() {
  set_name("thief");
  set_short("Thief");
  set_long("The thieves guild is a guild for thieves,  it gives you "
           "skills suitable for relieving other people of things they no "
           "longer require.\n");
  reset_get();
/*
  add_guild_command("assess", "/std/commands/assess", "assess");
*/
  add_guild_command("palm", 1);
  add_guild_command("sneak", 1);
  add_guild_command("hide", 1);
  add_guild_command("slip", 1);
   add_guild_command("backstab",1);
  add_guild_command("steal", 1);
   add_guild_command("peek",1);
   add_guild_command("disappear",1);
} /* setup() */

int query_legal_armour(string arm)
{
   switch(arm)
   {
   case "leather":
   case "studded leather":
   case "studded":
   case "elfin chain":
   case "cloak":
   case "amulet":
   case "gloves":
   case "boots":
   case "bracers":
  case "buckler":
  case "small shield":
  case "wooden shield":
  case "cowl":
   case "ring":
   return 1;
   default:
   return 0;
   }
}
int query_legal_weapon(string wep)
{
   switch(wep)
   {
   case "twohandedsword":
      return 0;
   default: return 1;
   }
}
string query_main_skill()
  {
  return "dex";
}
