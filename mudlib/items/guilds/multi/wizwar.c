inherit "std/guild";

int query_skill_cost(string skill)
{
 return 0;  /* Need a list of possible skills first.  Awaiting Dank */
}

void setup()
{
 set_name("wiz-war");
 set_short("Wizard-Warrior");
 set_long(
      "Wizard-Warriors specialize in neighter magic nor fighting, "+
      "but are fairly competent in both.  It is very costly for them "+
      "to advance in levels since they have to learn twice as much "+
      "as the specialized classes for each level they gain.\n");
 reset_get();
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
   case 1 : list += ({"magic missile",});
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
    case "lance":
         return 0;
    default: return 1;
  }
}

int query_dice()         { return 8; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 4500; }

int check_spell(object ob)
{
 if (random(3))
  call_out("do_check_spell", 0, ob);
}
