/*** Curse Spell ***/
/*** Created by Wonderflug, dare I associate myself with this ? ***/
 
inherit "/std/spells/patch.c";
 
#define SP_NAME "Curse"
#define GP_COST 2
 
string help() {
 return
        "\n\n"+
        "Spell Name: "+SP_NAME+"\n"+
        "Sphere: All\n"+
        "Level: 1st\n"+
        "Gp Cost: "+GP_COST+"\n"+
        "Description: \n"+
        "    This spell curses the target by -1 to hit in battle for "+
        "a limited duration.\n\n";

}

mixed spell(string str, object caster);

int cast_spell(string str,object cast)
{
  int skill;
  mixed ret;
  object caster;

  caster = cast ? cast : this_player();

  str = (string)caster->expand_nickname(str);

  ret = spell(str, caster);
  if (stringp(ret))
  {
         notify_fail(ret);
    return 0;
  }
  tell_object(caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(caster),caster->query_cap_name()+" begins to "+
        "cast a spell.\n",
        caster);
  return 1;
}


mixed spell(string str, object caster)
{
  mixed ob;
 
  if ((int)caster->query_spell_effect("spell"))
    return "You are already casting a spell.\n";
  ob = find_one_match(str, environment(caster));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;
 
  caster->add_spell_effect(1, "spell", SP_NAME,
    this_object(), "hb_spell", ({ ob }));
  return 1;
}
 

int hb_spell(object caster, mixed *params, int time)
{
  int level;
 
  if (!params[0])
  {
         tell_object(caster,
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
 
  if (params[0]->query_property("clericcursed"))
  {
         tell_object(caster,
      "The target is already under the effects of a Curse.\n");
    return 0;
  }
 

  if ((int)caster->adjust_gp(-GP_COST)<0)
  {
         tell_object(caster, "You fail to draw enough energy from "+
     "your god.\n");
    return 0;
  }
 
  tell_room(environment(caster),(string)caster->query_cap_name()+
        " chants, 'mali umanos'.\n", ({params[0],caster}));
 
  if(params[0] == caster)
        {
    tell_object(params[0], "You chant, 'mali umanos'.\n");
         tell_object(params[0], "You "+SP_NAME+" yourself.  Bright idea.\n");
         tell_room(environment(caster),(string)caster->query_cap_name()+
      " casts a spell upon "+params[0]->query_objective()+"self.\n",params[0]);
   }   
  else
  {
        tell_object(caster, "You chant, 'mali umanos'.\n");
 

        tell_object(params[0], (string)caster->query_cap_name() +
    " chants, 'mali umanos'.\n");
       
        tell_object(params[0], (string)caster->query_cap_name()+
    " touchs you muttering a nasty curse!\n");
       
        tell_object(caster, "You touch "+
    (string)params[0]->query_cap_name() + " while muttering a nasty curse!\n");
       
        tell_room(environment(caster),(string)caster->query_cap_name()+
    " touches "+params[0]->query_cap_name()+" while muttering nastily.\n",
                 ({params[0],caster}) );
  }
 
  level = (int)caster->query_level();
 
  params[0]->adjust_tmp_tohit_bon(-1);
  params[0]->add_static_property("clericcursed", 1);
 
  call_out("wear_off",100+(level*10),params[0]);
  return GP_COST;
}
 
void wear_off(object target)
{
  if(target)
  {
   target->adjust_tmp_tohit_bon(1);
   target->remove_static_property("clericcursed");
   tell_object(target, "Your "+SP_NAME+" thankfully wears off.\n");
  }
}


