inherit "std/guilds/cleric";

void setup()
{
 set_name("tymora");
 set_short("Priest of Tymora");
 set_long(
"This is the shrine of Tymora, where the goddess of chance is worshipped. "+
"This temple also work as a clerics' guild. The guild gives you " +
"skills that relate to healing and turning the undead minions.  " +
"You will also get a certain amount of help in defending yourself " +
"in combat as priests are a bunch very susceptible to pain.\n"+
"They also get at high levels the abilty to give people extra lives "+
"and at much lower levels refresh the character anew.  "+
"The Worshippers of Tymora are allowed to wear all types of armour, but "+
"may only use weapons of the bludgeoning type.\n");

 reset_get();
}

int query_legal_weapon(string type)
  {
  switch (type)
    {
    case "mace" :
    case "club" :
	case "flail":
	case "morning star":
	case "quarterstaff":
	case "war hammer":

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
      return 0;
    default:
      return 1;
    }
  }

mixed query_legal_spheres()
  {
  /* the spheres : */
  return ({"healing", "all", "clericdivination", "necromantic", 
       "protection", "summoning", "guardian", "sun", "weather"});
  }
