/* Ok, this time it's this code I will walk through...
 * Baldrick, april '94
 * Death.c removed from cmbat.c to make it cleaner.
 */

#define DIV_NUM 6

// prototypes:
void actual_death();

int do_death(object killed_by) 
  {
  int i, dead_xp, aln, tot;
  mapping damage_done;
  int att_level;
  int attackers, attacker_xp;

  object *attacker_list, *call_outed;

  /* Added to maybe fix an annoying bug..
   * The dead on login bug..
   * Baldrick, April '95.
   */
  if (this_object()->query_property("loading"))
    return 0;
 
  attacker_list = this_object()->query_attacker_list();
  call_outed = this_object()->query_call_outed();

  att_level = (int)this_object()->query_level();
  damage_done = (mapping)this_object()->query_damage_done();
  if (!damage_done)
    damage_done = ([ ]);
  for (i=0;i<sizeof(attacker_list);i++) 
    {
    attacker_list[i]->stop_fight(this_object());
    tot += damage_done[attacker_list[i]];
    attackers++;
    }
  for (i=0;i<sizeof(call_outed);i++)
    call_outed[i]->stop_fight(this_object());

  /* ??? where is this from ???  
   * It is the victims XP, so it can be added to the killer..
   * Smart, and nice.. 
   */
  dead_xp = (int)this_object()->query_xp();

  if (!tot) tot = 1;
  /* This is a tad expansive, will make the alignment change wery often..
   * Will make a divider.
   * Should make it level dependant, so killing a rat with 100 in alignment
   * won't be more important than killing a 50 dragon.
   * Baldrick
   */
  aln = (int)this_object()->query_align();

  // somewhere there is a divider..:=)
  //aln = (int)this_object()->query_align() / 5;

  /* this gives the total for each attacker.. */
  if (dead_xp != 0)
    attacker_xp = dead_xp / 20;
  if (attackers)
    attacker_xp += (int)this_object()->query_kill_xp() / attackers;

  /* Deliver the XP.. */
  for (i=0;i<sizeof(attacker_list);i++) 
    {
    /* This is one of the worst I have seen, Baldrick. */
    /*
    attacker_list[i]->adjust_xp( ( (xp * damage_done[attacker_list[i]]/tot) 
        * att_level ) / ( DIV_NUM * (int)attacker_list[i]->query_level()+1));
     */

    /* The simple one..:=) baldy.. Prolly add the damage_done too */
    attacker_list[i]->adjust_xp(attacker_xp);

    if (aln != 0)
      attacker_list[i]->adjust_align(-aln);
    }
  if (killed_by)
    say(killed_by->query_cap_name()+" dealt the death blow to "+
        this_object()->query_cap_name()+".\n");
  else
    say(this_object()->query_cap_name()+" died horribly.\n");
  if (environment())
    event(environment(), "death", attacker_list, killed_by);
  this_object()->add_property("dead",1);
  this_object()->set_alive(0);
  actual_death();
  return 0;
}

object make_corpse() 
  {
  object corpse, money, *obs, ob;
   mixed *usedstuff;
  string my_mess, room_mess;
  int i;

  corpse = clone_object("/obj/corpse");
  corpse->set_owner(this_object()->short(0));
  corpse->set_race_name(this_object()->query_race());

//? corpse->add_alias((string)this_object()->query_name());
//? corpse->add_alias((string *)this_object()->query_aliases());
//? corpse->add_plural((string *)this_object()->query_plurals());

  corpse->start_decay();
  corpse->add_adjective(this_object()->query_adjectives());
  if (!this_object()->query_race_ob())
    if (file_size("/std/races/"+this_object()->query_race()+".c") >= 0)
      corpse->set_race_ob("/std/races/"+this_object()->query_race());
    else
      corpse->set_race_ob("/std/races/unknown");
  else
    corpse->set_race_ob(this_object()->query_race_ob());

//dk Until we make an informed decision here, I'm going to have corpses
//unhold, unwear and unwield everything.  Otherwise, since some items have a
//special effect on the room only if they're worn or held by a living
//creature, creators would have to code each such item carefully to
//distinguish the effects when worn or held by a corpse...we probly don't
//want to do this, but even if we do, I don't want to deal with it right now.

  /* Un equip the player ? or corpse ? */
   usedstuff = (mixed *)this_object()->query_held_ob();

   if (sizeof(usedstuff)) {
      my_mess = "You have been slain";
      room_mess = (string)this_object()->query_cap_name() +
                  " dies";
   } 

  for (i=0;i<sizeof(usedstuff);i++)
    {
    /* Have to use this instead. */
    if (objectp(usedstuff[i]))
      {
      object ok;
      ok = usedstuff[i];
       this_object()->unhold_ob(ok);
      ok->move(environment(this_object()));
      } /* if (usedstuff.. */
    } /* for.. */

  /* Reset the array (to be sure ) */
  usedstuff = ({ });

  usedstuff = (mixed *)this_object()->query_worn_ob();

  if (sizeof(usedstuff))
     if (stringp(my_mess)) {
        my_mess += ", and your armour eerily hops"+
    " off your body and falls to the floor";
        room_mess += ", and " + this_object()->query_possessive() + 
            " armour eerily hops off "+this_object()->query_possessive() +
            " body and falls to the floor";
     } else {
        my_mess += "Your armour eerily hops"+
                   " off your body and falls to the floor";
        room_mess += this_object()->query_cap_name() + 
            "s armour eerily hops off "+this_object()->query_possessive() +
            " body and falls to the floor";
     }

    for (i=0;i<sizeof(usedstuff);i++)
      {
      if (objectp(usedstuff[i]))
        {
        this_object()->unwear_ob(usedstuff[i]);
        /*Shall they loose it or keep it in the corpse I */

        // usedstuff[i]->move(environment());
        } /* if (usedstuff.. */
      } /* for.. */

  /* Let the corpse loose everything */
  /* But they won't loose it, can put it back later tho.. */
  /*
  obs = all_inventory(this_object());
  for (i=0; i<sizeof(obs); i++)
    obs[i]->move(environment());
  */

  if (stringp(room_mess)) {
     tell_room(environment(this_object()),room_mess+".\n", this_object());
     tell_object(this_object(), my_mess+".\n");
  }
     
  // AS for now, the corpse contains the remaining stuff.
  all_inventory(this_object())->move(corpse);
  corpse->move(environment());
  return corpse;
} /* Make corpse */

//? shouldnt need to call this... so make it static, just in case 

static void actual_death() 
  {
  object ob, ob2;

//dw if second_life returns false... do stupid things... 

  if (!((int)this_object()->second_life())) {
    make_corpse()->move(environment());

//dw dest the ones that stick around... 
  // This is slightly useless now, the stuff is in the corpse
  // Good for the stuff that for some reason couldn't be moved tho
    ob = first_inventory(this_object());
    while(ob) {
      ob2 = next_inventory(ob);
      ob->dest_me();
      ob = ob2;
    }
    this_object()->dest_me();
  }
} /* void actual death */
