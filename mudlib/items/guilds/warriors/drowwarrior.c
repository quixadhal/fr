inherit "/std/guilds/warrior";

void setup() {
   set_name("drow_warrior");
   set_short("drow warrior");
   set_long(
      "The Drow Warriors guild teaches one how to be sneaky and deadly " +
      "at the same time.  It gives you skills that relate to finding " +
      "out how good a weapon or armour is at much lower costs, also " +
      "you can sneak and hide like the rogues.  Always remember that a " +
      "dagger in the back will cramp any wizards style.\n");
   reset_get();
   add_guild_command("slice",1);
   add_guild_command("judge", 1);
   add_guild_command("fix", 1);
   add_guild_command("sneak", 1);
   add_guild_command("hide", 1);
}

int query_legal_race(string race)
{
 switch(race)
 {
  case "drow":
  return 1;
  }
}
