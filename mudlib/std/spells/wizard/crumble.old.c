
/*** Falling Wall Spell ***/
/*** Coded by:  Taniwha ***/
/*** Fixed up by Wonderflug ***/
#define SP_NAME "Crumble Wall"
#define GP_COST 10
#define TYPE "impact" // yes this is correct it does impact damage
#define SIZE_OF_DICE 7
#define save_type "spells"
void hb_spell(object ob, mixed * params);

inherit "/std/spells/patch.c";
/* find_unique_match() does a find match that ensures the returned 
   object list contains no duplicates
   find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed in);
mixed find_one_match(string find,mixed in);
mixed spell(string str,object caster);

string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "School: Wizard Thief Only\n"+
       "Level: 5th\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Damage Type: "+TYPE+"\n"+
       "Saving Throw: None\n"+
       "Description: \n"+
       "     This spell collapses the walls in a room, crushing the "+
       "occupants with the rubble. The caster avoids damage until "+
       "the roof falls in as well.\n "+
       "Everyone in the room then takes double damage.\n"+
       "The damage caused is equal to the level of the caster d7, with "+
       "a maximum 15d7.\n";
}
int cast_spell(string str,object who)
{
  int skill;
  mixed ret;
  object caster;

   if(who) caster = who;
   else caster = this_player();
  ret = spell(str, caster);


  if (stringp(ret))
  {
    tell_room(environment(caster),ret);
    return 0;
  }

  tell_object(caster,"You begin to cast "+SP_NAME+".\n");
  tell_room(environment(caster),caster->query_cap_name()+
    " stares at the walls and they seem to shudder.\n",
	caster);
  return 1;
}
mixed spell(string str, object caster)
{
  mixed ob;
  string *xx;
  if ((int)caster->query_spell_effect("offensive"))
    return "You are already casting an offensive spell.\n";

  if ( environment(caster)->query_outside() )
    return "Nobody's stupid enough to stand around outside next "+
      "to a wall with YOU around.\n";

  if ( (int)environment(caster)->query_property("walls gone") >= 4 )
    return "There's no walls left to bring down here!\n";

  ob = find_unique_match(str, environment(caster));
  caster->add_spell_effect(1, "offensive", SP_NAME, this_object(),
   "hb_spell", ({ 1,ob, environment(caster) }));
  return 1;
}

int hb_spell(object caster, mixed *params)
{
 int damage;
 string str;
   object rubble;
 int NO_OF_DICE;
   int j;
 int i;
 NO_OF_DICE = caster->query_level();
 if(NO_OF_DICE == 0)
    NO_OF_DICE = 1;
 if (NO_OF_DICE > 15)
    NO_OF_DICE = 15;
  
  str = (string)caster->query_cap_name();
  /* to remove the caster, if he uses 'all' */
  if((i = member_array(caster, params[1])) != -1)
    params[1] = delete(params[1], i, 1);
  
  if(!sizeof(params[1])) 
  {
    tell_object(caster, "There is noone here by that name.\n");
    return 0;
  }
  if ( !params[2] || environment(caster) != params[2] )
  {
    tell_object(caster, "You lose your concentration as "+
      "you move, and flubble the spell.\n");
    return 0;
  }

 str = caster->query_cap_name();

 if (params[0] && (int)caster->adjust_gp(-GP_COST)<0)
 {
  tell_object(caster, "You are currently too "+
       "mentally drained to cast.\n");
  return 0;
 }
  i = 0;

  if ( params[0] )
  {
    tell_room(environment(caster),str + " chants, 'retro lithos' and a wall collapses.\n",
        caster);
    tell_object(caster, "You chant, 'retro lithos', the walls shudder as though "+
        "the very mortar that binds then has been stolen.\n");
  }

  rubble =  new("/std/item");
  rubble->move(environment(caster));
  rubble->reset_get();
  rubble->set_name("pile of rubble");
  rubble->add_alias("rubble");
  rubble->set_main_plural("piles of rubble");
  rubble->set_long("A pile of rubble, as you look round you realize that it's fallen from the walls here.\n");


  if ( (int)params[2]->query_property("walls gone") >= 2 )
  {
    tell_room(params[2], "As another wall falls down the entire "
    "roof collapses, to "+caster->query_cap_name()+
    "'s dismay.\n", caster);
    tell_object(caster, "You seem to have miscalculated..\n"+
      "The roof collapses upon you!\n");
    params[1] += ({ caster });
  }

  params[2]->add_property("walls gone", params[2]->query_property("walls gone")+1);
  for ( i=0;i<sizeof(params[1]);i++)
    if(params[1][i] && environment(params[1][i]) == environment(caster))
    {
        if (!living(params[1][i])) continue;
        params[1][i]->attack_by(caster);
        damage = roll(NO_OF_DICE,SIZE_OF_DICE);
        damage = wiz_fix_damage(caster,params[1][i],damage,save_type);
        params[1][i]->spell_damage(params[1][i],damage,TYPE,caster);
        tell_object(params[1][i], "A wall crumbles and you are crushed by rubble.\n");
      tell_room(params[2], params[1][i]->query_cap_name()+" is pummeled "+
        "by falling rubble.\n", params[1][i] );
    }
  return GP_COST;
}

