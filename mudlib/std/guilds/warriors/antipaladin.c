inherit "/std/guilds/warrior";

string help()
{
    return "help on anti-paladins here\n";
    reset_get();
}
string query_main_skill() { return "wis"; }


int query_skill_cost(string skill)
{
    return 0;
}

void start_player(object ob)
{
    if(!ob->query_creator())
    {
	object boo;
	boo = clone_object("/std/commands/shadows/gob.c");
	boo->move(ob);
	ob->remove_property("fear");
	ob->remove_timed_property("fear");
	ob->add_static_property("psionic",(int)ob->query_level()*5);
	call_out("setup_gob",10,boo,ob);
    }
    ::start_player(ob);
}

void setup_gob(object it, object him)
{
    it->move(him);
    it->init();
}

void setup()
{
    set_name("antipaladin");
    set_short("antipaladin");
    set_long("This is the Anti-paladin's guild.\n");
    set_main_skill("wis");
    reset_get();

    add_guild_command("charge", 1);
    add_guild_command("focus", 1);
    add_guild_command("drain", 4);
    add_guild_command("turn",1);
}

int query_advance_cost() { return 2000; }

string query_spell_directory() { return "/std/spells/cleric/"; }

int query_xp_cost() { return 2200; }

int query_legal_race(string race)
{
    switch(race)
    {
    default:
	return 0;
    case "human":
	return 1;
    }
}


mixed query_legal_spheres()
{
    return ({ ({"antipaladin","major"}) });
}

void set_gp(object ob)
{
    ob->set_max_gp(level+(int)ob->query_str()+(int)ob->query_con()/2+
      ob->query_wis());
}

