// Track skill for Rangers : Radix - July 18, 1995

#define TRACKED_SHADOW "/std/commands/shadows/tracked.c"
#define TRACKER_SHADOW "/std/commands/shadows/tracker.c"
#define TRACK_COST 5

void clean_tracking();
void load_shadows(object me, object vic);

int track(string who, object me)
{
   object *tmp, vic;
   if(!who)
   {
      notify_fail("Syntax: track <something>\n");
      return(0);
   }
   if(!me) me = this_player();
   if(me->query_alignment()>1000)
   {
      notify_fail("Mielikki grants no powers to those whom are evil.\n");
      return 0;
   }
   who = me->expand_nickname(who);
   tmp = find_match(who,environment(me));
   if(!sizeof(tmp)||tmp[0]->query_hidden_shadow()||tmp[0]->query_hidden())
   {
      notify_fail("Track someone that exists!\n");
      return(0);
   }
   vic = tmp[0];
   
   if(vic->query_dead())
   {
      notify_fail("Wisps of mist don't leave tracks!\n");
      return(0);
   }
   if(me->query_gp() < TRACK_COST)
   {
      notify_fail("You are too drained mentally to track someone.\n");
      return(0);
   }
   if(me->query_tracking()) me->clean_tracking();

   tell_object(me,"Ok, tracking "+capitalize(who)+".\n");
   load_shadows(me, vic);
   me->adjust_gp(-TRACK_COST);
   return(1);
}

load_shadows(object me, object vic)
{
   int time = ((int)me->query_level() / 5) * (int)me->query_wis();
   object tracker = clone_object(TRACKER_SHADOW);
   object tracked = clone_object(TRACKED_SHADOW);
   tracker->move(me);
   tracked->move(vic);
   tracker->start(me);
   tracked->start(vic);

   tracked->set_tracker(me);
   tracked->set_time_factor(time);
   vic->add_timed_property("being_tracked",1,time*3/2);
   me->set_victim(vic);
}
string help(string str)
{
   return
      "Track:\n\n"
      "GP Cost: NA\n"
      "When a ranger is tracking a person, he studies the environment "
      "and finds various footprints and other signs to determine the "
      "path of a target that has long sense departed.  In order to track "
      "a target, the ranger must find an origin, thus the target must "
      "first be present.  This is most useful when a target flees.  "
      "\n\nSyntax: track <target>\n\n";
}
