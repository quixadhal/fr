inherit "/std/guilds/cleric";

void setup()
{
  set_name("timion");
  set_short("Priest of Timion");
  set_long("The Priests of Timion are considered to be very noble, just, "
          "lawful.  What these priests lack in spells they gain back from "
          "being better fighters than most clerics.  Priests of Timion can "
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
  return ({
  ({ "healing", "minor" }),
  ({ "animal", "minor" }),
  ({ "combat", "major" }),
  ({ "clericdivination", "minor" }),
  ({ "necromantic", "minor" }),
  ({ "protection", "neutral" }),
  ({ "all", "minor" }),
  ({ "guardian", "neutral" }),
  ({ "sun", "minor" }),
  ({ "summoning", "neutral" }),
    });
}

int query_thac0_step() { return 4; }
