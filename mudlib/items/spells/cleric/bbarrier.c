
#include "tweaks.h"
/*** Balde Barrier ***/
/*** Created by Taniwha ***/
 

#define SP_NAME "Blade Barrier"
#define SPELLTYPE "offensive/defensive"      
#define TYPE "magical"
#define SIZE_OF_DICE 4
#define save_type "spells"
#define GP BBARIER_GP
#define LEVEL BBARIER_LEVEL
#define LOCKOUT BBARIER_LOCKOUT

object room;
int hb;

string help() {
       return
       "\n\n"+
       "Spell Name: "+SP_NAME+"\n"+
       "Level: "+LEVEL+"\n"+
       "Gp Cost: "+GP+"\n"+
       "Damage Type: Physical\n"+
       "Saving Throw: Level Dexterity\n"+
       "Description: \n"+
       "    This spell will create a wall of blades around the caster."+
       "Anyone in the room will take damage if they don't make the saving "+
       "throw, and extra damage if they are attacking the caster. "+
       "The spell lasts 1 round /level +3 , "+
       "until it is dispelled, or until the caster dies or leaves the game. "
       "Also note the caster gets a 10* bonus save, not total immunity. "+
       "\n";
}


int cast_spell(string str)
{
  
  room = ETP;  
  if((TP->query_hb_diff(hb) < LOCKOUT) || (TP->query_level()< LEVEL) )
  {
       tell_object(TP,"You just can't muster the concentration to cast yet.\n");
       return 0;
  }
  hb = TP->query_hb_counter();
  write("You start to cast "+SP_NAME+".\n");
  if( TP->adjust_gp(-GP)<0)
  { 
       tell_object(TP, "You are too mentally drained to cast.\n");
       return 0;
   }
   say((string)TP->query_cap_name()+
      " chants, \"Deus Clavius\".\n", ({ TP }));

   call_out("make_spell",1,TP);   
   return 1;
}
int cast(string str)
{
   return(cast_spell(str));
}

void make_spell(mixed tp)
{
   object ob;
   ob = clone_object(SPELLS+"blader.c");
   ob->move(room);
   ob->set_spell(tp,3+(int)tp->query_level());
   tell_room(room,"The ground rips open and a wall of blades springs up!\n",({ }) );
}


