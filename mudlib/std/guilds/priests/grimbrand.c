inherit "std/guilds/cleric";

void setup()
{
 set_name("Grimbrand");
 set_short("Priest of Grimbrand");
 set_long(
"This is a worshippor of Grimbrand, Duergar God of "
"Lying, Thieving, and Deception.  Grimbrand deems all "
"weapons and armours usable by his followers.\n\n");
 set_needed_align("evil");
   add_guild_command("turn",1);
  add_guild_command("sneak",1);
  add_guild_command("hide",1);
add_guild_command("steal",5);
  add_guild_command("palm",5);
  add_guild_command("slip", 5);
 reset_get();
}

int query_legal_weapon(string type)
  {
     return 1;
  }

int query_legal_armour(string type)
{
   switch(type) {
    case "full plate":
    case "field plate":
    return 0;
    default:
    return 1;
    }
}

int query_legal_race(string race)
  {
  switch (race)
    {
    case "immortal":
    case "duergar" :
      return 1;
    default :
      return 0;
    }
  }

mixed query_legal_spheres()
{
  return ({
  ({ "healing", "minor" }),
  ({ "all", "neutral" }),
  ({ "combat", "neutral" }),
  ({ "necromantic", "minor" }),
  ({ "protection", "neutral" }),
  ({ "guardian", "major" }),
    });
}

int query_advance_cost() { return 1000; }
int query_xp_cost() { return 2000; }
