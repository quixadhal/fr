inherit "std/guild";
#define SPELLTABLE "/table/spell_table"

int query_skill_cost(string skill)
{
   return(6);   // what is this?
}

void setup()
{
   set_name("aphelics");
   set_short("Aphelics");
 
 set_long("This is the legendary Aphelic guild.  They specialize "
    "in the school of illusion and the art of unarmed combat.  "
    "Traditionally, we can not wield many weapons nor wear armour of "
    "any kind... though at times, oddly, you can see a fellow mage "
    "suited in the best armour you have ever seen.  The Aphelic "
    "guild is the toughest of all organizations to climb the ranks "
    "in but the benefits of your long hours studying and "
    "practicing our difficult diciplines become apparent with "
    "time.\n");

   reset_drop();

}

int query_legal_race(string race)
{
  switch(race)
  {
      case "human" :
      case "elf" :
      case "immortal" :        // for test reasons
         return(1);
    default:         return 0;
  }
}

mixed query_legal_spheres()
{
  return ({
    ({"aphelic","major"}),
   ({"illusion","major"}),
    ({ "shadowmagic", "major" })
   });
}



string query_spell_directory() { return "/d/hoerk/test/guild/"; }

int query_legal_armour(string type)
{
  switch(type)
  {
    case "robe":
    case "basinet":
    case "amulet":
    case "pendant":
    case "necklace":
    case "cape":
       return 1;
    default: return 0;
  }
}

int query_legal_weapon(string type) { return(0); }

int query_dice()         { return 7; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 3500; }
int query_thac0_step()   { return 3;}
string query_main_skill() { return "int"; }
