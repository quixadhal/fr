
#include "/std/commands/tweaks.h"
int hb_spell(object me, mixed *params);


int slice(string str, object doer) 
{
  int skill,s1,i;
  int j,x;
  int damage;
  int bonus;
  int hits;
  int rate;
  int extrahits;
  object me;
  object *weap;
  object v_round;
  object protectr;
  object *vlist;
  object victim;
  me = doer ? doer : this_player();
  str = me->expand_nickname(str);

  me->adjust_gp(-3); // Lose some GP whatever, to stop slice being spammed
   if(me->query_gp() <= 0) return;

  if (!str)
  {
    notify_fail("Who are you trying to slice?\n");
    return 0;
  }
  vlist = find_match(str,environment(me));
  weap =   (object *)me->query_held_ob();

    
  if(!sizeof(vlist)) {
    notify_fail("Fantasizing about slicing someone?  Try someone "
      "that is here.\n");
    return 0;  }
    
  victim=vlist[0];
  
  if(victim->query_hide_shadow()) {
     notify_fail("Fantasizing about slicing someone?  Try someone "
       "that is here.\n");
     return 0; } 
    
  if(me->query_property("pacify_on")) {
     notify_fail("Something prevents you from doing this\n");
     return 0; }

  if(victim->query_dead()) {
     notify_fail("Attacking up a ghost?\n");
     return 0;  }
  
  if(victim->query_property("pacify_on"))  {
     notify_fail("This one's way too harmless to attack.\n");
     return 0;  }
     
  if(victim == me)  {
     notify_fail("Slicing yourself? That's bright.\n");
     return 0;  } 
  
  if(me->query_property("slicing")) {
     notify_fail("You try to work up to a slice but are too "
      "unskilled and waste some effort.\n");
     return 0;  }
  
  if ((!weap[0] && !weap[1]) || (weap[0]->query_attack_type() != 1 && 
  				 weap[1]->query_attack_type() != 1))   {
    notify_fail("Slice with what?\n");
    return 0; }

  
  me->add_timed_property("slicing", 1, 
    (100/(int)me->query_level()));
    
  bonus = (me->query_dex()-15)*10;
  if(environment(this_player())->query_light()>40)   bonus-=60;
  if (bonus < -60)  bonus = -60;
  x=me->query_dex()+me->query_level();
  
  switch(x) {
  
  	case 0..19:
   	hits=1;
   	rate=1;
   	extrahits=0;
   	break;
   	
   	case 20..29:
   	hits=2;
   	rate=2;
   	extrahits=0;
	break;

	case 30..39:
	hits=2;
	rate=1;
	extrahits=1;
	break;   	

	case 40..49:
	hits=3;
	rate=1;
	extrahits=1;
	break;
	
	case 50..59:
	hits=3;
	rate=1;
	extrahits=2;
	break;
	
	case 60..69:
	hits=6;
	rate=2;
	extrahits=0;
	break;
	
	default:
	hits=6;
	rate=2;
	extrahits=1;
	break;
	}  

  tell_object(victim,(string)me->query_cap_name()+" twirls "
    "and slices into you with a flurry of lightning\nquick attacks!\n");

  tell_object(me, "You slice into "+victim->query_cap_name()+
    " with a flurry of lightning quick attacks!\n");

  tell_room(environment(me), me->query_cap_name()+
    " twirls "+me->query_possessive()+" blades and slices into "+
    victim->query_cap_name()+" with a flurry of\n"
    "lightning quick attacks!\n", ({ me, victim }) );
 
  victim->attack_by(me);
  
  me->add_spell_effect(hits, "offensive","slice", this_object(),
    "hb_spell", ({ bonus,victim,hits, rate }));
  
  hb_spell(me,({bonus,victim,hits, extrahits}));

  return 1;
}


int hb_spell(object me, mixed *params)
{
  object protectr,victim,v_round;
  object *weap;
  int bonus, dam_bonus, i;
  int damg = 0;    // Event trigger - Radix
   if(me->query_gp() < 3) return;

  bonus = params[0];
  dam_bonus=bonus/20;     // this will either be bonus or penalty, depending on light
  victim = params[1];
  weap =  (object *)me->query_held_ob();

  if( !victim || (environment(me) !=  environment(victim)) )
    return 0;
 
  if(me->query_property("noguild")) return 0;

  if(environment(me)->query_property("noguild")) 
    return 0;

  protectr =  victim->query_protector();

  if( protectr && 
      environment(protectr) !=  environment(victim) ) 
    protectr = 0;
  
  if(victim->query_property("no_slice")) 
    bonus = 0;

   me->adjust_tmp_damage_bon(dam_bonus);
  me->adjust_tmp_tohit_bon(bonus);
 
  if(me->adjust_gp(-3)) {
 
     for(i = 0; i < params[3]; i++) {
    
        
        if ( protectr && protectr->query_protect_valid(victim, me) ) {
          tell_room(environment(me), protectr->query_cap_name()+
            " valiantly protects "+victim->query_cap_name()+".\n",
            ({ me, protectr, victim }) );
          tell_object(victim, protectr->query_cap_name()+
            " valiantly protects you!\n");
          tell_object(me, protectr->query_cap_name()+
            " protects "+ victim->query_cap_name()+" from your attack!\n");
          tell_object(protectr, "You protect "+victim->query_cap_name()+
            " from "+me->query_cap_name()+"'s attack!\n");
          v_round = protectr;
        }   
        else v_round = victim;
          
        if(weap[0] && weap[0]->query_attack_type() == 1)
        {
            damg = weap[0]->weapon_attack(v_round,me);
            weap[0]->event_slice(damg,me,v_round);
        }
        if(weap[1] && weap[1]->query_attack_type() == 1)
        {
            damg = weap[1]->weapon_attack(v_round,me);
            weap[1]->event_slice(damg,me,v_round);
        }
        v_round->attack_by(me);
    
        params[2]--;
        if( params[2] <= 0 ) call_out("remove_slice",0,me);
     } /* for */ 
     
  }  /* if gp */
  else tell_object(me,"You cannot keep on slicing.\n");

  me->adjust_tmp_tohit_bon(-bonus);
  me->adjust_tmp_damage_bon(-dam_bonus);
  return 1;
}

void remove_slice(object me) {
    if(me)  me->remove_spell_effect("slice");
}

string help(string str) {
  return
    "Syntax: slice <person>\n\n"
    "Slice is a Drow Warrior attack based on their skill with bladework. "
    "You get a series of extra blows, the number based "
    "upon your level and dexterity.  You also get a tohit and "
    "damage bonus, depending on your dexterity.  Both of "
    "these are affected by the light level in the current room.\n\n";

}
