inherit "std/guilds/cleric";

string query_title(object player)
{
 int lvl,male;

 lvl = query_level(player);
 male = (int)player->query_gender() != 2;

 if(lvl > 20) return (male) ? "the Morninglord": "the Morninglady";
 return (male) ? "the Dawn Priest": "The Dawn Priestess";
}

void setup()
{
 set_name("taniwha");
 set_short("Priest of Taniwha");
 set_long("The morning-priests of Taniwha worship rebirth, renewal, "
          "the dawn and youth.  These priests are in most respects "
          "similar to normal priests, but gain a couple of special spells, "
          "and are restricted to use either plated metal armour or no armour "
          "at all.  The morning-priests are also restricted to only use "
		  "non-edged bludgeon weapons.  Priests of Taniwha prefer "
		  "bright and shiny weapons and armours, those that symbolize "
		  "the bright morning sky.\n");
   add_guild_command("turn",1);
 reset_get();
}

int query_legal_race(string race)
  {
     switch(race)
       {
	case "drow":
        case "orc":
        case "goblins":
   case "duergar":
         return 0;
	default:
	 return 1;
      }
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
  switch(type)
   {
     /** only plate and shield allowed, plus head, hand, neck, footware **/

 	case "banded mail":
	case "banded":
	case "bracers":
	case "brigandine":
	case "chain mail":
	case "chain":
	case "elfin chain":
	case "hide":
	case "padded leather":
	case "padded":
	case "ring mail":
	case "scale mail":
	case "scale":
	case "splint mail":
	case "splint":
	case "studded":
	case "studded leather":
	case "wooden shield":

	return 0;
  default :
	return 1;
  }
}

mixed query_legal_spheres()
{
  return ({
  ({ "all", "minor" }),
  ({ "astral", "major" }),
  ({ "elemental", "neutral" }),
  ({ "healing", "neutral" }),
  ({ "plant", "major" }),
  ({ "sun", "major" }),
  ({ "weather", "minor" }),
  ({ "combat", "neutral" }),
  ({ "clericdivination", "major" }),
  ({ "guardian", "minor" }),
    });
}
