#include "tweaks.h"
/* Hide in shadows.
   Finally screwed Taniwha 1995
*/
#define HIDE_SKILL 20
#define COST HIDE_COST
#define SHADOW "/std/commands/shadows/hide"

int hide_in_shadows(string str,object hider)
{
  int sk_bon;
object me;
  object ob;

  if(hider) me = hider;
  else me = this_player();

  if ((int)me->query_gp() < COST)
  {
    tell_object(me,"Not enough guild points to hide.\n");
    return 1;
  }
  if ( sizeof( me->query_attacker_list() ) )
  {
    tell_object(me,"You cannot hide in the middle of a fight!\n");
    return 1;
  }
  me->adjust_gp(-COST);
  sk_bon = (int)me->query_level();

  if (sk_bon > random(HIDE_SKILL) && !me->query_hide_shadow())
  {
        /* they succeeded. */
        ob = clone_object(SHADOW);
        ob->setup_shadow(me);
   }
  tell_object(me,"You try to hide in the shadows.\n");
  return 1;
}

string help()
  {
  return "Syntax: hide\n\nAllows you to hide in shadows.  This allows "
    "you to escape glancing eyes. Success is based upon your level "
    "and it costs "+ COST +" guild points regardless of success or failure."
    "\n\nExample:\n> hide\nYou try to hide in the shadows.\n\nSee also: "
    "sneak.\n";
}

