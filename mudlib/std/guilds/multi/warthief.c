inherit "std/guild";

int query_skill_cost(string skill)
{
 return 0;  /* Need a list of possible skills first.  Awaiting Dank */
}

void setup()
{
 set_name("war-thief");
 set_short("Warrior-Thief");
 set_long(
      "Warrior-Thieves specialize in neighter fighting nor pilfering, "+
      "but are fairly competent in both.  It is quite costly for them "+
      "to advance in levels since they have to learn twice as much "+
      "as the specialized classes for each level they gain.\n");
 reset_get();
}

void set_gp(object ob)
{ ob->set_max_gp(level+(int)ob->query_dex()); }

void set_hp(object ob)
{ ob->set_max_hp(query_dice()*level); }

int query_legal_race(string race)
{
  switch(race)
  {
    case "elf":    
    case "half-elf":
    case "drow":    
    case "gnome":   
    case "halfling": 
         return 1;
    default:         return 0;
  }
}

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

int query_dice()         { return 8; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 3500; }
