
inherit "/std/guilds/rogue";
 
void setup() {
  set_name("thief");
  set_short("Thief");
  set_long("The thieves guild is a guild for thieves,  it gives you "+
           "skills suitable for relieving other people of things they no "+
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

string query_main_skill()
  {
  return "str";
}
