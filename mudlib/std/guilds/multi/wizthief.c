
inherit "std/guild";

#define SPELLTABLE "/table/spell_table"
int query_skill_cost(string skill)
{
return 6;
}

void setup()
{
 set_name("wizthief");
 set_short("Wizard-Thief");
 set_long(
      "Wizard-Thieves specialize in neither magic nor pilfering, "+
      "but are fairly competent in both.  It is costly for them "+
      "to advance in levels since they have to learn twice as much "+
      "as the specialized classes for each level they gain.\n");
 reset_get();
 set_main_skill("dex");
 add_guild_command("sneak",1);
add_guild_command("steal",1);
add_guild_command("palm",1);
add_guild_command("slip",1);
/* added Taniwha 19/01/95 */
   add_guild_command("hide",5);
   add_guild_command("backstab",8);
   add_guild_command("peek",1);

}



int query_legal_race(string race)
{
  switch(race)
  {
    case "elf":      return 1;
    case "human":    return 1;
   case "halfling":  return 1;
    case "half-elf": return 1;
    case "drow":     return 1;
    case "gnome":    return 1;
    default:         return 0;
  }
}

mixed query_legal_spheres()
{
 return ({"alteration","lesserdivination","illusion","enchantment"});
}



string query_spell_directory() { return "/std/spells/wizard/"; }

int query_legal_armour(string type)
{
  switch(type)
  {
    case "robe":
    case "leather":
    case "padded leather":
    case "padded":
    case "basinet":
    case "shoes":
    case "slippers":
    case "boots":
    case "amulet":
    case "pendant":
    case "necklace":
    case "cape":
    case "cloak":
    case "ring":
       return 1;
    default: return 0;
  }
}

int query_legal_weapon(string type)
{
  switch(type)
  {
    case "twohanded sword":
    case "polearm":
    case "bastard sword":
    case "pike":
    case "awl pike":
    case "axe":
    case "mace":
    case "flail":
    case "lance":
         return 0;
    default: return 1;
  }
}

int query_dice()         { return 7; }
int query_advance_cost() { return 1000; }
// lowered the xp cost from 4000, excessive considering they get no good offenive spells
int query_xp_cost()      { return 3000; }
int query_thac0_step()   { return 2;}
string query_main_skill() { return "dex"; }

