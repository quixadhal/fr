
#include "tweaks.h"
/*** Poison ***/
/*** Created by Taniwha ***/
 

#define SP_NAME "Poison"
#define SPELLTYPE "offensive"      
#define TYPE "magical"
#define save_type "poison"
#define GP STINK_GP
#define LEVEL POISON_LEVEL
#define LOCKOUT POISON_LOCKOUT


string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "School: Invocation\n"+
       "Level: "+LEVEL+"\n"+
       "Gp Cost: "+GP+"\n"+
       "Damage Type: Physical (poison)\n"+
       "Saving Throw: Level Constitution and Resist Poison\n"+
       "Description: \n"+
       "    This spell causes the victim lose HP at a rate dependent on "+
       " the victims constitution. There is an initial saving throw based "+
       " on relative level and constitution. And a 100% save for resist "+
       " poison. Note that the intended victim will become immune for a "+
       " period if the initial attack fails. "+
       " The strength of the poison depends on casters guild and level. "+       
       " Lolth priests poison is twice as powerful as that of other "+
       " priests at the same level. "+
       " Neutralize poison will neutralize this spell. "+
       "\n";
}


int cast_spell(string str, object who)
{
   object *vlist;
   object victim;
   object caster;
   object ob;
   int damage;

   if(who) caster = who;
   else caster = TP;
   vlist = find_match(str,environment(caster));
   if(sizeof(vlist)) victim = vlist[0];
   if( !victim ) 
   {
        write("Poison who ?\n");
        return 1;
   }
  write("You start to cast "+SP_NAME+".\n");
  if( caster->adjust_gp(-GP)<0)
  { 
       write("You are too mentally drained to cast.\n");
       return 1;
   }
   say((string)caster->query_cap_name()+
      " chants, \"Toxoplasmosis\".\n", ({ caster }));
   // saving throws
   if((int)victim->query_property("poisoned") || (int)victim->query_property("poison") || (int)victim->query_property("dead") ||
      (int)victim->query_property("undead") )
   {
      write((string)victim->query_cap_name()+" cannot be poisoned.\n");
       victim->attack_by(caster);
       return 1;
   }
   if( random((int)victim->query_level()+(int)victim->query_con()) >
     (random((int)caster->query_level() * 2) )
   )
   {
      victim->add_timed_property("poison",50,(int)caster->query_level() * 10);
      write("Oops your victim was unharmed by the attack.\n");
      victim->attack_by(caster);
      return 1;
   }
   damage = (int)caster->query_level()/POISON_MOD;
   if((string)caster->query_guild_name() == "Lolth") damage *= 2;
   
   victim->add_timed_property("poisoned",1,((int)caster->query_level() + 100));
   ob = clone_object(SPELLS+"poisoned.c");
   ob->set_get();
   ob->move(victim);
   ob->reset_drop();
   ob->reset_get();
   ob->set_spell(caster,damage);
   tell_room(environment(caster),(string)caster->query_cap_name()+ " scratches and poisons "+
   (string)victim->query_cap_name()+" leaving a festering wound.\n",({ }));
   victim->attack_by(caster);
   return 1;
}


