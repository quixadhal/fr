inherit "/std/guilds/warrior";
void setup()
{
   set_name("ranger");
   set_short("Ranger");
   set_main_skill("dex");
   add_guild_command("track",1);
   add_guild_command("scout",1);
   add_guild_command("hide",1);
   add_guild_command("sneak",1);
// add_guild_command("snare",1);
   add_guild_command("summon",1);
   add_guild_command("hunt",1);
   add_guild_command("mend",1);
   add_guild_command("herbalism",1);
}
string query_spell_directory() { return "/std/spells/druid/"; }
int query_xp_cost() { return 2250; }
int query_legal_race(string race)
{
   switch(race)
   {
      case "human":
      case "drow":
      case "elf":
      case "half-elf":
      case "immortal":
         return 1;
      default:
         return 0;
   }
}
int query_legal_armour(string type)
{
   switch(type)
   {
      case "banded mail": case "banded":
      case "brigandine":
      case "chainmail": case "chain": case "chain mail":
      case "bronze plate":
      case "field plate":
      case "full plate":
      case "plate mail": case "plate":
      case "ring mail":
      case "scale mail": case "scale":
      case "splint mail": case "splint":
      case "great helm": case "full helm": case "visored helm":
         return 0;
      default:
         return 1;
   }
}
int query_dual_wield_penalty() { return 0; }
mixed query_legal_spheres()
{
   return ({
   ({ "ranger", "major" }),
   });
}
