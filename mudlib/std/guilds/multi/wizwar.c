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
      "Wizard-Warriors specialize in neighter magic nor fighting, "
      "but are fairly competent in both.  It is very costly for them "
      "to advance in levels since they have to learn twice as much "
      "as the specialized classes for each level they gain.\n");
 reset_get();
set_main_skill("int");
  add_guild_command("focus", 1);
  add_guild_command("sneak", 1);
  add_guild_command("fix", 1);
  add_guild_command("judge", 1);
  add_guild_command("retrieve", 1);
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

string query_spell_directory() { return "/std/spells/wizard/"; }

int query_legal_armour(string type)
{
  switch(type)
  {
    case "robe":
    case "studded leather":
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
   case "elfin chain":
   case "cowl":
   case "small shield":
   case "medium shield":
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
    case "lance":
         return 0;
    default: return 1;
  }
}

int query_extr_str()  { return 1; }
int query_dice()         { return 8; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 3000; }
int query_thac0_step() { return 5; }

int query_dual_wield_penalty(object me, object w1, object w2)
{
  int bon;

  bon = 50 - (int)me->query_level()*2;
  bon = ( bon<0 ? 0 : bon );

  return bon;
}
mixed query_legal_spheres()
{
  return ({  });
}


void start_player(object ob)
{
   ::start_player(ob);

  if(ob->query_str() - ob->query_tmp_str() >= 18)
    return;
  if(ob->query_str() - ob->query_tmp_str() < 17)
    return;

  if(ob->query_extreme_str())  return;

  ob->set_extreme_str(roll(1,10));
  tell_object(ob,"You rolled extreme strength.\n");
}
