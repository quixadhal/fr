inherit "/std/guilds/mage";

void setup()
{
  set_name("abjurer");
  set_short("abjurer");
  set_long(" \n");
 /** insert description of specialist above ***/
  reset_get();
}

int query_legal_armour(string type)
{
	switch(type)
	{
     case "robe":
	 case "shoes":
	 case "slippers":
	 case "boots":
	 case "amulet":
	 case "pendant":
	 case "necklace":
	 case "cape":
	 case "cloak":
	 case "ring":
	  return 1;

     default:
	  return 0;

	}

}

int query_legal_weapon(string type)
{
	switch(type)
	{
      case "dagger":
	  case "dirk":
	  case "dart":
	  case "knife":
	  case "quarterstaff":
	  case "staff":
       return 1;

	  default:
	   return 0;

	}

}

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
   return ({"abjuration","lesserdivination",
       "greaterdivination", "necromancy",
       "invocation","conjuration","enchantment"});
}
