inherit "std/guilds/cleric";

#define STONED "/std/spells/cleric/stoned.c"
void on_death(object player,object killer)
{
    object ob;
    if(killer && interactive(killer))
    {
	if(!player->query_property("hokquest")) return;
	tell_room(environment(killer),"The air itself recoils for a moment.\n");
	// check level diff.
	if((int)killer->query_level() < ((int)player->query_level()+5)) return;
	// Did victim start the fight ?
	if(member_array(killer->query_name(),player->query_players_attacked()) != -1) return;
	tell_room(environment(killer),"The God Hokemj appears, he does NOT look pleased.\n",killer);
	tell_object(killer,"The God Hokemj appears and judges you GUILTY!.\n");
	ob=clone_object(STONED);
	ob->move(killer);
	killer->add_timed_property("stoned",1,80000);
	ob->reset_get();
	ob->setup_shadow(killer);
    }
}
void setup()
{
 set_name("hokemj");
 set_short("Priest of hokemj");
 set_long(
"This is the shrine of hokemj, where the God of chance is worshipped. "
"This temple also work as a clerics' guild. The guild gives you " 
"skills that relate to healing and turning the undead minions.  " 
"You will also get a certain amount of help in defending yourself " 
"in combat as priests are a bunch very susceptible to pain.\n"
"They also get at high levels the abilty to give people extra lives "
"and at much lower levels refresh the character anew.  "
"The Worshippers of hokemj are allowed to wear all types of armour, but "
"may only use weapons of the bludgeoning type.\n");

   add_guild_command("turn",1);
 reset_get();
}

void start_player(object ob)
{
   ::start_player(ob);
   ob->adjust_bonus_cha(-(int)ob->query_bonus_cha());
   ob->adjust_bonus_cha((int)ob->query_level());
}
int query_legal_weapon(string type)
  {
  switch (type)
    {
    case "mace" :
    case "club" :
	case "flail":
	case "morning star":
   case "twohanded_staff":
   case "twohanded_mace":
	case "quarterstaff":
	case "war hammer":
   case "whip":

     return 1;
    default : 
      return 0;
    }
  }

int query_legal_armour(string type)
{
	  return 1;
}

int query_legal_race(string race)
  {
  switch(race)
    { 
    case "drow":
    case "duergar":
    case "dwarf":
      return 0;
    default:
      return 1;
    }
  }

mixed query_legal_spheres()
{
  return ({
  ({ "healing", "major" }),
  ({ "all", "major" }),
  ({ "clericdivination", "neutral" }),
  ({ "necromantic", "minor" }),
  ({ "protection", "major" }),
  ({ "summoning", "minor" }),
  ({ "guardian", "neutral" }),
  ({ "sun", "neutral" }),
  ({ "plant", "neutral" }),
  ({ "weather", "major" }),
    });
}
