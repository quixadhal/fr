// Chatsystem Version 1.4
// By Begosh

#include "standard.h"
#define GUILD TP->query_guild_ob() 
#define LORD children( "global/lord" )
#define PATRON children( "global/patron" ) + LORD
#define THANE children( "global/thane" ) + PATRON
#define CRE children( "global/creator" ) + THANE

static nomask varargs mixed *filter_check( string verb, string str, 
					   object *checks )
{
    int i;
    object *tmp;

    if( !sizeof(checks) ) checks = users();
    tmp = checks;
    switch( str[0] )
    {
	case '!' : 
	    str = str[1..strlen(str)-1];
	    message(str,"You force-"+verb+"-tell: ", TP);
	    verb = CNAME+" [Forced-"+CAP(verb)+"]: ";
	    return ({ tmp, verb, str });
	case '@' :
	    for( i = 0; i<sizeof(checks); i++ )
	    {
		 if( !checks[i]->query_property("chan_"+verb) )
		    tmp -= ({ checks[i] });
	    }
	    str = CNAME+" "+str[1..strlen(str)-1];
	    verb = "["+CAP(verb)+"] ";
	    message( str, verb, TP );
	    return ({ tmp, verb, str });
	default  :
	    for( i = 0; i<sizeof(checks); i++ )
	    {
		if( !checks[i]->query_property( "chan_"+verb ) )
		    tmp -= ({ checks[i] });
	    }
	    message(str, "You "+verb+"-tell: ", TP );
	    verb = CNAME+" ["+CAP(verb)+"]: ";
	    return ({ tmp, verb, str });
    }
}

int do_chat( string str )
{
    string verb;
    mixed *Gval;

    verb = query_verb();
   if( !str || str =="" )
    {
	 message("You must have a message too.\n","",TP);
	 return 1;
    }
    if( str[0]=='!' && ( verb=="chat"||verb=="guild" ) )
        str = " "+str;
    if( TP->query_level() < 6 && verb == "chat" && !TP->query_creator() )
    {
	message("You don't have that ability yet...\n","",TP);
	return 1;
    }
    if( verb == "guild" ) 
    {
	if( !GUILD )
	{
	     message("You are not a member of any guild.\n","",TP);
	     return 1;
	}
	verb = (string)GUILD->query_name();
    }
    if( (string)TP->query_property( "chan_"+verb  ) == "nope" ) 
    {
	message("That ability has been removed.\n","",TP);
	return 1;
    }
    if( str == "off" || str == "on" )
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
			      "contact a creator.\n","",TP  );
      }
    } 

    if( !TP->query_property("chan_"+verb) )
    {
	message("You don't have that channel on.\n","",TP);
	return 1;
    }
    switch( verb )
    {
        case "demi"  :
            Gval = filter_check( verb, str, LORD );
	    break;                         

        case "patron":
            Gval = filter_check( verb, str, PATRON );
	    break;

        case "thane" :
            Gval = filter_check( verb, str, THANE );
            break; //BREAK GODDAMIT!!! ARGH!!!

        case "cre" :
            Gval = filter_check( verb, str, CRE );
        break;
/// Radix - only cre's need [000] and [emergency]
        case "000" :
        case "emergency" :
            Gval = filter_check( verb, str, CRE );
        break;
	default      :
	    Gval = filter_check( verb, str );
    }
    message( Gval[2], Gval[1], Gval[0], TP );
    return 1;
}
