/*

     Mordred @ Realms of the Dragon (Jason A. Macialek)
     --------------------------------------------------
     Mudlib error handler for the Realms of the Dragon mudlib.

     Coded from scratch, using an event inform idea that came
     from the Suvangi mudlib. (No code was used, mind you, if
     something goes wrong with it, you have only me to blame)
   Hellbent modified this file so that if the last verb is
   "update", nothing is added to the error file. 971011
 * 980601 Hellbent removed all traces of user_handler from here

#include <users.h>
 */
#define LOG_DIR "errors/"
#define DEFAULT_ERR_LOG_DIR "/log/errors/"

int view_errors( object user )
{
    return (int)user->query_creator() ;
}

private string build_log( mapping err, int caught, object tp,
  string vrb )
{
    mapping *errTrace ;
    string oTxt, nme ;
    int i ;

    if( tp )
    {
	nme = (string)tp->query_name() ;
    } else {
	nme = "no active player" ;
    }
    if( !vrb || vrb == "" )
    {
	vrb = "no verb" ;
    }
    oTxt = sprintf( "---==[ error occurred at %s ]==---\n", ctime( time() ) ) ;
    if( caught )
    {
	oTxt += "note    : error was caught via catch().\n" ;
    }
    oTxt += sprintf( "player  : %s [last verb: %s]\n", nme, vrb ) ;
    oTxt += sprintf( "object  : %O\n", (object)err["object"] ) ;
    oTxt += sprintf( "error   : %s", (string)err["error"] ) ;
    oTxt += sprintf( "program : %s\n", (string)err["program"] ) ;
    oTxt += sprintf( "file    : %s at line %d\n", (string)err["file"],
      (int)err["line"] ) ;
    errTrace = (mapping *)err["trace"] ;
    i = sizeof( errTrace ) ;
    if( !i )
    {
	return oTxt ;
    }
    while( i-- )
    {
	oTxt += "   ------------------------------------\n" ;
	oTxt += sprintf( "   object   : %O\n",
	  (object)errTrace[i]["object"] ) ;
	oTxt += sprintf( "   function : %s\n",
	  (string)errTrace[i]["function"] ) ;
	// Skullslayer put in this bit for arguments
	if (sizeof(errTrace[i]["arguments"])) {
	    oTxt += sprintf( "   arguments:");
	    foreach ( mixed arg in errTrace[i]["arguments"] ) {
		oTxt += sprintf( " %O,", arg ) ;
	    }
	    oTxt += "\n";
	}
	oTxt += sprintf( "   program  : %s\n",
	  (string)errTrace[i]["program"] ) ;
	oTxt += sprintf( "   file     : %s at line %d\n",
	  (string)errTrace[i]["file"],
	  (int)errTrace[i]["line"] ) ;
    }
    return (oTxt +"\n\n") ;
}

string error_handler( mapping err, int caught )
{
    string uName, cStr, fileExt, fileName, *pth, vrb, ofn ;
    object tp=0 ;

    // this works
    // if( (tp = this_player( 0 ) && tp) )
    tp = this_player( 0 ) ;
    if( tp )
    {
	vrb = (tp->query_verb() ? tp->query_verb() : "no verb") ;
	uName = " ("+ capitalize( (string)tp->query_name() ) +" ["+ vrb +
	"])" ;
    } else {
	uName = "" ;
    }
    //Hellbent was here 971011 - skully was too 980418
    if( vrb == "update" || vrb == "upd" || vrb == "load" )
	return "";
    //end of HB's mods.
    if( caught )
    {
	cStr = " [c]" ;
	fileExt = ".caught" ;
    } else {
	cStr = "" ;
	fileExt = "" ;
    }

    if( !(object)err["object"] )
    {
	log_roll_time( DEFAULT_ERR_LOG_DIR + "no_object.err", 
			build_log( err, caught, tp,
	    vrb ) ) ;
    }
    ofn = file_name( (object)err["object"] ) ;
    pth = explode( ofn, "/" ) ;
    switch( pth[0] )
    {
    case "d" :
	if( sizeof( pth ) < 3 )
	{
	    fileName = DEFAULT_ERR_LOG_DIR + "domain.err" ;
	} else {
	    fileName = "/d/"+ pth[1] +"/log/debug.err" ;
	}
	break ;
    case "w" :
	if( sizeof( pth ) < 3 )
	{
	    fileName = DEFAULT_ERR_LOG_DIR + "wizard.err" ;
	} else {
	    fileName = "/w/" + pth[1] +"/debug.err" ;
	}
	break ;
    default :
	fileName = DEFAULT_ERR_LOG_DIR + pth[0] + ".err" ;
	break ;
    }
    fileName += fileExt ;
    log_roll_time( fileName, build_log( err, caught, tp, vrb ) ) ;
    /* Uncomment this to remove the /log/debug.log support */
    // write_file( "/log/debug.log", sprintf( "%0", err ) ) ;
    if( vrb != "update" )
	event( efun::children( "/global/god.c" ) + 
	  efun::children( "/global/lord.c" ) +
	  efun::children( "/global/creator.c" ), "inform", ("%^RED%^Error"+
	    cStr +": "+ ofn + uName +"%^RESET%^"), "error" ) ;
}
