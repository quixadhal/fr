
/* Thorn Hedge object, actually a "dead" invisible NPC 
 * Effects based on level and dex, once cast this isn't a spell 
 * rather a local physical hazard
 * caster gets a bonus 10:1 chance of not being affected
 */ 
#include "tweaks.h"
inherit "/obj/monster";
#define THORN_DAMAGE (BLADE_DAMAGE/3)

int hb;
object mycaster;
int mycount;
void do_spell(object ob);

int dispell_me()
{
   tell_room(ETO,"The vines writhe, and retreat back into the ground.\n",({ }));
   this_object()->dest_me();
   return 1;
}
void do_death(object ob) { }
void attack_by(object ob)
{
   ob->stop_fight(this_object());
   tell_room(ETO,(string)ob->query_cap_name()+
      " stupidly attacks a thorn hedge.\n");
   mycaster->attack_by(ob);
   do_spell(ob);
}
int do_cut(string str)
{
   if(random(10))
   {
      tell_object(TP,"You are blocked by thorns!\n");
      tell_room(ETO,(string)TP->query_cap_name()+" is prevented from leaving by the thorns.\n",({ TP }));
      do_spell(this_player());
      return 1;
   }
   return 0;
}
void init()
{
   ::init();
   set_heart_beat(1);
   add_action("do_cut","s*outh");
   add_action("do_cut","n*orth");
   add_action("do_cut","e*ast");
   add_action("do_cut","u*p");
   add_action("do_cut","d*own");
   add_action("do_cut","w*est");
   add_action("do_cut","se");
   add_action("do_cut","sw");
   add_action("do_cut","ne");
   add_action("do_cut","nw");
   add_action("do_cut","southwest");
   add_action("do_cut","southeast");
   add_action("do_cut","northwest");
   add_action("do_cut","northeast");

   add_action("do_cut","sn*eak");

}

void do_spell(object ob)
{
   int odds;
   int i;

   if(ob == this_object()) return;
   if(ob->query_property("dead")) return;
   if( find_living((string)ob->query_name()) )
   {
       if(IMMORTLOCK) if(ob->query_creator()) return;
       if(ob == mycaster) odds = 10 * (int)ob->query_level();
       else odds = (int) ob->query_level();
       switch(random(odds) )
       {
       case 0:
       case 1:
       case 2:
       case 3:
       case 4:
       case 5:
	  if(random((int)ob->query_dex()) < 8 )
	  {
	     if(member_array(ob,mycaster->query_attacker_list()) >= 0 && present(mycaster) )
	     {
	    if(!interactive(ob))
		   ob->adjust_hp(-(THORN_DAMAGE*4));
	    else ob->adjust_hp(-THORN_DAMAGE);
	     }
	 else 
	 {
	   if(!interactive(ob)) ob->adjust_hp(-THORN_DAMAGE);
	    else if(ob->query_hp() > THORN_DAMAGE) ob->adjust_hp(-THORN_DAMAGE);
	 }
	  }
	  tell_object(ob,"You get scratched by thorns!\n");
	  tell_room(ETO,(string)ob->query_cap_name()+" is scratched by thorns!\n",({ ob }) );
       break;
       }
    }
}


void set_spell(object ob,int length)
{
	mycaster = ob;
	mycount = length;
}

void setup()
{
   set_name("thorn hedge");
   set_short("thorn hedge");
   set_race("monster");
   add_alias("hedge");
   add_alias("thorns");
   set_gender(0);
   add_property("dead",1);
   set_long("\n A hedge of thorn covered vines surrounds the area"+
   "\n");
   set_spell(this_object(),10);
}
void heart_beat()
{
     object *olist;
     object ob;
     int i;
     ::heart_beat();
      hb++;
     if(!mycaster) 
     {
	dispell_me();
     }
     if(hb > mycount)
     {
	dispell_me();
     } 
     olist = all_inventory(ETO);
     for(i = 0; i < sizeof(olist); i++)
     {
	do_spell(olist[i]);
     }
}     

