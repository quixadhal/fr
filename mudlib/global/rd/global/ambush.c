/* PLEASE COMMENT ALL CHANGES
 * - changed this_player(1) to this_player(), hoping it will fix the 
 *   problem in debug.log - Lotus

 */

#define MIN_LVL 1
#define AMBUSH_COST 60
#define STEALTH "other.covert.stealth"
#define HIDDEN_BONUS 100
#define TEACH_LEVEL 60
#define LEARN_LEVEL 40
 
 
int already_attacking(object hunter,object ob)
{
   int i;
   object *olist;
   olist = (object *)ob->query_attacker_list();
// tell_object(hunter,(string)ob->query_name()+" "+sizeof(olist)+"\n");
   for(i = 0; i < sizeof(olist); i++)
   {
//        tell_object(hunter,(string)olist[i]->query_name()+"\n");
      if(hunter == olist[i]) return 1;
   }
   return 0;
}

int ambush(string str) {
  int skill, level, mul, i, percent;
  object weap, *weaps, ambusher, *obs, *using;
  string sname, mess;
 
  ambusher = this_player();

  /* a check to see what is happening with ambush 
  if (this_player(1) != ambusher)
  {
     notify_fail("The Ambush command cannot be forced upon you.\n");
     return 0;
  }
  */
 
  if(!str) {
    notify_fail("Usage: ambush <person>\n");
    return 0;
  }

  level = (int)ambusher->query_skill(STEALTH);
  skill = (int)ambusher->query_skill_bonus(STEALTH);
  if(ambusher->query_hide_shadow()) skill += HIDDEN_BONUS;
 
 
  if (level < MIN_LVL) {
    write("You are level "+level+" in this skill, and you need "+
      MIN_LVL+".\n");
    write("You are not stealthy enough to even try such a risky combat
maneuver.\n");
    return 1;
  }

  weaps = (object *)ambusher->query_weapons();
  using = (object *)ambusher->query_holding();

/* We will only use the first one... */
  if (!sizeof(weaps)) {
    weap = ambusher;
    percent = 100;
  } else {
    weap = using[0];
    if(!weap) { weap = using[1]; }
    if(!weap) { weap = ambusher; }
    percent = 100;
  }

  skill += (int)weap->query_property("ambush bonus");
  sname = (string)weap->query_weap_skill();
  switch(sname) {
    case "fighting.combat.melee.sharp":
      mess = "impale";
      break;
    case "fighting.combat.melee.blunt":
      mess = "cosh";
      break;
    case "fighting.combat.melee.unarmed":
      mess = "pinch";
      break;
    default:
      write("You cannot ambush with that type of weapon.\n");
      return 1;
  }
  obs = find_match(str, environment(ambusher));
 
 
     // Little fix by Inkblot (the obs[0])
  if ((!sizeof(obs)) || (obs[0]->query_hide_shadow())) {
    write("You're seeing things, there's no-one here called that.\n");
    return 1;
  }

  if(sizeof((object *)ambusher->query_attacker_list())) {
    write("You can't sneak up behind people in the heat of battle!\n");
    return 1;
  }

  if((int)ambusher->adjust_gp(-AMBUSH_COST) == -1) {
    write("You lack sufficient guild points to Ambush at the moment.\n");
    return 1;
  }

   if(already_attacking(ambusher,obs[0]))
   {
      tell_object(ambusher,"You can't ambush "+obs[0]->query_cap_name()+" again.\n");
      return 1;
   }

  if((string)obs[0]->query_name() == (string)ambusher->query_name()) {
    write("Dumb move.\n");
  say(ambusher->query_cap_name()+" ambushes "+
    ambusher->query_objective()+
    "self.  How stupid.\n", obs[0]);
    weap->weapon_attack(obs[0], ambusher, percent);
    weap->weapon_attack(obs[0], ambusher, percent);
    weap->weapon_attack(obs[0], ambusher, percent);
    weap->weapon_attack(obs[0], ambusher, percent);
    return 1;
  }

  if(!living(obs[0])) {
    write("Trying to ambush "+add_a(obs[0]->query_short())
     +" will get you nowhere, and you would look silly anyway.\n");
    return 1;
  }

  write("You " + mess + " "+obs[0]->query_name()+".\n");
  mess = pluralize(mess);
  say(ambusher->query_cap_name()+" " + mess + " "+
      obs[0]->query_name()+".\n", obs[0]);
  tell_object(obs[0], ambusher->query_cap_name()+ " " + mess + " you.\n");
  obs[0]->attack_by(ambusher);
  ambusher->attack_by(obs[0]);
  weap->weapon_attack(obs[0], ambusher, skill);
  return 1;
}
 
 
string help(string str) {
  return "Syntax: ambush <person>\n\n"+
"The ambush action gives a bonus to your first attack equal to your skill in "
+
STEALTH + ". This bonus can only be applied to melee weapons (or unarmed " +
"combat) " +
"To ambush you must not be in combat yourself (though your target may be). " +
"Also, being hidden when you ambush gives a +" + HIDDEN_BONUS +
" bonus to this action.\n" +
"Example:\n" +
"> wield club\n" +
"> ambush thief\n" +
"You cosh thief.\n\n";
}
