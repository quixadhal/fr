
#include "tweaks.h"
/* Slice Taniwha 1995
 * An attack specific to drow warriors, since it can be used while IN combat
 * it should do less than backstab or slice
 * It is based on level AND dexterity
 * The number of extra attacks are (DEX / 9)* 3
 * at this stage
 * Frequency of use is (SLICE_LOCKOUT - level)  (SLICE_LOCKOUT noninally 40)
 * Cost is 1 GP/level
 * Use it too soon and you drop your weapons
 */

int savehb;

int slice(string str) {
   int skill,s1,i;
   int j;
   int damage;
   object me;
   object *weap;
   object *vlist;
   object victim;

   me = this_player();
   if (!str)
   {
      notify_fail("You are you trying to slice?\n");
      return 0;
   }

   weap = (object *)this_player()->query_weapons_wielded();
   vlist = find_match(str,environment(this_player()));
   if(!sizeof(vlist))
   {
      notify_fail("Fantasizing about sliceing someone?  Try someone that is here.\n");
      return 0;
   }

   victim = vlist[0];
   if(victim == me)
   {
      notify_fail("Slicing yourself? that's bright.\n");
      return 0;
   }
   if( this_player()->query_hb_diff(savehb) < (SLICE_LOCKOUT - (int)this_player()->query_level() )/2 )
   {
      write("You do not have the skill to slice your opponent so soon.\n");
      return 1;
   }
   savehb = this_player()->query_hp_counter();
   if((int)this_player()->adjust_gp(-SLICE_COST) == -1)
   {
      write("You don't have enough energy to slice! Try again later.\n");
      return 1;
   }
   if(!sizeof(weap))
   {
      tell_object(me,"Slice with what?\n");
      return 1;
   }
   
   tell_object(victim,(string)this_player()->query_cap_name()+" twirls his blades "+
	"and , before you can dodge, attacks.\n");
   tell_object(this_player(),"You dazzle "+(string)victim->query_cap_name()+
	" with your bladework.\n");
   victim->attack_by(this_player());
   for(i = 0; i <((int)this_player()->query_dex() + (int)this_player()->query_level())/SLICE_DIV ; i++)
   {
      weap[0]->weapon_attack(victim,this_player());
//    if(weap[1]) weap[1]->weapon_attack(victim,this_player());
   }
   return 1;
}

string help(string str) {
  return
"Syntax: slice <person>\n\n"+
"Slice is a Drow Warrior attack based on their skill with bladework. "+
"The higher the level, and the higher the dexterity, the more damage "+
"you will do. "+
   "\n";
}

