#include "animals.h"
#include "unarmed_combat.h"
inherit "/obj/monster";
object my_player;
#include "ranger.h"
void set_my_player(object ranger)
{
   my_player=ranger;
}
void setup()
{
   set_short("Grizzly Bear");
   set_name("Grizzly Bear");
   add_alias("grizzly bear");
   add_alias("bear");
   set_main_plural("Grizzly Bears");
   add_plural("grizzly bears");
   add_plural("bears");
   set_long("This is a large, powerful animal.  "
      "Its dense, brown fur protects it from the elements, and "
      "its powerful claws protects it from other animals.\n");
   set_level(18);
   set_gender(random(2)+1);
   msgin="@Grizzly Bear lumbers in from the $F.";
   msgout="@Grizzly Bear lumbers off to the $T.";
   add_timed_property("just_summoned",1,10);
   set_heart_beat(1);
}
int unarmed_attack(object target, object me)
{
   int i;
   object *att;
   att=(object *)me->query_attacker_list();
      monster::unarmed_attack(att[random(sizeof(att))],me);
      set_damage_dice(1,8);
      monster::unarmed_attack(att[random(sizeof(att))],me);
      set_damage_dice(1,8);
      monster::unarmed_attack(att[random(sizeof(att))],me);
      set_damage_dice(1,12);
}
valid_attack()
{
   int two, four;
   two=random(2);
   four=random(4);
   return([
      "punch"  :({AN+" "+({"swats","slaps",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  "You "+({"swat","slap",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  AN+" "+({"swats","slaps",})[two]+" you on the "+
                  ({"arm","leg","head","chest",})[four]+".\n"}),
      "kick"   :({AN+" "+({"slashes","rends",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  "You "+({"slash","rend",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  AN+" "+({"slashes","rends",})[two]+" you on the "+
                  ({"arm","leg","head","chest",})[four]+".\n"}),
      "knee"   :({AN+" "+({"bites","mangles",})[two]+" "+DN+"'s "+
                  ({"arm","leg","head","chest",})[four]+".\n",
                  "You "+({"bite","mangle",})[two]+" "+DN+"'s "+
                  ({"arm","leg","head","chest",})[four]+".\n",
                  AN+" "+({"bites","mangles",})[two]+" your "+
                  ({"arm","leg","head","chest",})[four]+".\n"})
      ]);
}
