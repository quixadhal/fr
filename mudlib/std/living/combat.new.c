/* Ok, this time it's this code I will walk through...
 * Baldrick, april '94
 * Removed the deathstuff and pu tit in death.c.
 * looks a lot better that way.
 */

inherit "/std/unarmed_combat";
inherit "/std/living/protect.c";

/* Hmm, are we using these now ? */
int *weapon_attack_out, *attack_out;                //dk

static object attackee;
static object *attacker_list,
              *call_outed;

static int concentrate;
static int dodging;


#define DIV_NUM 6
#include "money.h"

void set_weapon_attack_out(int mess, object *held_ob) { }

int query_dodging() { return dodging; }
int query_my_att_level() { return (int)this_object()->query_level(); }
void set_concentrate(int i) { concentrate = i; }
int query_concentrate() { return concentrate; }
void actual_death();

void create() 
  {
  attacker_list = ({ });
  call_outed = ({ });
  unarmed_combat::create();
}

void combat_commands() 
  {
  ::combat_commands();
  unarmed_combat_commands();
}

object query_attackee() { return attackee; }

void attack() 
  {
  int i, dam, his_att_lvl, olav, att_level, t;
  string his_name;
  object *obs,ob,*ww;
  object *protectors;

  if (!attacker_list)
   attacker_list = ({ });

  while (i<sizeof(attacker_list)) {
    if (!attacker_list[i])       //dw have they died unexpecedaly? 
      attacker_list = delete(attacker_list,i,1);
    else
//dw    I will put all the ones not in the correct environ in a new list.

      if (environment(attacker_list[i]) != environment()) 
        {
        write("You are hunting "+attacker_list[i]->short()+"\n");
/* this call out would be nice to get rid of...
 * Baldrick
 */
        call_out("check_stop_fight",600,attacker_list[i]);
        if (!call_outed)
          call_outed = ({ attacker_list[i] });
        else
          call_outed += ({ attacker_list[i] });
        attacker_list = delete(attacker_list,i,1);
        } 
       else
        i++;
  }

//dw check the not correct environ list to see if any one has come back.  
  i = 0;
  while (i<sizeof(call_outed))
    if (!call_outed[i])
      call_outed = delete(call_outed,i,1);
    else if (environment() == environment(call_outed[i])) {
      attacker_list += ({ call_outed[i] });
      call_outed = delete(call_outed,i,1);
    } else
      i++;
//dw not hitting anyone... do spell effects anyway... 
  if (!sizeof(attacker_list)) {
// this_object()->do_spell_effects(0);  (dk: ducky moved this to hb)
    attackee = 0;
    return;
  }
//dw choose a random person from the attacker list; they're in correct env.
  if (concentrate)
    attackee = attacker_list[0];
  else
    attackee = attacker_list[random(sizeof(attacker_list))];


/* The protect thingie.
 * Looks like a mess, remessing it now.
 * Baldrick, oct '94
 */
  if (protectors=query_protectors()
    {
    for (t=0;t<sizeof(protectors);t++)
      { 

      if (protectors[t] && member_array(protectors[t], attacker_list) != -1) 
        {
        tell_object(this_object(), protectors[t]->query_cap_name()+
                " turns against you and starts fighting you.\n");
        tell_object(protectors[t], "You start fighting "+
                this_object()->query_cap_name()+" and stop protecting "+
                this_object()->query_objective()+".\n");
        say(protectors[t]->query_cap_name()+" turns against "+
          this_object()->query_cap_name()+" and starts attacking him.\n",
          ({ protectors[t], this_object() }));
        }
      if ((ob = (object)attackee->query_protector()) && 
        environment(ob) == environment(attackee) && random(100) >= 20) 
        {
        tell_object(attackee, ob->query_cap_name()+
            " valiantly protects you.\n");
        tell_object(ob,"You valiantly protect " +
            attackee->query_cap_name()+".\n");
        say(ob->query_cap_name()+" valiantly protects "+
          attackee->query_cap_name()+".\n", ({ attackee, ob }));
        attackee = ob;
        } /* if (ob.. */
      } /* for */
    } /* if protectors */
  his_att_lvl = maxi(({ (int)attackee->query_level(), 1 }) );
  his_name = (string)attackee->query_name();
  attackee->attack_by(this_object());

//dw   Ok, do the damage to the person we are attacking.  This has already
//dw   been wombled to get the attackee to be the right person (ie being
//dw   protected).

  // Attack code below by Aragorn.

  ww = (object *)this_object()->query_weapons_wielded();
  if (!sizeof(ww))
     // dam = weapon_attack(attackee,this_object()); // Bare hands?
     dam = unarmed_attack(attackee,this_object()); // Bare hands?
  else
     for(olav=0;olav<sizeof(ww);olav++)
        dam += (int)ww[olav]->weapon_attack(attackee,this_object());

  /*
  tell_object(this_object(),sprintf("DEBUG : Wielding : %O\nFighting : %O.\n",ww,attackee));
  */

  // Here endeth the code by Aragorn
 
  if (!attackee) 
    {
    tell_object(this_object(),"You killed "+his_name+"\n");
    say(this_object()->query_cap_name()+" killed "+his_name+"\n");
    }

  // Fix by Aragorn
  att_level = (int)this_object()->query_level();
  att_level = att_level?att_level:1;
  this_object()->adjust_xp(dam*his_att_lvl/att_level);
  event(environment(), "fight_in_progress", attackee);

  /*
  tell_object(this_object(),sprintf("DEBUG : Did %d damage. his_att_lvl=%d, att_level=%d.\n",dam,his_att_lvl,att_level));
  */

}

void attack_by(object ob) 
  {
  if (ob == this_object())
    return ;
  if (!attacker_list)
    attacker_list = ({ });
  if (!sizeof(attacker_list)) 
    {
    dodging = (int)this_object()->query_level();
    }
  if (member_array(ob, attacker_list) == -1 &&
      member_array(ob, call_outed) == -1) 
    {
    tell_object(this_object(), "You are attacked by " + 
        ob->query_short() + ".\n");

    attacker_list += ({ ob });
    }
  set_heart_beat(1);
}

/* Hmm, this is called by the attacker, object ob is the victim */
void attack_ob(object ob) 
  {
  if (ob == this_object())
    return;
  if (!attacker_list)
    attacker_list = ({ });
  if (!sizeof(attacker_list)) 
    {
    /* This will be changed later.. */
    dodging = (int)this_object()->query_level();
    }
  if (member_array(ob, attacker_list) == -1 &&
      member_array(ob, call_outed) == -1) 
    {
    attacker_list += ({ ob });
    }
  if (ob)
    ob->attack_by(this_object());
    //tell_object(ob, "You are attacked! (debug).\n");
}

void check_stop_fight(object ob) 
  {
  int i;
  if ((i=member_array(ob,call_outed)) != -1)
    call_outed = delete(call_outed,i,1);
}

int stop_fight(object ob) 
  {
  int i;
  if ((i=member_array(ob,call_outed)) != -1) {
    tell_object(this_object(),"You stop hunting "+call_outed[i]->short(0)+
      ".\n");
    call_outed = delete(call_outed, i, 1);
  }
  if ((i=member_array(ob,attacker_list)) != -1)
    attacker_list = delete(attacker_list,i,1);
}

mixed *query_attacker_list() { return attacker_list; }
mixed *query_call_outed() { return call_outed; }

mixed stats() 
  {
  int i; object ob; mixed *ret;
  if (ob=this_object()->query_held_ob(0) && ob->query_weapon())
    ret += ({ ({ "Weapon", ob->short() }) }) + (mixed)ob->weapon_stats();
  if (ob=this_object()->query_held_ob(1) && ob->query_weapon())
    ret += ({ ({ "Secondary weapon", ob->short() }) });
  for (i=0; i<sizeof(attack_out); i+=7) 
    ret += ({ ({ "If",    attack_out[i], }), 
              ({ "Rate",  attack_out[i+1], }), 
              ({ "Attack", attack_out[i+2], }), 
              ({ "Tohit", attack_out[i+3], }), 
              ({ "Number of damage dice", attack_out[i+4], }), 
              ({ "Die size", attack_out[i+5], }), 
              ({ "Addend", attack_out[i+6], }), 
          }); 
  return ret;
}
