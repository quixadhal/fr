inherit "/std/guilds/mage";

void setup()
{
  set_name("drow_wizard");
  set_short("drow wizard");
  set_long("This is the Drow Wizards guild.  Most drow only become "+
		"general wizards and never become specialists.  Drow don't "+
        "like to limit their studies.  Drow Wizards are restricted to "+
	    "all armours except for robes, cloaks, rings, amulets, and the "+
		"like.  They are also restricted to using the dagger, staff, and "+
        "dart like weapons.\n");
 /** insert description of wizards above ***/
  reset_get();
}

int query_legal_race(string race)
  {
  switch(race)
    {
    case "drow":
      return 1;
    default:
      return 0;
    }
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


mixed query_legal_spheres()
{
   return ({"abjuration","alteration","illusion","lesserdivination",
    "greaterdivination","necromancy","invocation","conjuration","enchantment"});
}
