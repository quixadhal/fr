inherit "/std/object";

void setup()
{
   set_name("");
   set_short("");
   add_alias("ban");
   set_long("To ban assholes in /room/raceroom\n\n");
   reset_get();
}
void init()
{
   add_action("do_it","*");
}
void do_it(string x)
{
   if(query_ip_name(this_player()) == "fhsuvm.fhsu.edu"
      || query_ip_name(this_player()) == "tigr1.fhsu.edu")
   {
      this_player()->quit();
      return(1);
   }
}
