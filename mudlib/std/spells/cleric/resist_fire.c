 
/*** Resist Fire Spell ***/
/*** Blame this spell on Caanan ***/
inherit "/std/spells/patch.c";
 
/* find_unique_match() does a find match that ensures the returned 
   object list contains no duplicates
   find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed in);
mixed find_one_match(string find,mixed in);
 
 
#define SP_NAME "Resist Fire"
#define GP_COST 4
#define TYPE "fire"
 
 
string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "Sphere: Protection\n"+
       "Level: 2nd\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Description: \n"+
       "    This spell reduces damage done by Fire based attacks "+
       "by 50%.  The duration is based upon the casters level.\n\n";
       
 
}
 
mixed spell(string str, int skill, int cast, object caster);
 
int cast_spell(string str, object cast)
{
  int skill;
  mixed ret;
  object caster;
 
  caster = cast ? cast : this_player();
 
  str = (string)caster->expand_nickname(str);
 
  ret = spell(str, skill, 1, caster);
  if (stringp(ret))
  {
    notify_fail(ret);
    return 0;
  }
  tell_object("You start to cast "+SP_NAME+".\n");
  tell_room(environment(caster), caster->query_cap_name()+" begins to cast a
            spell.\n", caster);
  return 1;
  }
 
mixed spell(string str, int skill, int cast, object caster)
{
  mixed ob;
 
  if ((int)caster->query_spell_effect("defensive"))
    return "You are already casting an defensive spell.\n";
  ob = find_one_match(str, environment(caster));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;
 
 caster->add_spell_effect(1, "defensive", SP_NAME,
    this_object(), "hb_spell", ({ skill,ob,cast }));
  return 1;
}
 
int hb_spell(object caster, mixed *params)
{
  int resist_value;
  int level;
 
  if (!params[1])
  {
    tell_object(caster,
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
  if (params[2] && (int)caster->adjust_gp(-GP_COST)<0)
  {
    tell_object(caster, "You fail to draw enough energy from "+
     "your god.\n");
    return 0;
  }
 
  tell_room(environment(caster), (string)caster->query_cap_name()+
   " chants, 'donum sweatan itios'.\n", ({params[1],caster}));
 
  if(params[1] == caster)
   {
    tell_object(params[1], "You chant, 'donum sweatan itios'.\n");
    tell_object(params[1], "You cast "+SP_NAME+" upon yourself.\n");
    tell_room(environment(caster), (string)caster->query_cap_name()+
      " casts a spell upon "+params[1]->query_objective()+"self.\n",params[1]);
   }
  else
  {
   tell_object(caster, "You chant, 'donum sweatan itios'.\n");
 
   tell_object(params[1], (string)caster->query_cap_name() +
    " chants, 'donum sweatan itios'.\n");
 
   tell_object(params[1], "You feel resistant to Fire attacks.\n");
 
   tell_object(caster, "You cast "+SP_NAME+" on "+
    (string)params[1]->query_cap_name() + ".\n");
 
   tell_room(environment(caster), (string)caster->query_cap_name()+
    " casts a spell upon "+params[1]->query_cap_name()+".\n",
       ({params[1],caster}) );
  }
 
  resist_value = 50;
 
  params[1]->add_timed_property(TYPE, resist_value,
      50+((int)caster->query_level()));
  
  return GP_COST;
}
