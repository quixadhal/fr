inherit "/std/guilds/rogue";

#define SPELL_TABLE "/table/spell_table"
string query_main_skill() { return "cha"; }
int query_advance_cost() { return 750; }

void setup() {
  set_name("bard");
  set_short("Bard");
  set_long("The bards' guild is for those who seek the romantic life of an "
   "entertainer. Along the path to greatness, a bard will pick up a variety "
   "of skills, all necessary to put on a good show. And when times are tough,"
   " a bard may be forced to rely on those less-than-honorable abilities "
   "more often associated with thieves.\n");
  reset_get();
//add_guild_command("lore", "/std/commands/lore", "lore"); /*legend lore*/
  add_guild_command("palm", 1);
  add_guild_command("sneak", 1);
  add_guild_command("hide", 1);
  add_guild_command("slip", 1);
  add_guild_command("steal", 1);
  set_main_skill("cha");
//add_guild_command("assess", "/std/commands/assess", "assess");
} /* setup() */

int query_legal_weapon(string type) {
  return 1;
}

int query_legal_armour(string type) {
  switch(type)
  {
   case "elfin chain":
   case "amulet":
   case "leather":
   case "cloak":
   case "gloves":
   case "boots":
   case "ring":
   case "bracers":
   case "cowl":
   case "shield":
   case "small shield":
   case "medium shield":
   case "wooden shield":
         return 1;
   default: return 0;
  }
}

int query_legal_race(string race) {
  switch(race)
  {
    case "immortal":
    case "human":
    case "elf":
    case "half-elf":
    case "dwarf":
    case "gnome":
    case "halfling":
      return 1;
    default: return 0;
  }
}

string query_spell_directory() {
  return "/std/spells/bards/";
}

int query_xp_cost() { return 1800; }
mixed query_legal_spheres()
{
  return ({
    ({ "bard", "major" })
    });
}
