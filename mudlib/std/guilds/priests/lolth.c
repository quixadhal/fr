inherit "std/guilds/cleric";

void setup()
{
 set_name("Lolth");
 set_short("Priest of Lolth");
 set_long(
          "This is the temple of the Drow Goddess Lolth.  "+
          "Lolth deems all weapons and armours usable by her servants.\n");
 set_needed_align("evil");
   add_guild_command("turn",1);
 reset_get();
}

int query_legal_weapon(string type)
  {
     return 1;
  }

int query_legal_armour(string type)
{
    return 1;
}

int query_legal_race(string race)
  {
  switch (race)
    {
    case "drow" :
      return 1;
    default :
      return 0;
    }
  }

mixed query_legal_spheres()
  {
  /* the spheres : */
  return ({"animal", "charm", "healing", "all",
       "combat", "clericdivination", "elemental", "necromantic",
       "protection", "summoning", "guardian", "weather"});
  }
