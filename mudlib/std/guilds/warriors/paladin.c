inherit "/std/guilds/warrior";

string help()
{
 return "help on paladins here\n";
 reset_get();
}
string query_main_skill() { return "wis"; }

int query_skill_cost(string skill)
{
 return 0;
}

void start_player(object ob)
{
  object boo;
  boo = clone_object("/std/commands/shadows/gob.c");
  boo->move(ob);
  call_out("setup_gob",10,boo,ob);
  ::start_player(ob);
  return ;
}

void setup_gob(object it, object him)
{
  it->move(him);
  it->init();
}

void setup()
{
 set_name("paladin");
 set_short("paladin");
 set_long("This is the Paladin's guild.\n");
 set_main_skill("wis");
 reset_get();

  add_guild_command("charge", 1);
  add_guild_command("focus", 1);
  add_guild_command("layhands", 4);
}

int query_advance_cost() { return 2000; }

string query_spell_directory() { return "/std/spells/cleric/"; }

int query_xp_cost() { return 2200; }

int query_legal_race(string race)
{
 switch(race)
 {
   case "human":
   return 1;
   default:
   return 0;
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
