/*** Cone of Cold Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Cone of Cold"
#define GP_COST 10
#define SPELLTYPE "offensive"
#define TYPE "cold"
#define SIZE_OF_DICE 4
#define save_type "cold"

inherit "/std/spells/patch.c";

/* find_unique_match() does a find match that ensures the returned
   object list contains no duplicates
   find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed in);
mixed find_one_match(string find,mixed in);
int wiz_fix_damage(object caster,object victim,int damage,string save);

int ADJ_COST;

 /*** help file ***/
string help() {
		 return
       "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "School: Invocation\n"
       "Level: 5th\n"
       "Gp Cost: "+GP_COST+"\n"
       "Damage Type: "+TYPE+"\n"
       "Saving Throw: 1/2\n"
       "Description: \n"
		 "    This spell shoots a blast of cold and frost at a single target."
       "  The damage done is (caster's level)d4 + caster's level.  There "  
		 "is no maximum on this spell.\n"
       "    Example:  A 10th level Wizard would do 10d4+10.\n";


}

mixed spell(string str, object caster);

int cast_spell(string str,object cast)
{
  int skill;
  mixed ret;
  object caster;

  if(cast) caster = cast;
  caster = this_player();

  if(interactive(caster))
	  str = (string)caster->expand_nickname(str);
  
  ret = spell(str, caster);
  if (stringp(ret))
  {
    notify_fail(ret);
    return 0;
  }

 /******** Notifies Room and Caster that the casting has begun ********/

  tell_object(caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(caster),caster->query_cap_name()+" begins to cast a spell.\n",
	  caster);
  return 1;
  }

mixed spell(string str, object caster)
{
  mixed ob;

   /*** CHECKS TO SEE IF CASTER IS CASTING ANOTHER SPELL OF SAME TYPE ***/
   /*** NOT REALLY A FACTOR UNLESS PLAYER IS TRYING TO CAST SEVERAL ***/
   /*** TIMES IN RAPID SUCCESSION ***/
  if ((int)caster->query_spell_effect(SPELLTYPE))
    return "You are already casting an "+SPELLTYPE+" spell.\n";

  ob = find_one_match(str, environment(caster));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;

  caster->add_spell_effect(2, SPELLTYPE, SP_NAME,
    this_object(), "hb_spell", ({ ob }) );
  return 1;
}

int hb_spell(object caster, mixed *params, int time)
{

 int damage;
 int NO_OF_DICE;
 int level;
 int i;

  if ( time == 2 )
  {
    tell_object(caster, "A nimbus of absolute cold forms in your hands.\n");
    tell_room(environment(caster), "A nimbus of absolute cold forms "
      "between "+caster->query_cap_name()+"'s hands.\n", caster);
    return 1;
  }


 /*** sets up the number of dice to be used in damage calculations ***/
 
 NO_OF_DICE = caster->query_level();

 if(NO_OF_DICE == 0)
    NO_OF_DICE = 1;

   /*** CHECKS TO SEE IF TARGET IS HERE ***/
  if (!params[0])
  {
	 tell_object(caster,
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }

   /*** DEDUCTS THE GP COST OF THE SPELL, IF NOT ENOUGH, SPELL FAILS ***/
   /* Specialists spend only half guild points to cast spells native to their
	 * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
  if(interactive(caster) && (string)caster->query_guild_name() == "invoker")
	 ADJ_COST = GP_COST/2;

  if ( (int)caster->adjust_gp(-ADJ_COST) < 0 )
  {
	 tell_object(caster, "You are too mentally drained to cast.\n");
	 return 0;
  }

/*** TELLS ROOM WHAT THE CASTER CHANTS, NOT HEARD BY CASTER OR TARGET ***/
  tell_room(environment(caster),(string)caster->query_cap_name()+
	" chants, 'frezzus es coe'.\n", ({params[0],caster}));

  if(params[0] == caster)
	{
	 /*** PREVENTS CASTING OFFENSIVE MAGIC UPON ONES SELF ***/

	 tell_object(params[0], "Wouldn't that be suicide?\n");
	 tell_room(environment(caster),(string)caster->query_cap_name()+
		" stops casting.\n",params[0]);
	}
  else
  {
	 /*** TELL CASTER WHAT HE CHANTS ***/
	tell_object(caster, "You chant, 'frezzus es coe'.\n");

	 /*** TELL TARGET WHAT CASTER CHANTS ***/
	tell_object(params[0], (string)caster->query_cap_name() +
	 " chants, 'frezzus es coe'.\n");

	 /*** TELL TARGET WHAT HAPPENS TO HIM AFTER SPELL GOES OFF ***/
	tell_object(params[0], (string)caster->query_cap_name()+
    " makes a gesture toward you and the nimbus of cold blasts over "
    "you \nin a freezing cone.\n");

	 /*** TELL CASTER THE EFFECTS OF HIS SPELL AND WHO IT HIT ***/
	tell_object(caster, "You cast "+SP_NAME+" at "+
	 (string)params[0]->query_cap_name() + ".\n");

	 /*** TELLS ROOM THE EFFECTS OF THE SPELL BUT NOT CASTER OR TARGET ***/
	tell_room(environment(caster),(string)caster->query_cap_name()+
	 " finishes a spell as "+params[0]->query_cap_name()+" is blasted "
	  "with a cone of cold.\n",
		 ({params[0],caster}) );
  }

	/*** FOR LOOP TO RANDOMLY GENERATE DAMAGE, NO_OF_DICE(D)SIZE_OF_DICE ***/
	/*** 1d4 = 1 to 4 damage, or 1d6 = 1-6 damage, 6d6 would be 6-36, etc ***/
  for ( i=1 ; i<=NO_OF_DICE ; i++)
	 damage = damage + random(SIZE_OF_DICE)+1;

  level = caster->query_level();
  damage = damage + level;

	/*** SENDS INFO TO SAVING THROW ROUTINE IN SPELLS.C, IF VICTIM MAKES ***/
  damage = wiz_fix_damage(caster,params[0],damage,save_type);

	/*** SENDS INFO TO DAMAGE ROUTINE IN SPELLS.C TO DO DAMAGE TO TARGET ***/
  params[0]->spell_damage(params[0],damage,TYPE,caster);

	/*** STARTS COMBAT BETWEEN TARGET AND CASTER ***/
  params[0]->attack_by(caster);

	/*** GIVES EXP TO CASTER EQUAL TO THE VALUE RETURNED ***/
  return GP_COST;

}
