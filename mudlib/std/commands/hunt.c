int hunt(string str, object me)
{
   int bonus, i, weap_type, damage;
   string weap_name;
   object target;
   object* weap;
   object* list;
   me=this_player();
   if(me->query_alignment()>1000)
   {
      notify_fail("Mielikki grants no powers to those who are evil.\n");
      return 0;
   }
   if(me->query_timed_property("hunt_lockout"))
   {
     notify_fail("You must take more time to study your opponent "
         "before such a calculated manuever can be successfully "
         "executed.\n");
      return 0;
   }
   if(me->query_gp()<5)
   {
      notify_fail("You are just a little too fatigued right now.  "
         "It might be better to rest a bit before hunting anyone.\n");
      return 0;
   }
   weap=me->query_weapons_wielded();
   if(!sizeof(weap))
   {
     notify_fail("If this target is so weak that you can use your "
         "bare hands to kill it, you probably don't need to use "
         "such force on it.  You better reconsider.\n");
      return 0;
   }
   list=find_match(str,environment(me));
   if(!sizeof(list))
   {
      notify_fail("You can only hunt someone who is present.\n");
      return 0;
   }
   target=list[0];
   if(target->query_dead())
   {
      notify_fail("So, you believe in ghosts?  Well, even if they exist, "
        "your talents could probably be better used hunting something "
         "else.\n");
      return 0;
   }
   if(target==me)
   {
     notify_fail("Whoa there! Are you mental ? Hunting yourself ?\n");
      return 0;
   }
   if(me->query_hide_shadow())
      bonus=(me->query_level())/(sizeof(weap));
   else
      bonus=((me->query_level())/(sizeof(weap))/2);
   if(target->query_alignment()>0)
      bonus*=2;
   for(i=0;i<sizeof(weap);i++)
   {
      weap_name=weap[i]->query_name();
      weap_type=weap[i]->query_attack_type();
      switch(weap_type)
      {
         case 1:
            write("You viciously slash "+target->query_cap_name()+
               " with your "+weap_name+".\n");
            tell_object(target,me->query_cap_name()+" viciously slashes "
               "you with a "+weap_name+".\n");
            tell_room(environment(me),
               me->query_cap_name()+" viciously slashes "+
               target->query_cap_name()+" with a "+weap_name+".\n",
               ({me,target}));
            break;
         case 2:
            write("You brutally pummel "+target->query_cap_name()+
               " with your "+weap_name+".\n");
            tell_object(target,me->query_cap_name()+" brutally pummels "
               "you with a  "+weap_name+".\n");
            tell_room(environment(me),
               me->query_cap_name()+" brutally pummels "+
               target->query_cap_name()+" with a "+weap_name+".\n",
               ({me,target}));
            break;
         case 3:
            write("You ruthlessly impale "+target->query_cap_name()+
               " with your "+weap_name+".\n");
            tell_object(target,me->query_cap_name()+" ruthlessly impale "
               "you with a "+weap_name+".\n");
            tell_room(environment(me),
               me->query_cap_name()+" ruthlessly impales "+
               target->query_cap_name()+" with a "+weap_name+".\n",
               ({me,target}));
            break;
         default:
            write("You beat "+target->query_cap_name()+" to a pulp.\n");
            tell_object(target,me->query_cap_name()+" beats you to a "
               "pulp with a "+weap_name+".\n");
            tell_room(environment(me),
               me->query_cap_name()+" beats "+target->query_cap_name()+
               " to a pulp with a "+weap_name+".\n",
               me,target);
            break;
      }
      me->adjust_tmp_tohit_bon(bonus*3);
      me->adjust_tmp_damage_bon(bonus);
      weap[i]->weapon_attack(target,me);
      me->adjust_tmp_damage_bon(-bonus);
      me->adjust_tmp_tohit_bon(-bonus*3);
   }
   target->attack_by(me);
   me->adjust_gp(-5);
   me->add_timed_property("hunt_lockout",1,7);
   return 1;
}
string help(string str)
{
   return
      "Hunt:\n\n"
      "GP Cost: 5\n"
      "When a Ranger is hunting a person, he/she studies his oponent "
      "in order to find a weakness in his/her defenses.  The ranger "
      "then attacks gaining a short advantage.  The ranger can get a "
      "better advantage if the target doesn't even know if the ranger is "
      "there, because the ranger is hidden.  "
      "Once a weakness is exploited, the target will usually take "
      "measures to protect that weakness.  It takes the ranger a "
      "certain amount of time to find another weakness to exploit.  "
      "\n\nSyntax: hunt <target>\n\n";
}
