/*** Armour Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Armour"
#define GP_COST 2

int bonus;
int ADJ_COST;
object shadow;

string help() {
       return
       "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "School: Conjuration\n"
       "Level: 1st\n"
       "Gp Cost: "+GP_COST+"\n"
       "Description: \n"
       "   This spell conjures a glowing protective suit of armor "
       "that surrounds the target, granting a +2 armor class bonus for a "
       "limited duration, dependant on the caster.  Conjurers gain a "
       "bonus of +1 for every 3 levels.  At 4th grants +3, 7th grants +4, "
       "and so on.\n\n";

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
  write("You start to cast "+SP_NAME+".\n");
  say(this_player()->query_cap_name()+" begins to cast a spell.\n",
     previous_object());
  return 1;
  }

mixed spell(string str, int skill, int cast)
{
  mixed ob;

  if ((int)this_player()->query_spell_effect("spell"))
    return "You are already casting a spell.\n";
  ob = find_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;

  this_player()->add_spell_effect(1, "spell", SP_NAME,
    this_object(), "hb_spell", ({ skill,ob,cast }));
  return 1;
}

int hb_spell(object attacker, mixed *params)
{
 
  int level;
  int conj_bon;
  int duration_bon;
  object *looks;
  int i;

  if (!params[1])
  {
    tell_object(this_player(),
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
  
  if(params[1]->query_armour_spell())
   {
    tell_object(this_player(),
      "The target is already affected by an Armour spell.\n");
    return 0;
   } 	


   /* Specialists spend only half guild points to cast spells native to their
    * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
 if((string)previous_object()->query_guild_name() == "conjurer")
     ADJ_COST = GP_COST/2;	  

  if (params[2] && (int)previous_object()->adjust_gp(-ADJ_COST)<0)
  {
    tell_object(previous_object(), "You are too mentally drained to cast.\n");
    return 0;
  }
    
  say((string)previous_object()->query_cap_name()+
   " chants, 'mior armanis'.\n", ({params[1],previous_object()}));
    
  if(params[1] == previous_object())
   { 
    tell_object(params[1], "You chant, 'mior armanis'.\n");
    tell_object(params[1], "You cast "+SP_NAME+" upon yourself.\n");
    say((string)previous_object()->query_cap_name()+
      " casts a spell upon "+params[1]->query_objective()+"self.\n",params[1]);
   }
  else
  {
   tell_object(previous_object(), "You chant, 'mior armanis'.\n");
   
   tell_object(params[1], (string)previous_object()->query_cap_name() +
    " chants, 'mior armanis'.\n");
   
   tell_object(params[1], "You are now surrounded in a glowing blue " 
    "armour.\n");
   
   tell_object(previous_object(), "You cast "+SP_NAME+" on "+
    (string)params[1]->query_cap_name() + ".\n");
   
   say((string)previous_object()->query_cap_name()+
    " casts a spell upon "+params[1]->query_cap_name()+" as a glowing "
    "blue armour surrounds "+params[1]->query_objective()+".\n",
       ({params[1],previous_object()}) );
  }

  conj_bon = 0;
  duration_bon = 0;

 if((string)previous_object()->query_guild_name() == "conjurer")
  {
   level = (int)previous_object()->query_level();
   conj_bon = (level-1)/3;
   duration_bon = level*30;
  }

  bonus = 2 + conj_bon;

  params[1]->adjust_tmp_ac_bon(bonus);
  params[1]->add_extra_look(this_object());  
  shadow = clone_object("/std/spells/wizard/armour_sh.c");
  shadow->setshadow(params[1]); 

  call_out("wear_off",(200+(level*20)+duration_bon),params[1]);
  return GP_COST;
}

void wear_off(object target)
{
  if(target)
  {
   target->adjust_tmp_ac_bon(-bonus);
   tell_object(target, "Your "+SP_NAME+" wears off.\n");
   target->remove_extra_look(this_object());
   target->destruct_shadow();
  }
}

string extra_look()
{
  return "Is surrounded by a suit of glowing blue armour.\n";
}
