/*** Bless Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Bless"
#define GP_COST 2

object shadow;

string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "Sphere: All\n"+
       "Level: 1st\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Description: \n"+
       "    This spell grants the target a +1 to hit in battle for "+
       "a limited duration.\n\n";

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
    return "You are already casting an spell.\n";
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
  int resist_value;
  int level;

  if (!params[1])
  {
    tell_object(this_player(),
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
 
  if (params[1]->query_blessed())
  {
    tell_object(this_player(),
      "The target is already under the effects of a Bless.\n");
    return 0;
  }

  if (params[2] && (int)previous_object()->adjust_gp(-GP_COST)<0)
  {
    tell_object(previous_object(), "You fail to draw enough energy from "+
     "your god.\n");
    return 0;
  }
    
  say((string)previous_object()->query_cap_name()+
   " chants, 'bleiso umanos'.\n", ({params[1],previous_object()}));
    
  if(params[1] == previous_object())
   { 
    tell_object(params[1], "You chant, 'bleiso umanos'.\n");
    tell_object(params[1], "You "+SP_NAME+" yourself.\n");
    say((string)previous_object()->query_cap_name()+
      " casts a spell upon "+params[1]->query_objective()+"self.\n",params[1]);
   }
  else
  {
   tell_object(previous_object(), "You chant, 'bleiso umanos'.\n");
   
   tell_object(params[1], (string)previous_object()->query_cap_name() +
    " chants, 'bleiso umanos'.\n");
   
   tell_object(params[1], (string)previous_object()->query_cap_name()+
    " kneels over you and Blesses you.\n");
   
   tell_object(previous_object(), "You kneel over "+
    (string)params[1]->query_cap_name() + " Blessing "+
    params[1]->query_objective()+".\n");
   
   say((string)previous_object()->query_cap_name()+
    " kneels over "+params[1]->query_cap_name()+" chanting softly.\n",
       ({params[1],previous_object()}) );
  }

  
  shadow = clone_object("/std/spells/cleric/bless_sh.c");
  shadow->setshadow(params[1]);

  params[1]->adjust_tmp_tohit_bon(1);  

  call_out("wear_off",100+(level*20),params[1]);
  return GP_COST;
}

void wear_off(object target)
{
  if(target)
  {
   target->adjust_tmp_tohit_bon(-1);
   target->destruct_shadow();
   tell_object(target, "Your "+SP_NAME+" wears off.\n");
  }
}
