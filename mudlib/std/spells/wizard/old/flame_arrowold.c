/*** Flame Arrow Spell ***/
/*** Created by Eerevann Tokani ***/
/* fixed for NPC's Taniwha */

#define SP_NAME "Flame Arrow"
#define GP_COST 6
#define SPELLTYPE "offensive"
#define TYPE "fire"
#define SIZE_OF_DICE 6
#define save_type "fire"

inherit "/std/spells/patch.c";

/* find_unique_match() does a find match that ensures the returned
	object list contains no duplicates
	find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed inx);
mixed find_one_match(string find,mixed inx);
int wiz_fix_damage(object caster,object victim,int damage,string save);

int ADJ_COST;
object caster;
 /*** help file ***/
string help() {
		 return
		 "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "School: Conjuration\n"
       "Level: 3rd\n"
       "Gp Cost: "+GP_COST+"\n"
       "Damage Type: "+TYPE+"\n"
       "Saving Throw: 1/2\n"
		 "Description: \n"
       "    This spell will hurl fiery bolts at a single target.  The "
       "caster gets 1 arrow for every 5 levels of experience.  A single "
       "arrow will do 4d6 damage, two would do 8d6, and so on.\n";
       

}

mixed spell(string str, int skill, int cast);

int cast_spell(string str,object cast)
{
  int skill;
  mixed ret;

  if(cast) caster = cast;
  else caster= this_player();

  if(interactive(caster))
	  str = (string)caster->expand_nickname(str);

  ret = spell(str, skill, 1);
  if (stringp(ret))
  {
	 notify_fail(ret);
	 return 0;
  }

 /******** Notifies Room and Caster that the casting has begun ********/

  tell_object(caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(caster),caster->query_cap_name()+" begins to cast an offensive spell.\n",
	  caster);
  return 1;
  }

mixed spell(string str, int skill, int cast)
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

  caster->add_spell_effect(1, SPELLTYPE, SP_NAME,
    this_object(), "hb_spell", ({ skill,ob,cast }));
  return 1;
}

int hb_spell(object caster, mixed *params)
{
 
 int damage;
 int NO_OF_DICE;
 int i;

 /*** sets up the number of dice to be used in damage calculations ***/
 
NO_OF_DICE = ((int)caster->query_level())/5;

 if(NO_OF_DICE == 0)
	 NO_OF_DICE = 1;

 NO_OF_DICE = NO_OF_DICE * 4;

 /*** CHECKS TO SEE IF TARGET IS HERE ***/
  if (!params[1])
  {
	 tell_object(caster,
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }

   /*** DEDUCTS THE GP COST OF THE SPELL, IF NOT ENOUGH, SPELL FAILS ***/
   /* Specialists spend only half guild points to cast spells native to their
    * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
  if((string)caster->query_guild_name() == "conjurer")
	 ADJ_COST = GP_COST/2;
  
  if (params[2] && (int)caster->adjust_gp(-ADJ_COST)<0)
  {
	 tell_object(caster, "You are too mentally drained to cast.\n");
    return 0;
  }
    
  tell_room(environment(caster),(string)caster->query_cap_name()+
	" chants, 'pyros os missyl'.\n", ({params[1],caster}));
    
  if(params[1] == caster)
   { 
    /*** PREVENTS CASTING OFFENSIVE MAGIC UPON ONES SELF ***/

    tell_object(params[1], "Wouldn't that be suicide?\n");
	 tell_room(environment(caster),(string)caster->query_cap_name()+
      " stops casting.\n",params[1]);
   }
  else
  {
    /*** TELL CASTER WHAT HE CHANTS ***/
	tell_object(caster, "You chant, 'pyros os missyl'.\n");
   
    /*** TELL TARGET WHAT CASTER CHANTS ***/
	tell_object(params[1], (string)caster->query_cap_name() +
    " chants, 'pyros os missyl'.\n");
   
    /*** TELL TARGET WHAT HAPPENS TO HIM AFTER SPELL GOES OFF ***/
	tell_object(params[1],  (string)caster->query_cap_name()+
      " strikes you with "+(NO_OF_DICE/4)+" bolt(s) of flame.\n");
   
    /*** TELL CASTER THE EFFECTS OF HIS SPELL AND WHO IT HIT ***/
	tell_object(caster, "You cast "+SP_NAME+" and strike "+
    (string)params[1]->query_cap_name() + " with "+(NO_OF_DICE/4)+
      " bolts of flame.\n");
   
    /*** TELLS ROOM THE EFFECTS OF THE SPELL BUT NOT CASTER OR TARGET ***/
	tell_room(environment(caster),(string)caster->query_cap_name()+
    " finishes a spell and "+params[1]->query_cap_name()+" is struck with "+
     (NO_OF_DICE/4)+" bolt(s) of flame.\n",
		 ({params[1],caster}) );
  }

   /*** FOR LOOP TO RANDOMLY GENERATE DAMAGE, NO_OF_DICE(D)SIZE_OF_DICE ***/
   /*** 1d4 = 1 to 4 damage, or 1d6 = 1-6 damage, 6d6 would be 6-36, etc ***/
  for ( i=1 ; i<=NO_OF_DICE ; i++)
    damage = damage + random(SIZE_OF_DICE)+1;

   /*** SENDS INFO TO SAVING THROW ROUTINE IN SPELLS.C, IF VICTIM MAKES ***/
   /*** SAVE, DAMAGE WILL BE HALF ***/
  damage = wiz_fix_damage(caster,params[1],damage,save_type);

	/*** SENDS INFO TO DAMAGE ROUTINE IN SPELLS.C TO DO DAMAGE TO TARGET ***/
  params[1]->spell_damage(params[1],damage,TYPE,caster);

	/*** STARTS COMBAT BETWEEN TARGET AND CASTER ***/
  params[1]->attack_by(caster);

   /*** GIVES EXP TO CASTER EQUAL TO THE VALUE RETURNED ***/
  return GP_COST;

}
