// Temporary 'no new' for sites until actual 'lib can be fixed.
// Radix 
// 2-21-95
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
   string ip = query_ip_number(this_player());
   if(ip[0..13] == "128.118.145.80")
   {
   write("Sorry, your site has now been site baned until further notice.\n "+
      "email mudadm@castle.hiof.no if you have any complaints"+
       "\n\n");
    this_player()->quit();
   return(1);
   }
}
