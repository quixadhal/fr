/* This will be the table for spells.
 * It will be the place spells.c will look for when it casts a spell, and the
 * guld will find the spells to add to a player. 
 * This will reduce the memory requirements in the spell array in the player obs
 * But it may be slower than the old system. I am not sure yet tho..
 * Started sept 11 '93 by Baldrick.
 */
/* the complete array will not be finished until I know what I need */
/* it looks like the easiest method is to have two tables, one for sphere/spell
 * and one for spell/filename.. Shame ..*/

/*** Addition of spells and new spheres started by Eerevann Nov 93 ***/

//mixed spellarray;

mixed query_spellist()
  {
  mixed list;
  int level;
  string bing;

  list = ({ });
  level = this_player()->query_level();

  /* I'm afraid we have to put a query_spell into all the cases.. */

  /* this is the way of adding a sphere/school */

  /*** Level/Spell progression is as per AD&D ***/
  /*** CLERIC MAGIC ***/
  /*** 1st level spells at 1st level, 2nd level spells at 3rd level ***/
  /*** 3rd level spells at 5th level, 4th level spells at 7th level ***/
  /*** 5th level spells at 9th level, 6th level spells at 11th level ***/
  /*** 7th level spells at 14th level ***/

  /*** WIZARD MAGIC ***/
  /*** 1st level spells at 1st level, 2nd level spells at 3rd level ***/
  /*** 3rd level spells at 5th level, 4th level spells at 7th level ***/
  /*** 5th level spells at 9th level, 6th level spells at 12th level ***/
  /*** 7th level spells at 14th level 8th level spells at 16th level ***/
  /*** 9th level spells at 18th level ***/


  if (this_player()->query_sphere("all"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
      if(!this_player()->query_spell("bless"))
         list += ({"bless"});
    if (!this_player()->query_spell("curse"))
      list += ({ "curse" });
	break;
	  }
    } /* if ALL SPHERE */

  if (this_player()->query_sphere("bard"))
    {
     switch(level)
      {
	case 14..1000:
         if(!this_player()->query_spell("inaudibility"));
               list += ({"inaudibility"});
	case 11..13:
	case 9..10:
	case 7..8:
      if(!this_player()->query_spell("sobriety"))
         list += ({"sobriety"});
	case 5..6:
    if (!this_player()->query_spell("intoxicate"))
      list += ({ "intoxicate" });
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if ALL SPHERE */

  if (this_player()->query_sphere("animal"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if ANIMAL SPHERE */

  if (this_player()->query_sphere("astral"))
    {
     switch(level)
      {
	case 14..1000:
      if(!this_player()->query_spell("shooting stars"))
      list += ({"shooting stars"});
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:

	 break;
	  }
    } /* if ASTRAL SPHERE */


  if (this_player()->query_sphere("combat"))
    {
	 switch(level)
       {
	case 14..1000:
	case 11..13:
	case 9..10:
	 if (!this_player()->query_spell("flamestrike"))
	   list += ({"flamestrike",});
	case 7..8:
	case 5..6:
     if(!this_player()->query_spell("prayer"))
      list += ({"prayer",});
	case 3..4:
	case 1..2:

     break;
       }
    } /* if COMBAT SPHERE */

  if (this_player()->query_sphere("clericdivination"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	  if(!this_player()->query_spell("know alignment"))
	    list += ({"know alignment",});
	case 1..2:
	  if(!this_player()->query_spell("detect magic"))
	    list += ({"detect magic",});

	 break;
	  }
    } /* if cleric DIVINATION SPHERE */

  if (this_player()->query_sphere("elemental"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if ELEMENTAL */


  if (this_player()->query_sphere("guardian"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:

       
	 break;
	  }
    } /* if GUARDIAN SPHERE */


  if (this_player()->query_sphere("healing"))
    {
    switch(level)
      {
      case 14..1000:
         if(!this_player()->query_spell("restore"))
            list+=({"restore",});
      case 12..13:
         if(!this_player()->query_spell("holy storm"))
            list += ({"holy storm"});
      case 11:
	 if (!this_player()->query_spell("heal"))
	   list += ({"heal",});
      case 9..10:
	 if (!this_player()->query_spell("cure critical wounds"))
	   list += ({"cure critical wounds",});
	 if (!this_player()->query_spell("cause critical wounds"))
	   list += ({"cause critical wounds",});
      case 7..8:
	 if (!this_player()->query_spell("cure serious wounds"))
	   list += ({"cure serious wounds",});
	 if (!this_player()->query_spell("cause serious wounds"))
	   list += ({"cause serious wounds",});
      case 5..6:
      case 3..4:
      case 1..2:
	 if (!this_player()->query_spell("cure light wounds"))
	   list += ({"cure light wounds",});
	 if (!this_player()->query_spell("cause light wounds"))
	   list += ({"cause light wounds",});

	break;
      }
    } /* if HEALING SPHERE */


  if (this_player()->query_sphere("necromantic"))
    {
     switch(level)
      {
	case 14..1000:
         if(!this_player()->query_spell("energy drain"))
            list+=({"energy drain",});
	  if(!this_player()->query_spell("resurrect"))
	    list += ({"resurrect",});
	case 11..13:
	case 9..10:
	  if(!this_player()->query_spell("raise dead"))
	    list += ({"raise dead",});
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:


	 break;
	  }
    } /* if NECROMANTIC */


  if (this_player()->query_sphere("protection"))
    {
     switch(level)
      {
	case 14..1000:
            if(!this_player()->query_spell("holy_word"))
               list +=({"holy_word",});
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
         if(!this_player()->query_spell("sanctuary"))
           list +=({"sanctuary",});
	  if(!this_player()->query_spell("resist cold"))
	    list += ({"resist cold",});
      if (!this_player()->query_spell("resist fire"))
        list += ({ "resist fire", });
      if (!this_player()->query_spell("resist poison"))
        list += ({ "resist poison", });
	case 1..2:

	 break;
	  }
    } /* if PROTECTION */


  if (this_player()->query_sphere("summoning"))
    {
     switch(level)
      {
	case 14..1000:
    if (!this_player()->query_spell("symbol transformation"))
      list += ({ "symbol transformation", });
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
  if ( !this_player()->query_spell("darkness"))
    list += ({ "darkness", });
	case 1..2:
	break;
	  }
    } /* if SUMMONING */

  if (this_player()->query_sphere("plant"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
   if(!this_player()->query_spell("pacify"))
   list += ({ "pacify", });
	case 9..10:
	if (!this_player()->query_spell("thorn hedge"))
	  list += ({ "thorn hedge", });
	case 7..8:
	case 5..6:
	if (!this_player()->query_spell("neutralise poison"))
	  list += ({ "neutralise poison", });
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if PLANT */


  if (this_player()->query_sphere("sun"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
	  if(!this_player()->query_spell("light"))
	    list += ({"light",});

	 break;
	  }
    } /* if SUN */

  if (this_player()->query_sphere("weather"))
    {
     switch(level)
      {
	case 14..1000:
	case 11..13:
	case 9..10:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if WEATHER */



/*** THIS SECTION FOR MAGE SCHOOLS ****/

  if (this_player()->query_sphere("abjuration"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	  if(!this_player()->query_spell("major acid resistance"))
	    list += ({"major acid resistance",});
	  if(!this_player()->query_spell("major air resistance"))
	    list += ({"major air resistance",});
	  if(!this_player()->query_spell("major cold resistance"))
	    list += ({"major cold resistance",});
	  if(!this_player()->query_spell("major electrical resistance"))
	    list += ({"major electrical resistance",});
	  if(!this_player()->query_spell("major fire resistance"))
	    list += ({"major fire resistance",});
	  if(!this_player()->query_spell("major poison resistance"))
	    list += ({"major poison resistance",});

	case 12..13:
	  if(!this_player()->query_spell("major magical resistance"))
	    list += ({"major magical resistance",});

	case 9..11:
	
	case 7..8:
	
	case 5..6:
	  if(!this_player()->query_spell("minor acid resistance"))
	    list += ({"minor acid resistance",});
	  if(!this_player()->query_spell("minor air resistance"))
	    list += ({"minor air resistance",});
	  if(!this_player()->query_spell("minor cold resistance"))
	    list += ({"minor cold resistance",});
	  if(!this_player()->query_spell("minor electrical resistance"))
	    list += ({"minor electrical resistance",});
	  if(!this_player()->query_spell("minor fire resistance"))
	    list += ({"minor fire resistance",});
	  if(!this_player()->query_spell("minor poison resistance"))
	    list += ({"minor poison resistance",});

	case 3..4:
	  if(!this_player()->query_spell("minor magical resistance"))
	    list += ({"minor magical resistance",});

	case 1..2:

	 break;
	  }
    } /* if ABJURATION */

  if (this_player()->query_sphere("alteration"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
// WHO the hell put this in here???
// Wilt is necromancers ONLY.
// Will screw up the learn lists if it's in here twice too. --wf.
	 //if(!this_player()->query_spell("horrid wilting"))
	   //list += ({"horrid wilting",});
	case 14..15:
	case 12..13:
	case 9..11:
	case 7..8:
	case 5..6:
	 if(!this_player()->query_spell("minute meteors"))
	   list += ({"minute meteors",});

	case 3..4:
	case 1..2:
	  if(!this_player()->query_spell("burning hands"))
	    list += ({"burning hands",});
	  if(!this_player()->query_spell("shocking grasp"))
	    list += ({"shocking grasp",});
	  if(!this_player()->query_spell("light"))
	    list += ({"light"});
         if(!this_player()->query_spell("darkness")) list += ({"darkness"});

	 break;
	  }
    } /* if ALTERATION */

  if (this_player()->query_sphere("conjuration"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	case 7..8:
	case 5..6:
	  if(!this_player()->query_spell("flame arrow"))
	    list += ({"flame arrow",});
	case 3..4:
	  if(!this_player()->query_spell("acid arrow"))
	    list += ({"acid arrow",});
	case 1..2:
    if(!this_player()->query_spell("armour"))
         list += ({"armour",});

	 break;
	  }
    } /* if CONJURATION */


  if (this_player()->query_sphere("enchantment"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:
	break;
	  }
    } /* if enchantment */
  if (this_player()->query_sphere("aphelic"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	case 7..8:
	case 5..6:
	case 3..4:
         if(!this_player()->query_spell("form illusion"))
            list += ({"form illusion",});
	case 1..2:
	break;
	  }
    } /* if aphelic */

  if (this_player()->query_sphere("illusion"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	  if(!this_player()->query_spell("shadow magic lightning bolt"))
	    list += ({"shadow magic lightning bolt",});
	case 7..8:
	case 5..6:
	case 3..4:
	case 1..2:

	 break;
	  }
    } /* if ILLUSION */

  if (this_player()->query_sphere("invocation"))
    {
     switch(level)
      {
	case 18..1000:
	  if(!this_player()->query_spell("meteor swarm"))
	    list += ({"meteor swarm",});
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	  if(!this_player()->query_spell("cone of cold"))
	    list += ({"cone of cold",});
	  if(!this_player()->query_spell("ice storm"))
	    list += ({"ice storm",});
	  if(!this_player()->query_spell("major missile"))
	    list += ({"major missile",});
	case 7..8:
	case 5..6:
	  if(!this_player()->query_spell("lightning bolt"))
	    list += ({"lightning bolt",});
	  if(!this_player()->query_spell("fireball"))
	    list += ({"fireball",});
	case 3..4:
	  if(!this_player()->query_spell("minute meteors"))
	    list += ({"minute meteors",});
	  if(!this_player()->query_spell("snowball swarm"))
	    list += ({"snowball swarm",});
	case 1..2:
	  if(!this_player()->query_spell("magic missile"))
	    list += ({"magic missile",});
	  if(!this_player()->query_spell("fire burst"))
	    list += ({"fire burst",});


	 break;
	  }
    } /* if INVOCATION */
  
  if (this_player()->query_sphere("lesserdivination"))
    {
     switch(level)
      {
	case 7..1000:
	case 5..6:
	case 3..4:
/* removed Taniwha 1995, never BEEN a mage spell, cleric only */
		//if(!this_player()->query_spell("know alignment"))
	//  list += ({"know alignment",});
	case 1..2:
	  if(!this_player()->query_spell("detect magic"))
	    list += ({"detect magic",});

	 break;
	  }
    } /* if LESSERDIVINATION EVERY SPECIALIST AND WIZARD GETS THIS */

  if (this_player()->query_sphere("greaterdivination"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	case 14..15:
	case 12..13:
	case 9..11:
	break;
	  }
    } /* if GREATER DIVINATION 5TH LEVEL MAGIC AND HIGHER */


  if (this_player()->query_sphere("necromancy"))
    {
     switch(level)
      {
	case 18..1000:
	case 16..17:
	  if(!this_player()->query_spell("horrid wilting"))
	    list += ({"horrid wilting",});
	case 14..15:
	case 12..13:
	case 9..11:
	case 7..8:
	case 5..6:
	  if(!this_player()->query_spell("vampiric touch"))
	    list += ({"vampiric touch",});
    if(!this_player()->query_spell("spirit armour"))
      list += ({"spirit armour",});
	case 3..4:
	case 1..2:

	 break;
	  }
    } /* if NECROMANCY */

  if(this_player()->query_sphere("test"))
  {
     switch(level)
       {
       case 1..1000:
	if(!this_player()->query_spell("teleport"))
	  list += ({"teleport",});
	if(!this_player()->query_spell("typetest"))
	  list += ({"typetest",});
	if(!this_player()->query_spell("test"))
	  list+= ({"test",});
      break;
     }
  }  /*** TEST SPHERE, for testing spells...doh! ***/

   if(this_player()->query_guild_name()=="Grimbrand")
   {
      switch(level)
      {
         case 14..1000:
            if(!this_player()->query_spell("holy prayer"))
               list+=({"holy prayer",});
         case 11..13:
         case 9..10:
         case 7..8:
         case 5..6:
         case 3..4:
         case 1..2:
         default:
            break;
      }
   }
/*** RANGER SPHERE ***/
/*** Rangers gets priest spells at level 8 ***/
/*** Spheres include, plant and animal spheres ONLY ***/
  if (this_player()->query_sphere("ranger"))
    {
     switch(level)
      {
	case 14..1000:
            if(!this_player()->query_spell("enchant staff"))
               list+=({"enchant staff",});
	case 11..13:
            if(!this_player()->query_spell("barkskin"))
               list+=({"barkskin",});
            if(!this_player()->query_spell("thornfoot"))
               list+=({"thornfoot",});
            if(!this_player()->query_spell("know alignment"))
               list+=({"know alignment",});
	default:
	break;
	  }
    } /* if RANGER */

/*** PALADIN SPHERE ***/
/*** Paladins get priest spells at 9th level ***/
/*** Spheres, combat, clericdivination, healing, and protection up 
     to 4th level ***/
  if (this_player()->query_sphere("paladin"))
    {
     switch(level)
      {
        case 20..1000:
         if (!this_player()->query_spell("symbol transformation"))
            list += ({ "symbol transformation", });
	case 15..19:
  if (!this_player()->query_spell("prayer"))
    list += ({ "prayer", });
	case 13..14:
	case 11..12:
  if (!this_player()->query_spell("light"))
    list += ({ "light", });
	case 9..10:
  if (!this_player()->query_spell("bless"))
    list += ({ "bless",});
  if (!this_player()->query_spell("detect magic"))
    list += ({ "detect magic", });
    default:
    if (!this_player()->query_spell("know alignment"))
      list += ({ "know alignment", });
	break;
	  }
    } /* if PALADIN */

  if (this_player()->query_sphere("antipaladin"))
    {
     switch(level)
      {
        case 20..1000:
         if (!this_player()->query_spell("symbol transformation"))
            list += ({ "symbol transformation", });
	case 15..19:
  if (!this_player()->query_spell("chant"))
    list += ({ "chant", });
	case 13..14:
	case 11..12:
  if (!this_player()->query_spell("light"))
    list += ({ "light", });
	case 9..10:
  if (!this_player()->query_spell("curse"))
    list += ({ "curse",});
  if (!this_player()->query_spell("detect magic"))
    list += ({ "detect magic", });
    default:
    if (!this_player()->query_spell("know alignment"))
      list += ({ "know alignment", });
	break;
	  }
    } /* if ANTI-PALADIN */

  return list;
  } /* mixed query_spellist */

string query_spellfilename(string spell)
  {
  if (spell)
    {
    switch (spell)
      {


/*** Cleric Spell Listing, also Ranger and Paladin ****/

   case "sobriety": return "sobriety";
   case "intoxicate": return "intoxicate";
   case "holy_word":
       return ("holy_word");
   case "sanctuary":
       return ("sanctuary");
    case "symbol transformation":
      return ("sym_spell");
      case "holy storm": return "holy_stm";
   case "pacify":
      return ("pacify");
     case "shooting stars":
         return("shooting_stars");
	case "thorn hedge":
	  return ("thedge");
	case "neutralise poison":
	  return ("neutralise_poison");
      case "animate dead":
         return ("animate_dead");  // wizards and clerics share the same filename.
      case "cure light wounds":
	  return ("cure_lt");
      case "cure serious wounds":
	  return ("cure_sr");
      case "cure critical wounds":
	  return ("cure_cr");
      case "cause light wounds":
	  return ("cause_lt");
      case "cause serious wounds":
	  return ("cause_sr");
      case "cause critical wounds":
	  return ("cause_cr");
      case "energy drain":
         return ("energy_drain");
      case "heal":
	  return ("heal");
      case "holy prayer":
         return ("holy_prayer");
      case "flamestrike":
	  return ("flamestrike");
      case "light":          /** both wizard and cleric may use the ***/
	  return ("light");  /** same filename for the same spell ***/
      case "raise dead":
	  return ("raise_dead");
      case "restore":
         return ("restore");
      case "resurrect":
	  return ("resurrect");
      case "detect magic":
	  return ("det_magic");
      case "know alignment":
	  return ("know_align");
    case "resist fire":
      return ("resist_fire");
    case "resist poison":
      return ("resist_poison");
      case "resist cold":
	  return("resist_cold");
  case "darkness":
    return ("darkness");
      case "bless":
       return ("bless");
    case "curse":
      return ("curse");
    case "prayer":
     return ("prayer");
    case "chant":
      return ("chant");

/*** Mage Spell Listing ***/

      case "magic missile":
	  return ("mmissile");
      case "snowball swarm":
	  return ("snowball");
      case "lightning bolt":
	  return ("lightning");
      case "burning hands":
	  return ("burnhand");
      case "shocking grasp":
	  return ("shock_grasp");
      case "acid arrow":
	  return ("acid_arrow");
      case "flame arrow":
	  return ("flame_arrow");
      case "minute meteors":
	  return ("minute_meteor");
      case "vampiric touch":
	  return ("vamp_touch");
      case "cone of cold":
	  return ("conecold");
      case "shadow magic lightning bolt":
	  return ("shadow_lightning");
      case "minor acid resistance":
	  return ("min_acid");
      case "minor air resistance":
	  return ("min_air");
      case "minor cold resistance":
	  return ("min_cold");
      case "minor electrical resistance":
	  return ("min_elect");
      case "minor fire resistance":
	  return ("min_fire");
      case "minor magical resistance":
	  return ("min_magical");
      case "minor poison resistance":
	  return ("min_poison");
      case "major acid resistance":
	  return ("maj_acid");
      case "major air resistance":
	  return ("maj_air");
      case "major cold resistance":
	  return ("maj_cold");
      case "major electrical resistance":
	  return ("maj_elect");
      case "major fire resistance":
	  return ("maj_fire");
      case "major magical resistance":
	  return ("maj_magical");
      case "major poison resistance":
	  return ("maj_poison");
      case "fireball":
	  return ("fireball");
      case "ice storm":
	return ("ice_storm");
      case "fire burst":
	return ("fire_burst");
      case "horrid wilting":
	return("horrid_wilting");
      case "meteor swarm":
	return ("meteor_swarm");
      case "major missile":
	return ("maj_missile");
      case "armour":
   return ("armour");
     case "spirit armour":
     return ("sp_armour");
   case("delude"):
      return("dcloud");
   case("form illusion"):
      return("forming");
   case "inaudibility": return "inaud";
   case "invisibility": return "invis";
   case "read magic": return "read magic";

/*** TEST SPHERE DATA ***/

      case "teleport":
	 return ("trans");
      case "typetest":
	 return ("typetest");
      case "test":
	 return ("test");
      case "barkskin": return "barkskin";
      case "thornfoot": return "thornfoot";
      case "sticks to snakes": return "sticks_snakes";
   case "call lightning": return "call_lightning";
   case "enchant staff": return "enchant_staff";
      }
    } /* if (spell) */
  return 0;
  } /* query_spellfilename */
