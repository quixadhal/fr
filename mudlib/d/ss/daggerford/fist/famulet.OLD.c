inherit "/obj/armour";
 
void setup() {
   set_base_armour("amulet");
   set_enchant(-1);
   set_long("This amulet signifies membership in the Band of the "+
       "Silver Fist.  Type 'help amulet' for more info.\n");
   set_short("Amulet of the Silver Fist");
   set_name("fister_amulet");
   add_alias("amulet");
   set_value(0);
   reset_drop();
}
 
void init()
{
  add_action("raise_fist","fraise");
  add_action("band_band","band");
  add_action("band_who","bwho");
 add_action("do_help","help");
   ::init();
}
 
do_help(arg)
{
 if(!(arg))
  return 0;
 if(arg=="amulet")
 {
  write("You may use your amulet to do the following things:\n"+
        "   fraise  : raise your fist on high (The whole mud sees this)\n"+
        "    help   : this screen\n"+
       "    band   : Band <message> sends a message to all other members.\n"+
       "    bwho   : Lists other members of the Band.\n"+
        "Mail Timion with any comments/suggestions.\n");
       return 1;
   }
 else return 0;
}
raise_fist()
{
 write("You feel the strength of Many as you raise your fist on high.\n");
 shout(this_player()->query_cap_name()+" raises his fist in the air. 'Power to the Band of the Silver Fist!'\n");
 say("Power emenates from "+this_player()->query_cap_name());
 return 1;
}
 
band_band(string cows)
{
 object *people;
 int i;
 string ME;
 
 if(!cows)
  {
   write("syntax: band <message>\n");
   return 1;
  }
 ME=this_player()->query_cap_name();
 people=users();
 for(i=0;i<sizeof(people);i++)
  if(sizeof(find_match("fister_amulet",people[i])))
   tell_object(people[i], "[Silver Fist: "+ME+"]  "+cows+"\n");
 return 1;
}
 
 
band_who()
{
 object *people;
 int i;
 string ME;
 
 ME=this_player()->query_cap_name();
 tell_object(this_player(),"**Silver Fist Members: ");
 people=users();
 for(i=0;i<sizeof(people);i++)
  if(sizeof(find_match("fister_amulet",people[i])))
    tell_object(this_player(), people[i]->query_cap_name()+"  ");
  tell_object(this_player(),"**\n");
 return 1;
}
