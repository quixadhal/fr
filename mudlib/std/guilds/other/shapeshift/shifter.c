/* basically made mods to the wiz-war guild ob
 * Raskolnikov Oct 96
 */
inherit "std/guild";

int query_skill_cost(string skill)
{
    return 0;
}

void setup()
{
    set_name("shifter");
    set_short("Shapeshifter");
    set_long(
      "One of the most mysterious of all beings, the Shapeshifter "
      "is able to change his form at will.  This skill takes many "
      "years to perfect and therefore the cost of advancement is "
      "quite steep.\n");
    reset_get();
    set_main_skill("int");
    add_guild_command("shift", 1);
    add_guild_command("unshift", 1);
    add_guild_command("focus", 1);
    add_guild_command("sneak", 1);
    add_guild_command("fix", 1);
    add_guild_command("judge", 1);
    add_guild_command("hide", 1);
}

int query_legal_race(string race)
{
    switch(race)
    {
    case "elf":      return 1;
    case "half-elf": return 1;
    case "drow":     return 1;
    case "human":    return 1;
    default:         return 0;
    }
}

/* since only one form can wield/wear anything let them wield or wear
 * anything in their normal state
 */
int query_legal_armour(string type)
{
    return 1;
}

int query_legal_weapon(string type)
{
    return 1;
}

int query_extr_str()  { return 1; }
int query_dice()         { return 10; }
int query_advance_cost() { return 1000; }
int query_xp_cost()      { return 3000; }
int query_thac0_step() { return 5; }

int query_dual_wield_penalty(object me, object w1, object w2)
{
    int bon;

    bon=50-(int)me->query_level();
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

    //if(ob->query_str() - ob->query_tmp_str() >= 18)
    //return;
    if(ob->query_str() - ob->query_tmp_str() < 17)
	return;

    if(ob->query_extreme_str())  return;

    ob->set_extreme_str(roll(1,10));
    tell_object(ob,"You rolled extreme strength.\n");
}

void init()
{
    this_player()->setmin("@$N arrives from $F.");
    this_player()->setmout("@$N leaves $T.");
    ::init();
}
