#include "tweaks.h"

 
mixed spell(string str, int cast);

/* Finger of Death.
   Made by Baldrick June 1993.
   Mods for FR jan '95, by the same nerd.
   Uses saving throw to balance the spell. But it should be *very* high level
   To get it:
   Have fun with it.
*/
int savehb;
object my_player;

string help() 
  {
  return
    "This spell kills the one you manage to touch, if the victim is powerful " +
    "enough it may survive.\n\n";
  }
 
int cast_spell(string str) 
  {
  mixed ret;
 
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
  int achit, THAC0, defenderac, result;

  if (!str || str == "")
    return "You wave you hands in the air trying to touch nothing.\n";
  ob = find_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    return "Who is " + capitalize(str) + "?\n";
  if (!living(ob))
    return ("Why kill a dead object ?.\n");
  if (ob->query_creator())
    return ("You don't think it is wise to kill an Immortal.\n");
  if (ob->query_property("dead"))
    return (string)ob->query_cap_name() + " is already dead.\n";
   my_player = this_player();

   if(ob->query_property("undead"))
   {
      ob->attack_by(this_player());
      return("Oops !\n");
   }
  if( this_player()->query_hb_diff(savehb) < FD_LOCKOUT )
  {
     ob->attack_by(this_player());
     return "You can't cast this spell yet";
  }
  savehb = this_player()->query_hb_counter();

  if (cast && (int)this_player()->adjust_gp(-FD_COST) < 0)
    return "Too low on power.\n";

  
/* here is the "saving throw" I'm trying out 
 * First, does the wizard manage to touch the victim?
 */
      /* the AC the attacker will hit. */

   THAC0 = (int)this_player()->query_thac0();
   achit = (THAC0 - (int)this_player()->query_level() - roll(1,20));
   defenderac = ((int)ob->query_total_ac() -
                (int)ob->extra_bonus("defend") - (int)ob->query_level());

   result = (achit - defenderac);
   if (result > 0)
    {
    ob->adjust_gp(-(FD_COST/3));
    tell_object(ob, "You notice " + (string)this_player()-> query_cap_name() +
      " grabs after you, but misses.\n");
    this_player()->attack_ob(ob);
    return ("You try to reach for your victim, but misses.\n");
    }
     tell_object(my_player,"You touch and attempt to kill " + 
         ob->query_cap_name() + ".\n");
    call_out("do_kill",FD_DELAY,ob);
}  
int do_kill(object ob)
{
   if( member_array(my_player,ob->query_attacker_list()) == -1)
  {
    tell_room(environment(ob),(string)my_player->query_cap_name() + " touches " +
     (string)ob->query_cap_name() + " and the poor victim dies\n");
    tell_object(ob, "You feel a tingling sensation as " + (string)my_player->query_cap_name() +
    " touches you.\n\n");
     ob->do_death(my_player);
  }
  return 1;
}


