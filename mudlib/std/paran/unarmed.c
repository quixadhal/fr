inherit "std/weapon";

muscle_damage(attacker,attack_by) {
  int dam;

  if (check_fail())
    failure(attacker);
  dam = attacker->hit_player(random(((weapon_class*2)+
         query_skill_bonus("unarmed combat"))/3),4);
  write_string(dam,attacker,attack_by);
  return dam;
}

write_string(dam, him, me) {
  if (dam<3) {
    me->event_say(this_object(),"You missed "+him->query_name()+".\n");
    him->event_say(this_object(),me->query_cap_name()+" missed you.\n");
    event(environment(me),me->query_cap_name()+" missed "+
          him->query_name()+".\n");
    return ;
  }
  if (dam<10) {
    me->event_say(this_object(),"You just hit "+him->query_name()+".\n");
    him->event_say(this_object(),me->query_cap_name()+" just hits you.\n");
    event(environment(me),me->query_cap_name()+" just hits "+
          him->query_name()+".\n");
    return ;
  }
  if (dam<20) {
    me->event_say(this_object(),"You swipe "+him->query_name()+".\n");
    him->event_say(this_object(),me->query_cap_name()+" swipes you.\n");
    event(environment(me),me->query_cap_name()+" swipes  "+
          him->query_name()+".\n");
    return ;
  }
  if (dam<100) {
    me->event_say(this_object(),"You hit "+him->query_name()+".\n");
    him->event_say(this_object(),me->query_cap_name()+" hits you.\n");
    event(environment(me),me->query_cap_name()+" hits "+
          him->query_name()+".\n");
    return ;
  }
  me->event_say(this_object(),"You smash "+him->query_name()+".\n");
  him->event_say(this_object(),me->query_cap_name()+" smashes you.\n");
  event(environment(me),me->query_cap_name()+" smashes "+
          him->query_name()+".\n");
}
