/*** Spirit Armour Spell ***/
/*** Created by Eerevann Tokani ***/


#define SP_NAME "Spirit Armour"
#define GP_COST 6
#define save_type "spells"

int bonus;
int ADJ_COST;
object shadow;
int damage;


string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "School: Necromancy\n"+
       "Level: 3rd\n"+
       "Gp Cost: "+GP_COST+"\n"+
       "Description: \n"+
    "   This spell allows the caster to surround himself with "+
       "a portion of his own life essence.  The spirit armour grants "+
       "the caster an Armour Class bonus of 5 for a limited duration.\n"+
      "   When the spell ends, the armour dissipates and the caster "+
	"loses a bit of his life essence, suffering 2-8 points of damage "+
	"unless a saving throw is succesfully made, which reduces the damage "+
   "to one half.\n"+
   "   Necromancers do not take damage from this spell, as "+
       "they are more in tune with their life essence.\n"+
     "   This spell affects the caster ONLY.\n"+
     " WARNING:  This spell COULD kill you if you take enough "+
     "damage to kill yourself when it wears off.\n\n";
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
  int duration_bon;
  
  int i;

  if (params[1] != this_player())
  {
    tell_object(this_player(),
      "Your may only cast this spell upon yourself!\n");
    return 0;
  }
  
  if(params[1]->query_spirit_armour_spell())
   {
    tell_object(this_player(),
      "You are already affected by a Spirit Armour spell.\n");
    return 0;
   } 	


   /* Specialists spend only half guild points to cast spells native to their
    * school, so GP_COST is checked and halved, if necessary.     */
  
  ADJ_COST = GP_COST;
  
 if((string)previous_object()->query_guild_name() == "necromancer")
     ADJ_COST = GP_COST/2;	  

  if (params[2] && (int)previous_object()->adjust_gp(-ADJ_COST)<0)
  {
    tell_object(previous_object(), "You are too mentally drained to cast.\n");
    return 0;
  }
    
  say((string)previous_object()->query_cap_name()+
   " chants, 'spiritis solis armanis'.\n", ({params[1],previous_object()}));
    
    tell_object(params[1], "You chant, 'spiritis solis armanis'.\n");
    tell_object(params[1], "You surround yourself with your own life "+
	"essence.\n"); 
    say((string)previous_object()->query_cap_name()+
      " finishes a spell and a gray mist surrounds "+
      	(string)previous_object()->query_objective()+".\n",params[1]); 


  duration_bon = 0;

 damage = random(4)+random(4)+2; /** simulates 2d4 **/
 damage = params[1]->spell_saving_throw(params[1],damage,save_type);

 level = (int)this_player()->query_level();

 if((string)previous_object()->query_guild_name() == "necromancer")
  {
   duration_bon = level*30;
   damage = 0;
  }

  params[1]->add_extra_look(this_object());  
  shadow = clone_object("/std/spells/wizard/sp_armour_sh.c");
  shadow->setshadow(params[1]); 

    params[1]->adjust_tmp_ac_bon(5);
  call_out("wear_off",(200+(level*20)+duration_bon),params[1]);
  return GP_COST;
}

void wear_off(object target)
{
   tell_object(target, "Your "+SP_NAME+" wears off.\n");
   target->adjust_tmp_ac_bon(-5);

  target->adjust_hp(-damage);

   if (damage > 0)
    {
   tell_object(target, "You feel some of your life essence burn away!\n");
     say(target->query_cap_name()+" is wracked with pain for a moment "+
	"as the gray mist that surrounded "+target->query_objective()+
    	" dissipates.\n",target);
    }

   target->remove_extra_look(this_object());
   target->destruct_shadow();
}

string extra_look()
{
  return "Is surrounded by a swirling gray mist.\n";
}
