/*** Light Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Light"
#define GP_COST 2
#define SPELLTYPE "misc"

int ADJ_COST;

string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "School: Alteration\n"+
       "Level: 1st\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Description: \n"+
       "    This spell creates light allowing you to see in dark rooms.\n\n";
       

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

  if ((int)this_player()->query_spell_effect(SPELLTYPE))
    return "You are already casting an "+SPELLTYPE+" spell.\n";
  ob = find_match(str, environment(this_player()));
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
/*** variables, dependant upon spell ***/


  if (!params[1])
  {
    tell_object(this_player(),
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
   
   /* Specialists spend only half guild points to cast spells native to their
    * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
  if((string)previous_object()->query_guild_name() == "transmuter")
    ADJ_COST = GP_COST/2;
  
  if (params[2] && (int)previous_object()->adjust_gp(-ADJ_COST)<0)
  {
    tell_object(previous_object(), "You are too mentally drained to cast.\n");
    return 0;
  }
    
  say((string)previous_object()->query_cap_name()+
   " chants, 'blah blah blah'.\n", ({params[1],previous_object()}));
    
  if(params[1] == previous_object())
   { 

   /** when cast upon self ***  only need altar chant part ***/

    tell_object(params[1], "You chant, 'magius lios'.\n");
    tell_object(params[1], "You cast "+SP_NAME+" upon yourself.\n");
    say((string)previous_object()->query_cap_name()+
      " casts a spell upon "+params[1]->query_objective()+"self.\n",params[1]);
   }
  else
  {
   tell_object(previous_object(), "You chant, 'magius lios'.\n");
   
   tell_object(params[1], (string)previous_object()->query_cap_name() +
    " chants, 'maguis lios'.\n");
   
   tell_object(params[1], (string)previous_object()->query_cap_name() + 
      " casts light on you.\n");
   
   tell_object(previous_object(), "You cast "+SP_NAME+" on "+
    (string)params[1]->query_cap_name() + ".\n");
   
   say((string)previous_object()->query_cap_name()+
    " casts a light upon "+params[1]->query_cap_name()+".\n",
       ({params[1],previous_object()}) );
  }

  /*** specific spell stuff here ***/
   
   params[1]->set_light(60);
   call_out("wear_off",100+((params[1]->query_level())+400), params[1]);

 return GP_COST;
}

void wear_off(object target)
{
 target->set_light(0);
 tell_object(target,"Your globe of light disappears.\n");
 say(target->query_cap_name()+"'s globe of light disappears.\n",target);
 
}
