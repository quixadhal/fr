inherit "/std/guilds/cleric";

void setup()
{
  set_name("virga");
  set_short("Priest of Virga");
   set_long("Priests of Virga.\n"
         "The Priests of Virga follow a code of honor and law. "
        "To honor and serve Virga.\n"
        "To Protect Law and Order regardless of personal danger.\n"
         "To Heal the Good and Seek out and Smite the Evil.\n"
         "Honor is Life. Death before Dishonor.\n"
         "Priest of Virga can wear any armour, but must "
        "wield only blunt weapons, with the execption of axes. "
      "\n\n");
  reset_get();
  /* add_guild_command in a guild ? should be in known commands at joining .. */
  /* It's an add_guild_command for the guild object.. */
  /* Baldrick.. */
   add_guild_command("turn",1);
}

int query_legal_race(string race)
{
  switch(race)
  {
    case "human": 
      case "gnome":
      case "half-elf":
    case "dwarf": 
      return 1;
    default : return 0;
  }
}

int query_legal_weapon(string type) 
{ 
  switch(type)
  {
    case "battle axe":
      case "flail":
      case "hammer":
      case "mace":
      case "quarterstaff":
      case "sling":
      case "staff":
      case "war hammer":
    case "hand axe":
   case "twohanded axe":
         return 1;
    default: return 0;
  }
}

int query_legal_armour(string type)
{
    return 1;
}

 int query_channel() { return 0; }

mixed query_legal_spheres()
{
  return ({
  ({ "healing", "major" }),
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
