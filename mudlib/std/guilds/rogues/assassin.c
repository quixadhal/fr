inherit "/std/guilds/rogue";
 
int query_legal_armour(string arm)
{
   switch(arm)
   {
   case "leather":
   case "studded leather":
   case "studded":
   case "padded leather":
   case "padded":
   case "chainmail":
   case "chain mail":
   case "chain":
   case "ring mail":
   case "elfin chain":
   case "boots":
   case "cloak":
   case "gloves":
   case "amulet":
   case "helmet":
   case "helm":
   case "basinet":
   case "cowl":
   case "bracers":
  case "buckler":
  case "small shield":
  case "wooden shield":
  case "shield":
   case "large shield":
  case "medium shield":
   case "ring":
   case "slippers":
   return 1;
   default:
   return 0;
   }
}
void setup() {
  set_name("assassin");
  set_short("Assassin");
  set_long("The assassin guild gives you good thief skills, specially "
           "designed to kill fast.  You'll also get to know a bit about "
           "poisons at higher levels. There is "
           "but a few rules to follow for the guild and those are "
           "posted on the board.\n");
  reset_get();
  add_guild_command("sneak", 1);
  add_guild_command("focus", 1);
  add_guild_command("decapitate", 1);
  add_guild_command("hide", 1);
  add_guild_command("slip", 1);
  add_guild_command("judge", 1);
  add_guild_command("ambush", 1);
  set_main_skill("dex");
}

int query_dual_wield_penalty(object me, object w1, object w2)
{
  int bon;

  if ( w1->query_attack_type() == 2 || w2->query_attack_type() == 2 )
    return 50;

  bon = 50 - (int)me->query_level()*4/3;
  bon = (bon<0 ? 0 : bon );
  return bon;
}
