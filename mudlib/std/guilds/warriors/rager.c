inherit "/std/guilds/warrior";

void setup() 
   {
   set_name("battlerager");
   set_short("Battle Rager");
   set_long(
"Battle ragers are fierce Duergar warriors.  Trained to tap "+
"into primal rage and let it lose in battle, ignoring pain and attacking "+
"friend or foe.  Only a Duergar can be a Battle Rager.\n\n");
   reset_get();
   add_guild_command("judge", 1); 
  add_guild_command("focus", 1);
   add_guild_command("fix", 1);
  add_guild_command("berserk",1);
}
 
 
int query_legal_race(string race) {
switch(race) {
  case "duergar" :
     return 1;
  default :
    return 0;
  }
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
