inherit "std/guilds/cleric";

void setup()
{
 set_name("druid");
 set_short("Druid");
 set_long(
	"Druids are the keepers of nature.  They protect nature and all "+
	"wildlife, and must be either neutral good or true neutral.  They "+
	"are very strong spellcasters, having minor talents in healing, "+
	"and a well balanced array of fighting and combat affecting spells.  "+
	"Druid spells are cast by going into a trance and becoming one with "+
	"nature, drawing power from the earth itself.\n");
 reset_get();
}

string query_spell_directory() 	{  return "/std/spells/druid/"; }
int query_dice()		{ return 7; }
int query_advance_cost()	{ return 1000; }
int query_xp_cost()		{ return 2200; }

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
    case "orc":
    case "half-orc":
    case "goblin":
    case "lizard-man":
      return 0;
    default:
      return 1;
    }
  }

mixed query_legal_spheres()
  {
  /* the spheres : */
  return ({"druid"});
  }
