inherit "/std/guilds/warrior";

void setup() 
   {
   set_name("fighter");
   set_short("Fighter");
   set_long(
      "The Warriors guild teaches one principle of survival:  beating " +
      "people to a pulp!  It gives you skills that relate to finding " +
      "out how good a weapon or armour is at much lower costs than " +
      "other wimpy guilds, like the wizards.  Warriors hack and slash " +
      "their way through life, and do not appear to be much good at " +
      "anything else.\n");
   reset_get();
   add_guild_command("judge", 1); 
  add_guild_command("focus", 1);
   add_guild_command("fix", 1);
  add_guild_command("berserk",1);
}
 
 
void init()
{
  ::init();
 if(this_player()->query_property("flipped"))
 {
  write("You are still berserk!");
  this_player()->adjust_gp((int)(this_player()->query_property("flipped")));
  this_player()->remove_property("flipped");
  this_player()->do_force_on_me("berserk");
 }
}
