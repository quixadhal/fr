/*    /daemon/services/channel.c
 *    from the Nightmare IV LPC Library
 *    handles intermud channels using the Intermud 3 protocols
 *    created by Descartes of Borg 950625
 *    Modified for Discworld by Turrican 1-11-95
 */

#define SERVICE_CHANNEL

string GetLocalChannel(string ch);
string GetRemoteChannel(string ch);

void eventReceiveChannelWhoReply(mixed *packet) {
    object ob;

    if( file_name(previous_object()) != INTERMUD_D ) return;
    if( !(ob = find_player(packet[5])) ) return;
    packet[6] = GetLocalChannel(packet[6]);
    if( !sizeof(packet[7]) ) {
	tell_object(ob, "No one is listening to " + packet[6] + " at " +
		packet[2] + ".\n");
	return;
    }
    tell_object(ob, "Listening to " + packet[6] + " at " + packet[2] + ": ");
    tell_object(ob, implode(packet[7], " ")+"\n");
}

int filter_listeners(object ob, string chan) {
  if (!ob->query_creator() || ob->check_earmuffs("intermud-all") ||
      ob->check_earmuffs(chan))
    return 0;
  return 1;
}

void eventReceiveChannelWhoRequest(mixed *packet) {
    string *who;

    if( file_name(previous_object()) != INTERMUD_D ) return;
    who = (string *)filter_array(users(), "filter_listeners", this_object(),
        packet[6])->query_cap_name();
    INTERMUD_D->eventWrite(({ "chan-who-reply", 5, mud_name(), 0, packet[2],
			      packet[3], packet[6], who }));
}

void eventReceiveChannelUserRequest(mixed *packet) {
    object ob;
    string visname;
    int gender;

    if( file_name(previous_object()) != INTERMUD_D ) return;
    if( !(ob = find_player(packet[6])) ) {
	INTERMUD_D->eventWrite( ({ "error", 5, mud_name(), 0, packet[2], 0,
				   "unk-user", packet[6] + " is not a valid "
				     "player.", packet }) );
	return;
    }
    visname = (string)ob->query_cap_name();
    switch( (string)ob->query_gender_string() ) {
	case "male": gender = 0; break;
        case "female": gender = 1; break;
        default: gender = 2; break;
    }
    INTERMUD_D->eventWrite( ({ "chan-user-reply", 5, mud_name(), 0, 
			       packet[2], 0, packet[6], visname, gender }));
}

void eventReceiveChannelMessage(mixed *packet) {
    if( file_name(previous_object()) != INTERMUD_D ) return;
    if( packet[2] == mud_name() ) return;
     "/global/do_chat"->received_cre(GetLocalChannel(packet[6])+" "+
        packet[7] + " " + replace_string(packet[2]," ","_") + " " + packet[8]);
}

void eventReceiveChannelEmote(mixed *packet) {
    string target;
    object *people;

  if( file_name(previous_object()) != INTERMUD_D ) return;
    if( packet[2] == mud_name() ) return;
    if( !packet[7] ) return;

     "/global/do_chat"->received_cre(GetLocalChannel(packet[6])+" "+
        packet[7] + " " + packet[2] + " " + replace_string(replace_string(packet[8],"$N ",""), " ", "_"));
}

varargs void eventSendChannel(string who, string ch, string msg, int emote,
			      string target, string targmsg) {
    mixed *packet;
    string targpl, where;

    if( emote ) {
	if( target && targmsg ) {
	    if( sscanf(target, "%s@%s", targpl, where) != 2 )
	      targpl = target;
	    where = mud_name();
	}
	else targpl = where = targmsg = 0;
	packet = ({ "channel-e", 5, mud_name(), lower_case(who), 0, 0, GetRemoteChannel(ch), 
                    who, msg });
    }
    else packet = ({ "channel-m", 5, mud_name(), lower_case(who), 0, 0, GetRemoteChannel(ch), 
		     who, msg });
    INTERMUD_D->eventWrite(packet);
}

void eventSendChannelWhoRequest(string channel, string mud) {
    string pl;

    pl = (string)this_player(1)->query_name();
    INTERMUD_D->eventWrite(({ "chan-who-req", 5, mud_name(), pl, mud, 0,
			      channel }));
}

string GetLocalChannel(string channel) {
  switch (channel) {
    case "imud_code":
      return "intercre";
    case "imud_gossip":
      return "intergossip";
    case "intermud":
      return "intermud";
    case "discworld-admin":
      return "dwadmin";
    case "discworld-cre":
      return "dwcre";
    case "discworld-chat":
      return "dwchat";
  }
  return 0;
}

string GetRemoteChannel(string channel) {
  switch (channel) {
  case "intercre" :  return "imud_code";
  case "dwadmin" :  return "discworld-admin";
  case "dwcre" :  return "discworld-cre";
  }
}

void eventRegisterChannels(mapping list) {
    mixed *val;
    string channel, ns;

    if( file_name(previous_object()) != INTERMUD_D ) return;
    ns = (string)INTERMUD_D->GetNameserver();
    foreach(channel, val in list) {
	if( !val ) continue;
        if (!GetLocalChannel(channel)) {
            INTERMUD_D->eventWrite(({ "channel-listen", 5, mud_name(), 0, ns,
                                      0, channel, 0 }));
//	    log_file("channels", "New channel: " + local + " recognized " +
//		     ctime(time()) + "\nValue: " + sprintf("%O", val) + "\n\n");
	}
	else INTERMUD_D->eventWrite(({ "channel-listen", 5, mud_name(), 0, ns,
                                       0, channel, 1 }));
    }
}

int eventAdministerChannel(string channel, string *additions, string *subs) {
    if( !((int)master()->high_programmer(geteuid(this_player(1)))) )
      return 0;
    if( member_array(channel, (string *)INTERMUD_D->GetChannels()) == -1 )
      return 0;
    INTERMUD_D->eventWrite(({ "channel-admin", 5, mud_name(),
			      (string)this_player(1)->query_cap_name(),
			      (string)INTERMUD_D->GetNameserver(),
			      0, channel, additions, subs }));
    return 1;
}

int AddChannel(string channel, int privee) {
    if( !((int)master()->high_programmer(geteuid(this_player(1)))) )
      return 0;
    if( member_array(channel, (string *)INTERMUD_D->GetChannels()) != -1 )
      return 0;
    INTERMUD_D->eventWrite(({ "channel-add", 5, mud_name(),
			      (string)this_player(1)->query_cap_name(),
			      (string)INTERMUD_D->GetNameserver(), 0,
			      channel, privee }));
    return 1;
}

int RemoveChannel(string channel) {
    if( !((int)master()->high_programmer(geteuid(this_player(1)))) )
      return 0;
    if( member_array(channel, (string *)INTERMUD_D->GetChannels()) == -1 )
      return 0;
    INTERMUD_D->eventWrite(({ "channel-remove", 5, mud_name(),
			      (string)this_player(1)->query_cap_name(),
			      (string)INTERMUD_D->GetNameserver(), 0,
			       channel }));
    return 1;
}
