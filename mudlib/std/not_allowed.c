/*   Orignally developed by Grimbrand on Feb. 10 1995.           */

void init() {
   add_action("not_allowed", "cast");
   add_action("not_allowed", "c*ast");
   add_action("not_allowed", "kill");
   add_action("not_allowed", "k*ill");
   add_action("not_allowed", "heal");
   add_action("not_allowed", "recall");
   add_action("not_allowed", "point");
   add_action("not_allowed", "recite");
   add_action("not_allowed", "re*cite");
   add_action("not_allowed", "portal");
   add_action("not_allowed", "a*mbush");
   add_action("not_allowed", "b*ackstab");
   add_action("not_allowed", "b*ury");
   add_action("not_allowed", "c*onsider");
   add_action("not_allowed", "f*orget");
   add_action("not_allowed", "b*erserk");
   add_action("not_allowed", "h*ide");
   add_action("not_allowed", "j*udge");
   add_action("not_allowed", "p*alm");
   add_action("not_allowed", "p*ick");
   add_action("not_allowed", "r*emember");
   add_action("not_allowed", "s*lice");
   add_action("not_allowed", "s*lip");
   add_action("not_allowed", "s*neak");
   add_action("not_allowed", "s*teal");
   add_action("not_allowed","a*ttack");
   add_action("too_quiet", "sh*out");
   add_action("too_quiet", "chat");
   add_action("too_quiet", "guild");
   this_object()->add_property("noguild",1);
   this_object()->add_property("nocast",1);
}

not_allowed() {
   write("   Something about this place is preventing you from "+
         "taking any offensive actions, perhaps it is some sort "+
         "of magical side effect left over from long ago.\n"+
         "\n");
   say(this_player()->query_cap_name()+" attempts an aggressive act "+
       "yet somehow is unable to complete it with any success.\n\n",
       ({ this_player() }));
   return 1;
  }

too_quiet() {
   write("\n   You attempt to contact someone outside of this place "+
         "and find your vocalization swiftly absorbed by the mystical "+
         "power surrounding you here.\n"+
         "\n");
   say(this_player()->query_cap_name()+" tries to contact someone "+
       "not within the limits of this place and succeeds in merely "+
       "mouthing the words without any sound issuing forth.\n\n",
       ({ this_player() }));
   return 1;
}
