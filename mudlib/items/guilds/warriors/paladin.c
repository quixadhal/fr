inherit "/std/guilds/warrior";

string help()
{
 return "help on paladins here\n";
 reset_get();
}

int query_skill_cost(string skill)
{
 return 0;
}

void setup()
{
 set_name("paladin");
 set_short("paladin");
 set_long("This is the Paladin's guild.\n");
 set_main_skill("wis");
 reset_get();
}

int query_advance_cost() 
{
 if (this_player()->query_value() < 2000)
  return 1000;
 else
  return (int)this_player()->query_value() - 1000;
}

int query_xp_cost() { return 3500; }

int query_legal_race(string race)
{
 switch(race)
 {
  case "orc":
  case "half-elf":
  case "elf":
  case "halfling":
  case "lizard-man":
  case "goblin":
  case "drow":
  case "half-orc":
  case "troll":
   return 0;
  default:
   return 1;
 }
}


mixed query_legal_spheres()
{
  return ({"paladin"});
}

void set_gp(object ob)
{
 ob->set_max_gp(level+(int)ob->query_str()+(int)ob->query_con()/2+
		ob->query_wis());
}
 
void init()
{
 add_action("kill","prohibit_attack");
 ::init();
}
 
prohibit_attack(arg)
{
 if(!arg) {return 0;}
 if(!find_living(arg)) {return 0;}
 if(find_living(arg)->query_alignment()<=0)
   {
    write("You cannot attack!! That would be Dishonerable!\n");
    return 1;
   }
  else return 0;
}
