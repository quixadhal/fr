inherit "std/guild";

#define SPELLTABLE "/table/spell_table"
int query_skill_cost(string skill)
{
return 6;
}

void setup()
{
 set_name("wiz-thief");
 set_short("Wizard-Thief");
 set_long(
      "Wizard-Thieves specialize in neighter magic nor pilfering, "+
      "but are fairly competent in both.  It is costly for them "+
      "to advance in levels since they have to learn twice as much "+
      "as the specialized classes for each level they gain.\n");
 reset_get();
 add_main_skill("dex");
add_main_skill("int");
}

void set_gp(object ob)
{ ob->set_max_gp(level+(int)ob->query_int()); }

void set_hp(object ob)
{ ob->set_max_hp(query_dice()*level); }

int query_legal_race(string race)
{
  switch(race)
  {
    case "elf":      return 1;
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
       return 0;
    default: return 1;
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
    case "lance":
         return 0;
    default: return 1;
  }
}

int query_dice()         { return 7; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 4000; }
