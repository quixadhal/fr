inherit "/std/guilds/warrior";

void setup() {
    set_name("drow_warrior");
    set_short("drow warrior");
    set_long(
      "The Drow Warriors guild teaches one how to be sneaky and deadly " 
      "at the same time.  It gives you skills that relate to finding " 
      "out how good a weapon or armour is at much lower costs, also " 
      "you can sneak and hide like the rogues.  Always remember that a " 
      "dagger in the back will cramp any wizards style.\n");
    reset_get();
    // add_guild_command("slice",1);
    add_guild_command("focus", 1);
    add_guild_command("judge", 1);
    add_guild_command("fix", 1);
    add_guild_command("sneak", 1);
    add_guild_command("hide", 1);
    add_guild_command("darkglobe", 1);
}

int query_channel()
{
  return 0;
}

int query_legal_armour(string type)
{

    switch(type)
    {
    case "full plate":
    case "field plate":
   case "hide":
	return 0;
    default:
	return 1;
    }
}

int query_legal_race(string race)
{
    switch(race)
    {
    case "drow":
	return 1;
    }
    return 0;
}

int query_dual_wield_penalty(object me, object w1, object w2)
{
    int bon;

    if ( w1->query_weapon_type() == 1 && w2->query_weapon_type() == 1 )
    {
	bon = 25 - (int)me->query_level()*2;
	bon = (bon<0 ? 0 : bon);
	return bon;
    }

    return ::query_dual_wield_penalty(me, w1, w2);
}

