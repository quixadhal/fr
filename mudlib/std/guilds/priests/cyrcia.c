inherit "std/guilds/cleric";

void setup()
{
 set_name("Cyrcia");
 set_short("Priest of Cyrcia");
 set_long(
          "This is the temple of the Drow Goddess Cyrcia.  "
         "Some other Gods disagreed with the suggestion below."
	"Cyrcia allows her servants only blunt weapons, and"
	" armours that do not hinder movement.\n");
 set_needed_align("evil");
   add_guild_command("turn",1);
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
    case "whip":
    case "dagger":
	case "twohanded_mace":
     return 1;
    default : 
      return 0;
    }
}

int query_channel()
{
  return 0;
}

int query_legal_armour(string type)
{
   switch(type)
   {
   case "full plate":
   case "field plate":
   return 0; // taniwha disagrees
   default:
    return 1;
   }
}

int query_legal_race(string race)
  {
  switch (race)
    {
    case "immortal":
    case "drow" :
      return 1;
    default :
      return 0;
    }
  }

mixed query_legal_spheres()
{
  return ({
  ({ "animal", "minor" }),
  ({ "charm", "major" }),
  ({ "healing", "neutral" }),
  ({ "all", "neutral" }),
  ({ "combat", "major" }),
  ({ "clericdivination", "minor" }),
  ({ "elemental", "minor" }),
  ({ "necromantic", "major" }),
  ({ "protection", "neutral" }),
  ({ "summoning", "major" }),
  ({ "guardian", "minor" }),
  ({ "weather", "minor" })
    });
}
