/*
 * Process_input
 * grabbed from RoD and lobotomized by Baldrick dec '97
 * included at the bottom of player.c
 */
// Skullslayer - define MAX_STRLEN to stop the driver barfing as it tries
//               to interpret the command

#define MAX_STRLEN 900

#define EXPANSION ([     \
     "u" : "up",         \
     "d" : "down",       \
     "n" : "north",      \
     "s" : "south",      \
     "e" : "east",       \
     "w" : "west",       \
     "ne" : "northeast", \
     "nw" : "northwest", \
     "se" : "southeast", \
     "sw" : "southwest", \
  ])

nomask static mixed process_input( string ss )
{
    string verb, t, tmp ;

    reset_eval_cost() ;
    if ( !strlen(ss) ) return "";
    // Taniwha crash workround
    if( !strsrch(ss,"%^") ) return "";
    while( ss[<1] == ' ' ) ss = ss[0..<2];
    if ( !strlen(ss) ) return "";
    if( strlen(ss) > MAX_STRLEN ) {
	ss = ss[ 0..MAX_STRLEN ];
	tell_object(this_object(),"Command too long - processing anyway.\n");
    }
    switch( ss[0] )
    {
	case '\'' : ss = "say "+   ss[1..<1]; break;
	case ':'  : ss = "emote "+ ss[1..<1]; break;
	case '\"' : ss = "lsay "+  ss[1..<1]; break;
	case ';'  : ss = "parse "+ ss[1..<1]; break;
    }

    if( (tmp = EXPANSION[ss]) ) ss = tmp ;

    /* Ok, my stuff: (Baldrick)
     */
    /* First the aliases. */
    sscanf(ss, "%s %s", verb, t);
    if(!verb)
	verb = ss;
    if ( exec_alias(verb, t) ) { return 1; }

    //if( action_check( ss ) ) { return 1; }
    action_check( ss );

    //if( lower_check( ss ) ) { return 1; }
    lower_check( ss );

    return 1;

}
