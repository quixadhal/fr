inherit "/std/guilds/rogue";

#define SPELL_TABLE "/table/spell_table"
string query_main_skill() { return "cha"; }

void setup() {
  set_name("bard");
  set_short("Bard");
  set_long("The bards' guild is for those who seek the romantic life of an "+
   "entertainer. Along the path to greatness, a bard will pick up a variety "+
   "of skills, all necessary to put on a good show. And when times are tough,"+
   " a bard may be forced to rely on those less-than-honorable abilities "+
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
    case "banded mail":
    case "banded":
    case "bronze plate":
    case "field plate":
    case "full plate":
    case "plate mail":
    case "splint mail":
    case "buckler":
    case "medium shield":
    case "large shield":
    case "small shield":
    case "wooden shield":
       return 0;
    default: return 1;
  }
}

int query_legal_race(string race) {
  switch(race)
  {
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
  return "/std/spells/wizard/";
}


mixed query_legal_spheres() {

string race;
  race = (string)this_player()->query_race_name();
  switch(race)
  {
    case "gnome": return ({"illusion"});
    case "dwarf":
    case "halfling": return ({""});
    default: return ({"abjuration","alteration","illusion","lesserdivination",
       "greaterdivination", "necromancy",
       "invocation","conjuration","enchantment"});
  }
}
