/*** Acid Arrow Spell ***/
/*** Completely Rewritten by Wonderflug, June '95 ***/
/*** Created by Eerevann Tokani ***/
/*** Revised by Taniwha ***/

inherit "/std/spells/patch.c";

/* find_unique_match() does a find match that ensures the returned 
   object list contains no duplicates
	find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed in);
mixed find_one_match(string find,mixed in);
int wiz_fix_damage(object caster,object victim,int damage, string save);


#define SP_NAME "Acid Arrow"
#define GP_COST 4
#define SPELLTYPE "offensive"
#define TYPE "acid"
#define SIZE_OF_DICE 4
#define save_type "acid"

int ADJ_COST;
object caster;

 /*** help file ***/
string help() {
       return
       "\n\n"+
		 "Spell Name: "+SP_NAME+"\n"+
       "School: Conjuration\n"+
		 "Level: 2nd\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Damage Type: "+TYPE+"\n"+
       "Saving Throw: None\n"+
       "Description: \n"+
		 "    This spell conjures magical globules of acid.  These "+
       "arrows are then hurled at the target and do 2d4 points of damage."+
       "One arrow gets created per 4 levels of experience.\n";
       

}

mixed spell(string str, object caster);

int cast_spell(string str,object cast)
{
  int skill;
  mixed ret;
  object caster;

  if(cast) caster = cast;
  else caster = this_player();

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
  tell_room(environment(caster),caster->query_cap_name()+" begins to cast a "+
    "spell.\n", ({caster}));
  return 1;
  }

mixed spell(string str, object caster)
{
  mixed ob;

  if ((int)caster->query_spell_effect(SPELLTYPE))
	 return "You are already casting an "+SPELLTYPE+" spell.\n";

  ob = find_one_match(str, environment(caster));
  if (sizeof(ob))
	 ob = ob[0];
  else
	 return "Your target is not here.";

  caster->add_spell_effect(1, SPELLTYPE, SP_NAME,
    this_object(), "hb_spell", ({ 1, ob }));
  return 1;
}


int hb_spell(object caster, mixed *params)
{
 int i; 
 int damage;
 int num_arrows;
 
 num_arrows = (int)caster->query_level() / 4;

   /*** CHECKS TO SEE IF TARGET IS HERE ***/
  if (!params[1] || environment(caster) != environment(params[1]))
  {
	 tell_object(caster,
      "Your target seems to have left.\n");
    return 0;
  }

  ADJ_COST = GP_COST;
  
  if(interactive(caster) && (string)caster->query_guild_name() == "conjurer")
	 ADJ_COST = GP_COST/2;

  if ((int)caster->adjust_gp(-ADJ_COST)<0)
  {
	 tell_object(caster, "You are too mentally drained to cast.\n");
	 return 0;
  }
    
/*** TELLS ROOM WHAT THE CASTER CHANTS, NOT HEARD BY CASTER OR TARGET ***/
  tell_room(environment(caster),(string)caster->query_cap_name()+
	" chants, 'corosez myssle'.\n", ({params[1],caster}));
    

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
	tell_object(caster, "You chant, 'corosez myssle'.\n");
   
    /*** TELL TARGET WHAT CASTER CHANTS ***/
	tell_object(params[1], (string)caster->query_cap_name() +
	 " chants, 'corosez myssle'.\n");

    /*** TELL TARGET WHAT HAPPENS TO HIM AFTER SPELL GOES OFF ***/
	tell_object(params[1], caster->query_cap_name()+" spreads his arm wide "+
          " and "+num_arrows+" blobs of acid appear and array around "+
	  (string)caster->query_objective()+".\n\nThe blobs streak toward you "
	  "and splash all over you, and your flesh bubbles and\nburns as the "+
          " acid eats it away.\n");
   
	 /*** TELL CASTER THE EFFECTS OF HIS SPELL AND WHO IT HIT ***/
	tell_object(caster, num_arrows+" blobs of acid appear in front of "+
          "you.\n\nYou launch them into "+(string)params[1]->query_cap_name()+ 
          ", who screams in pain as the acid sears "+params[1]->query_possessive()+
	  " flesh!\n");


    /*** TELLS ROOM THE EFFECTS OF THE SPELL BUT NOT CASTER OR TARGET ***/
	tell_room(environment(caster),(string)caster->query_cap_name()+
	 " finishes a spell and launches "+num_arrows+" blobs of acid "+
	 "at "+params[1]->query_cap_name()+".\n\n"+params[1]->query_cap_name()+
         " howls in pain as "+params[1]->query_possessive()+" flesh bubbles and "+
         "drips to the ground.\n",
	({params[1],caster}) );
  }

  /* damage is 2d4 / 4 levels; do each arrow individually, since 
   * some defense spells depend on how many 'hits' get done 
   */

  for (i=0;i<num_arrows;i++)
  {
    damage = 0;
    damage = random(SIZE_OF_DICE) + random(SIZE_OF_DICE) +2;
    damage = wiz_fix_damage(caster,params[1],damage,save_type);
	/*** SENDS INFO TO DAMAGE ROUTINE IN SPELLS.C TO DO DAMAGE TO TARGET ***/
    params[1]->spell_damage(params[1],damage,TYPE,caster);
	/*** STARTS COMBAT BETWEEN TARGET AND CASTER ***/
    params[1]->attack_by(caster);
  }
	/*** GIVES EXP TO CASTER EQUAL TO THE VALUE RETURNED ***/
  return GP_COST;

}


