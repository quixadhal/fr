#include "tweaks.h"

mixed spell(string str, int cast);

/* Power word Die.
   Made by Baldrick June 1993.
   Mods for FR jan '95, by the same nerd.
   Uses saving throw to balance the spell. But it should be *very* high level
   To get it: Kill the Deathmaster
   Have fun with it.

   Modified Taniwha 7/2/95 , players had too little chance
      also can't kill undead now
*/
int savehb;
object my_player;

string help() 
  {
  return
    "This spell kills the one you use it at, if the victim is powerful enough "+
   ",or attacks you, "+
   "is already dead, or has death resistance, "+
    "it may survive.\n\n";
  }
 
int cast_spell(string str) 
  {
  mixed ret;
   my_player = this_player();
 
  str = (string)this_player()->expand_nickname(str);
  ret = spell(str, 1);
  if (stringp(ret)) 
    {
    notify_fail(ret);
    return 0;
    }
  return 1;
  }
 
mixed spell(string str, int cast) 
  {     
  mixed ob;
  int skill;
  int check;
  int cost;

  cost = PWK_COST;

   if(this_player()->query_hb_diff(savehb) < PWK_LOCKOUT) return "You cannot cast this spell now!\n";
   savehb = this_player()->query_hb_counter();
  if (!str || str == "")
    return "You shout but there is no target for it.\n";
  ob = find_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    return "Who is " + capitalize(str) + "?\n";
  if (!living(ob))
    return ("Why kill a dead object ?.\n");

  if (ob->query_creator())
    return ("You don't think it is wise to kill an immortal.\n");
  if (ob->query_property("dead") )
    return (string)ob->query_cap_name() + " is already dead.\n";

  if (cast && (int)this_player()->adjust_gp(-cost) < 0)
    return "Too low on power.\n";

  if( ob->query_property("undead") )
  {
     ob->attack_by(this_player());
     write("Oops, undead don't die that easilly !.\n");
  }
/* here is the "saving throw" I'm trying out */

    if((random((int)this_player()->query_level() 
        * (int)this_player()->query_wis() + 5))
        < ((int)ob->query_level() * (int)ob->query_wis() 
         ))
    {
      ob->adjust_gp(-(cost/3));
      tell_object(ob, "You hear " + (string)this_player()-> query_cap_name() +
         " whisper to you.\n");
      this_player()->attack_ob(ob);
      return ("Your word comes out only as a whisper.\n");
    }
    write("You call upon the gods to help you kill " + 
         ob->query_cap_name() + ".\n");
    say(((string)this_player()->query_cap_name() + " shouts: DIE " +
        (string)ob->query_cap_name() + "!\n"));
    call_out("do_kill",PWK_CALLOUT,ob);
    return 1;
}

int do_kill(object ob)
{
// if(present(ob,my_player) && (member_array(my_player,ob->query_attacker_list()) == -1))
   if(member_array(my_player,ob->query_attacker_list()) == -1)
    {
       tell_object(ob, "You feel " + (string)my_player->query_cap_name() +
         "'s word attack you.\n\nThe powerword killed you.\n\n");
       ob->do_death(this_player());
    }
    return 1;
}


