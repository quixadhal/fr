#include "tweaks.h"
/** Ambush.c by Taniwha, with a spot of help from Ilmryn. **/
/** This is a very nasty attack command, designed for the Assassin's guild
    ONLY.  It is made pretty nasty because Assassins are killers, and they 
    are supposed to kill in one shot.  Since we can't do anything that nasty
    here, we decieded on a high damage command that does it's damage with a 
    single attack.  It maybe attempted with any weapon, and the damage is 
    level of the user, divided by 2, times the damage roll of the weapon 
    , and all of this randomized.  The damage multiplier stops going up at
    level 20, for a max multiplier of 10.  While testing it at level 10 the
    damage ranged from 15-30, and at level 30 the damage was around 50.  This
    was ALL well below the damage capable of being done by a wizard of equal
    or lower level.  Also of note is the fact that if the user is listed in
    the attacking list then they suffer damage.  Even if they have stopped,
    but are being hunted by a monster or character for 3 screens ago, they
    get damaged, and obviously fail the ambush.  This should be more than
    adequate balancing for the capabilities of this command.  ****/

int hbdiff;


static int already_attacking(object victim)
{
int i;
   object *list;
   list = (object *)this_player()->query_attacker_list();
   if(sizeof(list)) return 1;
   list = (object *)victim->query_attacker_list();
   for(i = 0; i < sizeof(list); i++)
   {
      if(list[i] == this_player() ) return 1;
   }
   return 0;
}
int ambush_damage(object weapon,object victim)
{
   int lvl;
   int dam;
   dam = (int)weapon->query_damage_roll()+ (int)this_player()->query_damage_bonus();
   lvl = (int)this_player()->query_level();
// tell_object(this_player(),"Weapon damage is "+dam+"\n");
   if(lvl < 4) lvl = 2;
   else if(lvl < 6) lvl = 3;
   else if(lvl < 8) lvl = 4;
   else if(lvl < 10) lvl = 5;
   else if(lvl < 12) lvl = 6;
   else if(lvl < 14) lvl = 7;
  else if(lvl < 16) lvl = 8;
  else if(lvl < 18) lvl = 9;
  else if(lvl < 20) lvl = 10;
  else if(lvl < 22) lvl = 11;
  else if(lvl <24) lvl = 12;
  else if(lvl < 26) lvl = 13;
  else lvl = 14;
  dam = 1+(random(dam*lvl));
   return dam;
}
int ambush(string str) {
   int skill,s1,i;
   int damage;
   object me;
   object *weap;
   object *vlist;
   object victim;

   me = this_player();
   if (!str)
   {
     	   notify_fail("You are you trying to ambush?\n");
      return 0;
   }
if((string)this_player()->query_guild_name() != "assassin") {
write("Ambush is for assassins, you are not that, so the command is hereby removed from you.\n");
this_player()->remove_known_command("ambush");
return 1;
}

   weap = (object *)this_player()->query_weapons_wielded();
   vlist = find_match(str,environment(this_player()));
   if(!sizeof(vlist))
   {
	notify_fail("Fantasizing about ambushing someone?  Try someone that is here.\n");
            return 0;
   }
    victim = vlist[0];
   if(victim == me)
   {
    	notify_fail("Ambushing yourself? that's bright.\n");
      return 0;
   }
/*
   if(this_player()->query_gp() < AMBUSH_COST)
   {
  	notify_fail("You lack the energy to ambush at this time.\n");
      return(0);
   }
*/
if((int)this_player()->adjust_gp( -((int)this_player()->query_level()*2)) == -1) {
write("You don't have enough energy to ambush! Try again later.\n");
return 1;
}
   if(sizeof(weap) > 1)
   {
   tell_object(me,"You try to make your ambush with weapons all wrong for the "+
	"job, and you screw it up severely.\n");
    victim->attack_by(me);
      return 1;
   }
   if(!sizeof(weap))
   {
	tell_object(me,"Ambush with what?\n");
      return 1;
   }
/*
   this_object()->adust_gp(AMBUSH_COST);
*/
   if(this_player()->query_hb_diff(hbdiff) < AMBUSH_LOCKOUT)
   {
      notify_fail("You don't feel calm enough to ambush.\n");
      victim->attack_by(this_player()); /* I MAY remove this later */
      return 0;
   }
   hbdiff = this_player()->query_hb_counter();
         damage = ambush_damage(weap[0],victim);
   if(already_attacking(victim))
   {
      tell_object(me,"Ooops "+(string)victim->query_cap_name()+
	" sees you coming, and turns in time to land a solid blow on you first.\n");
      tell_object(victim," "+(string)me->query_cap_name()+
	" suddenly makes a strange move, and then leaps at you.  You manage "+
	"to spin around in time and land a vicious blow on them.\n");
	me->adjust_hp(-damage/2);
   }
   else
   {
      victim->adjust_hp(-damage);
   tell_object(victim,(string)this_player()->query_cap_name()+" hits you "+
	"totally unexpectedly with a vicious blow.\n");
   tell_object(this_player(),"You catch "+(string)victim->query_cap_name()+
	" flat footed with your ambush "+
   "\n");
   }
 victim->attack_by(this_player());
   return 1;
}

string help(string str) {
  return
"Syntax: ambush <person>\n\n"+
"Ambush is a nastier version of the backstab command.  It takes into account "+
"the assassin's detailed knowledge of the body, and of the art of killing.  "+
"Combining this with the element of surprise, it is deadly.  But because it "+
"takes total concentration, you must be at absolute peace with yourself to "+
"succeed, if not your opponent will mostlikely see you coming, and turn your "+
"attack back upon you.\n";
}
