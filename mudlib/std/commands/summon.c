#include "animals.h"
inherit "/std/object";
int summon(string str, object me)
{
   int cost, min_level;
   int animal_hp, animal_gp;
   int wis_bonus;
   string ANIMAL;
   object animal, shadow, ob;
   if(!me) me=this_player();
   if(me->query_timed_property("KILLED_OWN_ANIMAL"))
   {
      notify_fail("No animals will hear your calls.  They all seek "
         "to hide from you as though you were a common person.\n");
      return 0;
   }
   if(me->query_alignment()>1000)
   {
      notify_fail("Mielikki grants no power to those whom are evil.\n");
      return 0;
   }
   switch(str)
   {
      case "weasel":
         min_level=3;
         cost=5;
         ANIMAL=WEASEL;
         animal_hp=4;
         animal_hp=4;
         break;
      case "hawk":
         min_level=6;
         cost=10;
         ANIMAL=HAWK;
         animal_hp=4;
         animal_gp=4;
         break;
      case "wolf":
         min_level=9;
         cost=15;
         ANIMAL=WOLF;
         animal_hp=6;
         animal_gp=6;
         break;
     case "boar":
         min_level=12;
         cost=20;
         ANIMAL=BOAR;
         animal_hp=6;
         animal_gp=6;
         break;
      case "tiger":
         min_level=15;
         cost=25;
         ANIMAL=TIGER;
         animal_hp=8;
         animal_gp=8;
         break;
      case "bear":
         min_level=18;
         cost=30;
         ANIMAL=BEAR;
         animal_hp=10;
         animal_gp=10;
         break;
      default:
         cost=-1;
         break;
   }
   if(me->query_level()<min_level)
   {
      notify_fail("You can't summon that type of animal.\n");
      return 0;
   }
   if(cost==-1)
   {
      notify_fail("You can't summon that type of animal.\n");
      return 0;
   }
   if(me->query_gp()<cost)
   {
      notify_fail("You are a bit too weary to summon that animal "
         "right now.\n");
      return 0;
   }
   if(sizeof(me->query_attacker_list()))
   {
      notify_fail("Things are a little too hot now to summon animals.\n");
      return 0;
   }
   if(!environment(me)->query_outside())
   {
      notify_fail("There are no animals around to summon right now.\n");
      return 0;
   }
   if(me->query_static_property("animal_summoned"))
   {
      notify_fail("You can only control one animal at a time.\n");
      return 0;
   }
   wis_bonus=(me->query_wis()-15)*me->query_level();
   if(wis_bonus<0)
      wis_bonus=-(me->query_level());
   me->adjust_gp(-cost);
   if(!file_exists(ANIMAL))
   {
      notify_fail("Summon WHAT ????\n");
      return 0;
   }
   me->add_static_property("animal_summoned",1);
   animal=clone_object(ANIMAL);
   animal->move(environment(me));
   animal->set_my_player(me);
   animal->set_max_hp(roll(me->query_level(),animal_hp)+wis_bonus);
   animal->set_max_gp(roll(me->query_level(),animal_hp)+wis_bonus);
   animal->set_thac0(me->query_thac0());
   ob=clone_object(OBJECT);
   ob->move(me);
   ob->animal_setup(me,animal,animal_hp,animal_gp);
   animal->set_hp(animal->query_max_hp());
   animal->set_gp(animal->query_max_gp());
   tell_room(environment(me),me->query_cap_name()+" calls "+me->query_possessive()+
      animal->query_short()+" to "+me->query_possessive()+" side.\n",
      me);
   write("You call you "+animal->query_short()+" to your side.\n");
   return 1;
}
string help()
{
   return
      "Animal  Level  GP  Offense  Defense  HP's  Special\n"
      "Weasel    3    5   *        ***      *     None (Can not protect)\n"
      "Hawk      6    10  **       ***      *     Blind (Can not protect)\n"
      "Wolf      9    15  **       *        **    None\n"
      "Boar      12   20  ***      *        **    None\n"
      "Tiger     15   25  ***      **       ***   Hard to Surprise\n"
      "Bear      18   30  ****     **       ****  Bearhug\n"
      "\n"
      "Valid Orders:  syntax:  order <animal> to <command> <target>\n"
      "bearhug/release (only bears can bearhug)\n"
      "follow/unfollow\n"
      "kill\n"
      "protect/unprotect (weasels and falcons are too small to protect)\n"
      "stop\n"
      "\n";
}
