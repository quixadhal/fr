inherit "/global/remote_cre";
#include "standard.h"
#include <network.h>

#define GUILD this_player()->query_guild_ob()
#define GROUP this_player()->query_group_ob()
#define RACEG this_player()->query_race_group_ob()  

#define GOD children( "global/god" )
#define LORD children( "global/lord" ) + GOD
#define THANE children( "global/thane" ) + LORD
#define PATRON children( "global/patron" ) + THANE
#define CRE children( "global/creator" ) + PATRON

void create() {
    call_out("do_sockets",1);
}

static nomask varargs mixed *filter_check( string verb, string str,
  object *checks, string rname,
  string mudname )
{
    int i;
    object *tmp;

    if( !sizeof(checks) ) checks = users();
    tmp = checks;
    switch( str[0] )
    {
    case '!' :
	str = str[1..strlen(str)-1];
	if(!rname) {
	    message(str,"You force-"+verb+"-tell: ", TP);
	    verb = CNAME+" [Forced-"+CAP(verb)+"]: ";
	}
	else if(!mudname)
	    verb = capitalize(rname)+" (Forced-"+CAP(verb)+"): ";
	else
	    verb = capitalize(rname)+"@"+mudname+" ("+CAP(verb)+"): ";

	return ({ tmp, verb, str });
    case '@' :
	for( i = 0; i<sizeof(checks); i++ )
	{
	    if( !checks[i]->query_property("chan_"+verb) )
		tmp -= ({ checks[i] });
	}
	if(!rname) {
	    str = CNAME+" "+str[1..strlen(str)-1];
	    verb = "["+CAP(verb)+"] ";
	    message( str, verb, TP );
	}
	else if(!mudname) {
	    str = capitalize(rname)+" "+str[1..strlen(str)-1];
	    verb = "("+CAP(verb)+") ";
	}
	else {
	    str = capitalize(rname)+"@"+mudname+" "+str[1..strlen(str)-1];
	    verb = "("+CAP(verb)+") ";
	}

	return ({ tmp, verb, str });
    default  :
	for( i = 0; i<sizeof(checks); i++ )
	{
	    if( !checks[i]->query_property( "chan_"+verb ) )
		tmp -= ({ checks[i] });
	}
	if(!rname) {
	    message(str, "You "+verb+"-tell: ", TP );
	    verb = CNAME+" ["+CAP(verb)+"]: ";
	}
	else if(!mudname) {
	    verb = capitalize(rname)+" ("+CAP(verb)+"): ";
	}
	else {
	    verb = capitalize(rname)+"@"+mudname+" ("+CAP(verb)+"): ";
	}
	return ({ tmp, verb, str });
    }
}

int do_chat( string str ) {
    string verb;
    mixed *Gval;

    verb = query_verb();
    if(!str || str =="")
    {
	message("You must have a message too.\n","",TP);
	return 1;
    }
    if(str[0]=='!' && (verb=="group"||verb=="guild"||verb=="race"))
	str = " "+str;
    if(verb == "guild")
    {
	if(!GUILD)
	{
	    message("You are not a member of any guild.\n","",TP);
	    return 1;
	}
	if(!GUILD->query_channel())
	{
	    message("Your guild does not have that ability.\n","",TP);
	    return 1;
	}
	verb = (string)GUILD->query_name();
    }
    if(verb == "group")
    {
	if(!GROUP)
	{
	    message("You are not a member of any group.\n","",TP);
	    return 1;
	}
	if(!GROUP->query_channel())
	{
	    message("Your group does not have that ability.\n","",TP);
	    return 1;
	}
	verb = (string)GROUP->query_name();
    }
    if(verb == "race")
    {
	if(!RACEG)
	{
	    message("You are not a member of any race group.\n","",TP);
	    return 1;
	}
	if(!RACEG->query_channel())
	{
	    message("Your race group does not have that ability.\n","",TP);
	    return 1;
	}
	verb = (string)RACEG->query_name();
    }

    if(this_player()->query_property("chan_"+verb) == "nope")
    {
	message("Your channel has been removed.\n","",TP);
	return 1;
    }
    if(str == "off" || str == "on")
    {
	switch( str )
	{
	case "off" :
	    message("Ok, you turn off the "+verb+"-channel.\n","",TP);
	    TP->remove_property("chan_"+verb);
	    return 1;
	    break;
	case "on" :
	    message("Ok, you turn on the "+verb+"-channel.\n","",TP);
	    TP->add_property( "chan_"+verb, 1 );
	    return 1;
	    break;
	default : message("Something bad just happened, " +
	      "contact an immortal.\n","",TP  );
	}
    }

    if(!TP->query_property("chan_"+verb))
    {
	message("You don't have that channel on.\n","",TP);
	return 1;
    }
    switch(verb)
    {
    case "demi"  :
	Gval = filter_check( verb, str, LORD );
	break;
    case "dwadmin" :
	Gval = filter_check( verb, str, LORD );
	break;
    case "patron":
	Gval = filter_check( verb, str, PATRON );
	break;
    case "thane" :
	Gval = filter_check( verb, str, THANE );
	break; 
    case "cre" :
	Gval = filter_check( verb, str, CRE );
	break;
    case "dwcre" :
	Gval = filter_check( verb, str, CRE );
	break;
    case "intercre" :
	Gval = filter_check( verb, str, CRE );
	break;
    case "sport" :
	Gval = filter_check( verb, str, CRE );
	break;
    case "emergency" :
	Gval = filter_check( verb, str, CRE );
	break;
    default      :
	Gval = filter_check( verb, str );
    }
   if(sizeof(Gval[0]))
       message( Gval[2], Gval[1], Gval[0], TP );

    if( verb == "cre" || verb == "thane" || verb == "demi" )
    {
	add_send_mess(verb+" "+this_player()->query_name()+" "+
	  implode(explode(mud_name()," "),"_")+
	  " "+str);
	transmit();
    }
    if( (verb == "dwcre") || (verb == "dwadmin") || (verb == "intercre" ) )
    {
	SERVICES_D->eventSendChannel(this_player()->query_short(), verb,
	  Gval[2], 0, 0, 0);
    }
    return 1;
}

varargs void received_cre(string s) {
    object who_targ;
    mixed *Gval;
    string verb, str, name, mud, *cren, who_data, garb;
    int i, j;

    if(s)  received += ({ s });

    if (sizeof(received))
	for(i=0;i<sizeof(received);i++) {
	    sscanf(received[i],"%s %s %s %s", verb, name, mud, str);
	    if(verb == "cre")
		Gval = filter_check(verb,str,CRE,name);
	    if(verb == "sport")
		Gval = filter_check(verb,str,CRE,name);
	    if(verb == "thane")
		Gval = filter_check(verb,str,THANE,name);
	    if(verb == "demi")
		Gval = filter_check(verb,str,LORD,name);
	    if(verb == "dwcre")
		Gval = filter_check(verb,str,CRE,name,mud);
	    if(verb == "dwadmin")
		Gval = filter_check(verb,str,LORD,name,mud);
	    if(verb == "intercre")
		Gval = filter_check(verb,str,CRE,name,mud);

	    if(sizeof(Gval) > 2)
		message(Gval[2],Gval[1],Gval[0]);
	    /* uncomment next line if you want the mudname to come back. */
	    //    message(Gval[2],"["+mud+"]"+Gval[1],Gval[0]);

	}
    received = ({ });
} /* received_cre() */
