/*** Cone of Cold Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Cone of Cold"
#define GP_COST 10
#define SPELLTYPE "offensive"
#define TYPE "cold"
#define SIZE_OF_DICE 4
#define save_type "spells"

int ADJ_COST;

inherit "/std/spells/patch.c";
mixed find_unique_match(string find, mixed in);
mixed find_one_match(string find, mixed in);
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

mixed spell(string str, int skill, int cast);

int cast_spell(string str)
{
  int skill;
  mixed ret;

  str = (string)this_player()->expand_nickname(str);
  
  ret = spell(str, skill, 1);
  if (stringp(ret))
  {
    notify_fail(ret);
    return 0;
  }

 /******** Notifies Room and Caster that the casting has begun ********/

  write("You start to cast "+SP_NAME+".\n");
  say(this_player()->query_cap_name()+" begins to cast an offensive spell.\n",
     previous_object());
  return 1;
  }

mixed spell(string str, int skill, int cast)
{
  mixed ob;

   /*** CHECKS TO SEE IF CASTER IS CASTING ANOTHER SPELL OF SAME TYPE ***/
   /*** NOT REALLY A FACTOR UNLESS PLAYER IS TRYING TO CAST SEVERAL ***/
   /*** TIMES IN RAPID SUCCESSION ***/
  if ((int)this_player()->query_spell_effect(SPELLTYPE))
    return "You are already casting an "+SPELLTYPE+" spell.\n";
  
  ob = find_one_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;

  this_player()->add_spell_effect(1, SPELLTYPE, SP_NAME,
    this_object(), "hb_spell", ({ skill,ob,cast }));
  return 1;
}

int hb_spell(object attacker, mixed *params)
{
 
 int damage;
 int NO_OF_DICE;
 int level;
 int i;

 /*** sets up the number of dice to be used in damage calculations ***/
 
 NO_OF_DICE = this_player()->query_level();

 if(NO_OF_DICE == 0)
    NO_OF_DICE = 1;
   
   /*** CHECKS TO SEE IF TARGET IS HERE ***/
  if (!params[1])
  {
    tell_object(this_player(),
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }

   /*** DEDUCTS THE GP COST OF THE SPELL, IF NOT ENOUGH, SPELL FAILS ***/
   /* Specialists spend only half guild points to cast spells native to their
    * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
  if((string)previous_object()->query_guild_name() == "invoker")
    ADJ_COST = GP_COST/2;
  
  if (params[2] && (int)previous_object()->adjust_gp(-ADJ_COST)<0)
  {
    tell_object(previous_object(), "You are too mentally drained to cast.\n");
    return 0;
  }
    
/*** TELLS ROOM WHAT THE CASTER CHANTS, NOT HEARD BY CASTER OR TARGET ***/
  say((string)previous_object()->query_cap_name()+
   " chants, 'frezzus es coe'.\n", ({params[1],previous_object()}));
    
  if(params[1] == previous_object())
   { 
    /*** PREVENTS CASTING OFFENSIVE MAGIC UPON ONES SELF ***/

    tell_object(params[1], "Wouldn't that be suicide?\n");
    say((string)previous_object()->query_cap_name()+
      " stops casting.\n",params[1]);
   }
  else
  {
    /*** TELL CASTER WHAT HE CHANTS ***/
   tell_object(previous_object(), "You chant, 'frezzus es coe'.\n");
   
    /*** TELL TARGET WHAT CASTER CHANTS ***/
   tell_object(params[1], (string)previous_object()->query_cap_name() +
    " chants, 'frezzus es coe'.\n");
   
    /*** TELL TARGET WHAT HAPPENS TO HIM AFTER SPELL GOES OFF ***/
   tell_object(params[1], (string)previous_object()->query_cap_name()+
      " blasts you with a cone of cold.\n");
   
    /*** TELL CASTER THE EFFECTS OF HIS SPELL AND WHO IT HIT ***/
   tell_object(previous_object(), "You cast "+SP_NAME+" at "+
    (string)params[1]->query_cap_name() + ".\n");
   
    /*** TELLS ROOM THE EFFECTS OF THE SPELL BUT NOT CASTER OR TARGET ***/
   say((string)previous_object()->query_cap_name()+
    " finishes a spell as "+params[1]->query_cap_name()+" is blasted "
     "with a cone of cold.\n",
       ({params[1],previous_object()}) );
  }

   /*** FOR LOOP TO RANDOMLY GENERATE DAMAGE, NO_OF_DICE(D)SIZE_OF_DICE ***/
   /*** 1d4 = 1 to 4 damage, or 1d6 = 1-6 damage, 6d6 would be 6-36, etc ***/
  for ( i=1 ; i<=NO_OF_DICE ; i++)
    damage = damage + random(SIZE_OF_DICE)+1;
 
  level = this_player()->query_level();
  damage = damage + level;

   /*** SENDS INFO TO SAVING THROW ROUTINE IN SPELLS.C, IF VICTIM MAKES ***/
   /*** SAVE, DAMAGE WILL BE HALF ***/
  damage = params[1]->spell_saving_throw(params[1],damage,save_type);

   /*** SENDS INFO TO DAMAGE ROUTINE IN SPELLS.C TO DO DAMAGE TO TARGET ***/
  params[1]->spell_damage(params[1],damage,TYPE);

   /*** STARTS COMBAT BETWEEN TARGET AND CASTER ***/
  params[1]->attack_by(previous_object());

   /*** GIVES EXP TO CASTER EQUAL TO THE VALUE RETURNED ***/
  return GP_COST;

}
