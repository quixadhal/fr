
/* Rage '94 - disarm cmd for fighters */
/* Redone '95, Rage */

#include "tweaks.h"

string help()
{
  return "\nSyntax: disarm <target>\n"
    "Cost: "+GPCOST_DISARM+" Gp\n"
    "Duration: Needs "+HBLOCKOUT_DISARM+" heartbeats to restore power.\n"
    "     When you disarm a target, you will try to reach out and grab your "
    "target's weapon. If your target is not holding any weapons, nothing will "
    "happen. If your target is holding two weapons, you can only grab one "
    "weapon at a time.\n"
    "     You can both disarm during combat with your target, "
    "and also before fighting your target. Even should you succeed "
    "in disarming a target you are not fighting with, your target will "
    " attack you, the weapon falling to the ground. If you fail to disarm a "
    "target you are not fighting with, there is a large chance that the "
    "target will attack you, seeing what you were trying to do. If you "
    "succeed in disarming, there is a little chance of the weapon being "
    "destroyed by the disarm. This will happen because the weapon is "
    "dragged out of the target's hands so tremendously hard that the "
    "weapon is crushed into the ground.\n"
    "     If your hitpoints are below half of your maximum, you will be too "
    "tired to disarm.\n"
    "     Chance of success is based upon you and your target's strength, "
    "dexterity, level, and a random bonus. A strong and quick person will be "
    "better at disarming than a weak and slow person.\n";
}

int chance(object me,object ob);

int disarm(string str,object x)
{
  object *ob, tar;
  int i;
  int hold;
  object *fuk;
  int cnt;
  object me;

  if(x) 
    me = x;
  else 
    me = this_player();

  hold = 0;    /* gets set to 1 in the loop if target holds any weapons */

  if (!str) 
  {
    tell_object(me,"Disarm whom?\n");  /* no string, no dude */
    return 1;
  }

  str = lower_case(str);
  str = (string)me->expand_nickname(str);

  if (str == ((string)me->query_name())) 
  {
    tell_object(me,"You dare not disarm yourself.\n");
    return 1;
  }

  fuk = find_match(str, environment(me));
  for (cnt = 0; cnt < sizeof(fuk); cnt++)
    if (((int)fuk[cnt]->query_level() > 0) && living(fuk[cnt]))
    {
      tar = fuk[cnt];
      break;
    }

  if (!tar) 
  {
    tell_object(me,capitalize (str)+ " is nowhere to be seen.\n");
    return 1;
  }

  if ((int)me->query_timed_property("dis") == 1)
  {
    tell_object(me,"The tactical part of your brain needs a bit of "
      "recovery before you can disarm\nanyone again.\n");
    return 1;
  }
  if ((int)me->query_gp() < GPCOST_DISARM) 
  {
    tell_object(me,"Sorry, not enough guildpoints to disarm.\n");
    return 1;
  }
  if ((int)me->query_hp() < (int)me->query_max_hp() / 2)
  {
    tell_object(me,"You are too tired to disarm.\n");
    return 1;
  }

  if ( tar->query_creator() )
  {
    tell_object(me, "Disarming an immortal would not be wise.\n");
    return 1;
  }
  ob = (mixed *) tar->query_held_ob();

  for (i=0; i<sizeof(ob); i++) 
    if ((int)tar->is_weapon(ob[i]) == 1)
    {
      me->adjust_gp(-(GPCOST_DISARM));
      me->add_timed_property("dis", 1, HBLOCKOUT_DISARM);
      if (chance(me,tar) == 1)
      {             /* success */
        tell_object(me,"You strike "+ tar->query_cap_name()+ "'s "+
          ob[i]->query_short()+ " to the ground.\n");
        tell_room(environment(tar), me->query_cap_name()+ " strikes "+
          tar->query_cap_name()+ "'s "+
          ob[i]->query_short()+ " to the ground.\n", ({ tar, me }));
        tell_object(tar, me->query_cap_name()+ " strikes your "+  
          ob[i]->query_short()+ " to the ground.\n");
  
        if (random(100) > 94)
        {
          tell_object(me,capitalize (ob[i]->query_short())+ " is destroyed "
            "by the blow!\n");
          tell_room(environment(tar),capitalize (ob[i]->query_short())+ 
            " is destroyed by the blow!\n", ({tar, me }));
          tell_object(tar,capitalize (ob[i]->query_short())+ 
            " is destroyed by the blow!\n");
          ob[i]->dest_me();
        }
        else
          ob[i]->move(environment(tar));
  
        hold = 1;
        break;
      }
      else 
      {                   /* failure */
        tell_object(me,"You fail to strike "+ tar->query_cap_name()+ "'s "+
          ob[i]->query_short()+ " to the ground.\n");
        tell_room(environment(tar), me->query_cap_name()+ " fails to strike "+
          tar->query_cap_name()+ "'s "+
          ob[i]->query_short()+ " to the ground.\n", ({ tar, me }));
        tell_object(tar, me->query_cap_name()+ " fails to strike your "+  
          ob[i]->query_short()+ " to the ground.\n");
        hold = 1;
        if (random(100) > 50) 
        {
          tell_object(me, tar->query_cap_name()+ " gets mad and attacks.\n");
          tar->attack_by(me);
        }
        break;
      }
    } /* end if, for */

  if (hold != 1) 
  {    /* ooops, your target wasn't holding any weps */
    tell_object(me,tar->query_cap_name()+ " is not holding any weapons.\n"); 
    return 1;
  }
  else if ( !interactive(tar) )
    tar->attack_by(me);

  return 1;

}


int chance(object me,object ob)
{
  int def, att;

  if ( ob->query_property("nodisarm") )
    return 0;

  att = ((int)me->query_str() * 2);
  att += (int)me->query_dex();
  att += ((int)me->query_level() + random(10));

  def = ((int)ob->query_dex() * 2);
  def += (int)ob->query_str();
  def += ((int)ob->query_level() + random(10));

  if (def > att + 10) 
    ob->adjust_xp(50);
  if (att > def + 10) 
    me->adjust_xp(50);

  if (def > att + 20) 
    ob->adjust_xp(50);
  if (att > def + 20) 
    me->adjust_xp(50);

  if (att > def) 
    return 1;
  else 
    return 0;

}
