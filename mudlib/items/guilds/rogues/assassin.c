inherit "/std/guilds/rogue";
 
void setup() {
  set_name("assassin");
  set_short("Assassin");
  set_long("The assassin guild gives you good thief skills, specially "+
           "designed to kill fast.  You'll also get to know a bit about "+
           "poisons at higher levels. There is "+
           "but a few rules to follow for the guild and those are "+
           "posted on the board.\n");
  reset_get();
  add_guild_command("sneak", 1);
  add_guild_command("hide", 1);
  add_guild_command("slip", 1);
  add_guild_command("judge", 1);
  add_guild_command("ambush", 1);
  set_main_skill("dex");
}
