/* Turn */
/* By Wonderflug */

#define TURN_GP_COST 5
#define TURN_BASE 15
#define TURN_DESTROY_XP 5
#define TURN_AWAY_XP 10
#define TURN_LOCKOUT 50

inherit "/std/spells/patch.c";

mixed find_unique_match(string find, mixed in);

string help()
{
  return "\nSyntax:  turn <target1>,<target2>,...\n"+
	"Cost: "+TURN_GP_COST+" GP\n\n"+
	"  This command lets you bring forth the wrath of your god against "+
	"undead creatures.  Depending on the level of the priest, a "+
	"netherworld creature may be destroyed completely, turned (ie, "+
	"forced to run away), simply cowed into not fighting, or "+
	"enraged.  In order to focus the power of your god, a holy "+
	"symbol is needed.  Once an attempt has been made to turn a creature, "+
	"further attempts will usually fail. "+
	"\n\n";
}

int turn(string str)
{
  int i, lev, t_wis, t_lev;
  string has_symbol;
  object *ob, *items;
  object turner;

  turner = this_player();
  t_wis = (int)turner->query_wis();
  t_lev = (int)turner->query_level();
   if((string)turner->query_guild_name() == "lathander") t_lev += 8; /* lathander AD&D +4 against undead +8 here */
 

  if (!str)
  {
	notify_fail("Syntax: turn <target>\n");
	return 0;
  }

  has_symbol = "frooble";
  items = all_inventory(turner);
  for (i=0;i<sizeof(items);i++)
	if ((string)items[i]->query_name() == "holy symbol")
		has_symbol = (string)items[i]->query_property("faith");

  if (has_symbol=="frooble")
  {
	notify_fail("You need a holy symbol of your faith to turn undead.\n");
	return 0;
  }
  if (has_symbol != (string)turner->query_guild_name() )
  {
	tell_object(turner, "You are stricken by balefire for using an "+
	  "instrument of another faith!\n");
	tell_room(environment(turner), "A bolt of balefire comes out of "+
	  "nowhere and strikes "+turner->query_cap_name()+"!\n",
	  turner);
	turner->set_gp(0);
	turner->adjust_hp( -(random(20))-10 );
	return 1;
  }

  ob = (object*)find_unique_match(str, environment(turner));

  if (!(sizeof(ob)))
  {
	notify_fail("Your target is not here.\n");
	return 0;
  }
  if ((int)turner->query_gp() < TURN_GP_COST )
  {
	notify_fail("You don't have the energy to turn any undead "+
	  "right now.\n");
	return 0;
  }

  turner->adjust_gp(-TURN_GP_COST);
  tell_room(environment(turner), "\n"+turner->query_cap_name()+
	" raises a holy symbol and calls down the wrath of "+
	turner->query_possessive()+" god!\n", turner);
  tell_object(turner, "You raise your holy symbol and call down the wrath "+
	"of "+turner->query_guild_name()+"!\n");

/*  Now loop through all the targets we got, check they're undead, and
 * do a turn-roll and see how wasted they are.
 */

  for (i=0;i<sizeof(ob);i++)
  {
    if ((!(ob[i]->query_hb_counter())) || ob[i] == turner )
	continue;

    if (ob[i]->query_property("turned_by_"+this_player()->query_name()) )
    {
	tell_room(environment(turner), ob[i]->query_cap_name()+
	  " howls in rage and attacks "+turner->query_cap_name()+"!\n",
	  turner);
	tell_object(turner, ob[i]->query_cap_name()+ " howls in rage at "+
	  "your attempt to turn it again and \nattacks you!\n");
	ob[i]->attack_ob(turner);
	continue;
    }
    if ((lev = ob[i]->query_property("undead")))
    {
      switch( random(t_wis + t_lev) - (lev+TURN_BASE) )
      {
	case 10..5000:
	  tell_room(environment(turner), ob[i]->query_cap_name()+
	    " is utterly destroyed!\n");
	  turner->adjust_xp((int)ob[i]->query_kill_xp()/TURN_DESTROY_XP);
	  ob[i]->dest_me();  /* utter destruction leaves no corpse :) */
	  break;
	case 5..9:
	  tell_room(environment(turner),ob[i]->query_cap_name()+
	    " is turned away!\n");
	  turner->adjust_xp((int)ob[i]->query_kill_xp()/TURN_AWAY_XP);
	  ob[i]->run_away();
	  ob[i]->stop_fight(turner);
	  turner->stop_fight(ob[i]);
	  break;
	case 0..4:
	  tell_room(environment(turner), ob[i]->query_cap_name()+
	    " cowers from the power but holds its ground.\n");
	  ob[i]->stop_fight(turner);
	  turner->stop_fight(turner);
	  break;
	default:
	  tell_room(environment(turner), ob[i]->query_cap_name()+
	    " laughs defiantly and attacks "+turner->query_cap_name()+"!\n", 
	    turner);
	  tell_object(turner, ob[i]->query_cap_name()+" laughs defiantly and "+
	    "attacks you!\n");
	  ob[i]->attack_ob(turner);
	  break;
      }
	if (ob[i])
      ob[i]->add_timed_property("turned_by_"+this_player()->query_name(), 
		1, TURN_LOCKOUT);
    }
    else
    {
	tell_object(turner,ob[i]->query_cap_name()+" is not undead.  "+
	  ob[i]->query_cap_name()+" gets mad and attacks you.\n");
	tell_room(environment(turner), ob[i]->query_cap_name()+
	  " notices "+turner->query_cap_name()+" using a holy symbol at "+
	  ob[i]->query_objective()+".\n"+ob[i]->query_cap_name()+" gets mad "+
	  "and attacks "+turner->query_objective()+".\n", turner);
	ob[i]->attack_ob(turner);
    }
  }  
  return 1;
}
