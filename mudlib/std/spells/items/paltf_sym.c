
inherit "/std/object.c";


void setup()
{
  set_name("holy symbol");
  add_alias("cross");
  set_short("Silver Cross");
  set_long("\nSilver Cross\n\n"
     "     This is a small silver cross that radiates purity and "
     "goodness wherever it goes.  As you take a closer you look "
     "you begin to wonder what mysterious powers this tiny cross "
     "holds...\n\n");
  set_read_mess("One must look inside to find Salvation.\n\n");
  set_value(0);
  set_weight(100);
  add_property("faith","paladin");
  reset_drop();
}

void find_tower(string str)
{
 object *tower;
 int i;
 int p_lev;
 int gps;
 p_lev = this_player()->query_level();
 gps = this_player()->query_gp();
  if(!str)
   {
    write("Stare at what?\n\n");
    return 1;
   }
  if((this_player()->query_guild_name() != "paladin") && (str == "cross"))
  {
   write("A small dragon comes and snatches the skull from your "
     "hands saying:  You're not a Lord :P\n\n");
   write("The dragon blows some fire at you for good measure.\n\n");
   this_player()->adjust_hp(-20);
   this_object()->dest_me();
   return 1;
  }
 if((p_lev < 20) && (str == "cross"))
  {
  write("You are too inexperienced to use the powers of the skull.\n\n");
  return 1;
  }
 if((gps < 105) && (str == "cross"))
  {
   tell_object(this_player(), "You are too tired to use your "
    "tower finding ability...\n\n");
   return 1;
  }
 tower = children("/d/omiq/towers/goodtow");
 for(i=0;i<sizeof(tower);i++)
   if((environment(tower[i])) && (str == "cross"))
   {
    tell_object(this_player(), "You stare intently at the "
     "Silver Cross.  As you focus all of your energy on the "
     "tiny cross an image appears before you...\n\n"
      ""+environment(tower[i])->query_long()+"\n\n"
     "You feel drained...\n\n");
    this_player()->adjust_gp(-100);
   return 1;
   }
 else return 0;
}

void init()
{
 add_action("find_tower", "stare");
 ::init();
}
