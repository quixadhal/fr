/* Ambush.
 * Made by someone. Fixed to work with "new" FR by Baldrick, aug '94.
 * Cost should not be fixed. Need a smart method to calc it.
 */
/*Cost increased allong with damae.  This is to make the guilds using
this command more competetive and more AD&D true.  Gonna start trying to
to come up with a good formula for the cost of this puppy. ilmryn 9-29-94 */

#define COST 5 //cost increasted to compinsate for some for increased damage
		//done by the command. was a 3 ilmryn 9-29-94
#define HIDDEN_BONUS 10 

int ambush(string str) 
  {
  int skill, mul, i;
  object  ambusher, *obs;
  mixed *weap;
  string sname, mess;

  ambusher = this_player();

  if(!str) {
    notify_fail("Usage: ambush <person>\n");
    return 0;
  }
//change it so they got a double bonus for level, this is to make it more even 
//with the spell casting guilds that do upwards of 70-80 points of damage
//with a single spell.
skill = (random((int)ambusher->query_level() * 2)) + (int)ambusher->query_dex();;
  if(ambusher->query_hide_shadow()) skill += HIDDEN_BONUS;

  weap = (object)ambusher->query_weapons_wielded();
  if(!weap)
    sname = "unarmed";
   else 
    sname = (string)weap[0]->query_attack_type_name();

  switch(sname) 
    {
	case "slashing":
	  mess = "backstab";
	  break;
	case "pierce":
	  mess = "backstab";
	  break;
    case "sharp":
      mess = "backstab";
      break;
    case "blunt":
      mess = "cosh";
      break;
    case "unarmed":
      mess = "spock pinch";
      break;
    default:
      write("You cannot ambush with that type of weapon.\n");
      return 1;
    } /* switch */

  obs = find_match(str, environment(ambusher));

  if (!sizeof(obs)) 
    {
    write("Ambush whom?\n");
    return 1;
    }
  if(sizeof((object *)ambusher->query_attacker_list())) 
    {
    write("You can't sneak up behind people in the heat of battle!\n");
    return 1;
    }
  if((int)ambusher->adjust_gp(-COST) == -1) 
    {
    write("You lack sufficient guild points to Ambush at the moment.\n");
    return 1;
    }

  write("You " + mess + " "+obs[0]->query_name()+".\n");
  mess = pluralize(mess);
  say(ambusher->query_cap_name()+" " + mess + " "+
      obs[0]->query_name()+".\n", obs[0]);
  tell_object(obs[0], ambusher->query_cap_name()+
              " " + mess + " you.\n");
  obs[0]->attack_by(ambusher);
  ambusher->attack_by(obs[0]);

ambusher->modify_skill(sname,skill);

  if (weap) weap->weapon_attack(obs[0], ambusher);
    else
   this_player()->unarmed_attack(obs[0], ambusher); 

ambusher->modify_skill(sname, -skill);

  return 1;
} /* int ambush */

string help(string str) 
  {
  return "Syntax: ambush <person>\n\n"+
"The ambush action gives a bonus to your first attack equal to your skill " +
". This bonus can only be applied to melee weapons (or unarmed " +
"combat) " +
"To ambush you must not be in combat yourself (though your target may be). " +
"Also, being hidden when you ambush gives a +" + HIDDEN_BONUS +
"bonus to this action.\n" +
"Example:\n" +
"> wield club\n" +
"> ambush thief\n" +
"You cosh thief.\n\n" +
"See also\n"+
"  Hmmm?\n";
}
