inherit "/std/guilds/cleric";

void setup()
{
  set_name("tempus");
  set_short("Priest of Tempus");
  set_long("The Priests of Tempus are considered to be very warlike and "+
          "chaotic.  What these priests lack of spells they gain back from "+
          "being better fighters than most clerics.  Priests of Tempus can "+
          "wear all kinds of armour and wield any meelee weapons.\n");
  reset_get();
  /* add_guild_command in a guild ? should be in known commands at joining .. */
  /* It's an add_guild_command for the guild object.. */
  /* Baldrick.. */
  add_guild_command("judge", 1);
  add_guild_command("fix", 1);
   add_guild_command("turn",1);
}

int query_legal_race(string race)
{
  switch(race)
  {
    case "elf": 
    case "halfling": 
    case "gnome":
    case "goblin":
    case "drow": 
    case "orc":
      return 0;
    default : return 1;
  }
}

int query_legal_weapon(string type) 
{ 
  switch(type)
  {
    case "bow":
    case "sling":
    case "crossbow":
         return 0;
    default: return 1;
  }
}

int query_legal_armour(string type)
{
    return 1;
}


mixed query_legal_spheres()
  {
  return ({"healing", "elemental", "animal", "combat", "clericdivination",
           "necromantic", "protection",
           "weather", "all", "guardian", "sun", "summoning"});

  }

int query_thac0_step() { return 2; }
