inherit "std/guild";

int query_skill_cost(string skill)
{
 return 0;  /* Need a list of possible skills first.  Awaiting Dank */
}

void setup()
{
 set_name("cle-war");
 set_short("Cleric-Warrior");
 set_long(
      "Cleric-Warriors specialize in neighter divine magic nor fighting, "
      "but are fairly competent in both.  It is costly for them "
      "to advance in levels since they have to learn twice as much "
      "as the specialized classes for each level they gain.  They are "
      "able to withstand almost as much daage as true fighters, and can "
      "use all the armours they can use as well.  They are however restricted "
      "to normal clerical weapons (blunt).\n");
 reset_get();
 set_main_skill("wis");
}

int query_legal_race(string race)
{
  switch(race)
  {
    case "dwarf":      return 1;
    case "half-elf": return 1;
    case "elf":     return 1;
    default:         return 0;
  }
}

/* If you want to, feel free to broaden this list */
mixed query_legal_spells()
{
  mixed list;
  list = ({ });

  switch(level)
  {
   case 20: list += ({"wish",});
   case 1 : list += ({"cure light wounds",});
            list += ({"light",});
  }
  return list;
}

int query_legal_spell(string str)
{
  int spell;

  if(spell = member_array(str, query_legal_spells()) != -1)
    return 1;
  return 0;
}

string query_spell_directory() { return "/std/spells/cleric/"; }

int query_legal_armour(string type) { return 1; }

int query_legal_weapon(string type)
{
  switch(type)
  {
    case "mace":
    case "flail":
    case "sling":
    case "hammer":
    case "quarterstaff":
    case "staff":
    case "warhammer":
         return 1;
    default: return 0;
  }
}

int query_dice()         { return 9; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 3500; }
