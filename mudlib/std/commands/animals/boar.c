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
   set_short("Wild Boar");
   set_name("Wild Boar");
   add_alias("wild boar");
   add_alias("boar");
   set_main_plural("Wild Boars");
   add_plural("wild boars");
   add_plural("boars");
   set_long("This animal closely resembles a domesticated hog, but is "
      "obviously not as docile.  It has a slightly shorter snout, "
      "course, dark hair,a strait tail, and short tusks.\n");
   set_level(12);
   set_gender(random(2)+1);
   msgin="@Wild Boar rushes in from the $F.";
   msgout="@Wild Boar rushes out to the $T.";
   add_timed_property("just_summoned",1,10);
   set_heart_beat(1);
   set_damage_dice(3,4);
}
valid_attack()
{
   int two, four;
   two=random(2);
   four=random(4);
   return([
      "punch"  :({AN+" "+({"head butts","tripps",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  "You "+({"trounce","trip",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  AN+" "+({"trounces","tripps",})[two]+" you on the "+
                  ({"arm","leg","head","chest",})[four]+".\n"}),
      "kick"   :({AN+" "+({"slashes","tramples",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  "You "+({"slash","trample",})[two]+" "+DN+
                  " on the "+({"arm","leg","head","chest",})[four]+
                  ".\n",
                  AN+" "+({"slashes","tramples",})[two]+" you on the "+
                  ({"arm","leg","head","chest",})[four]+".\n"}),
      "knee"   :({AN+" "+({"bites","kicks",})[two]+" "+DN+"'s "+
                  ({"arm","leg","head","chest",})[four]+".\n",
                  "You "+({"bite","kick",})[two]+" "+DN+"'s "+
                  ({"arm","leg","head","chest",})[four]+".\n",
                  AN+" "+({"bites","kicks",})[two]+" your "+
                  ({"arm","leg","head","chest",})[four]+".\n"})
      ]);
}
