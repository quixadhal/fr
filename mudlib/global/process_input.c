/*
 * Process_input
 * grabben from RoD and lobotomized by Baldrick dec '97
 */
// Skullslayer - define MAX_STRLEN to stop the driver barfing as it tries
//               to interpret the command
// Skullslayer - took out random error messages, "What?" will do :)
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

nomask protected mixed process_input( string ss )
{   
    string verb, t, tmp, ret ;
    int i;

    reset_eval_cost() ;


    if ( (i = query_ed_mode()) != -1 )
      {
      if( ss && ss[0] == '!' )
        {
        ss = ss[1..];
        }
       else
        {
          //message( M_EDITOR, ret, this_object() );
	if (!ss) ss = "\n";
        if ( strlen( ret = ed_cmd( ss ) ) )
          write( ret, this_object() );
        // We might have finished
        if ( query_ed_mode() == -1 )
          {
          write("Editor ended\n");
          EdExitType = ss;
          if ( EndEditor )
            {
            evaluate( EndEditor );
            EndEditor = 0;
            }
          }
        return 1; 
        }
      }

    if ( !strlen(ss) || ss == "\n" ) { 
	show_prompt();
	return "";
    }

    // Taniwha crash workround
    if( !strsrch(ss,"%^") ) return "";
    while( ss[<1] == ' ' ) ss = ss[0..<2];
    if ( !strlen(ss) ) { 
	show_prompt();
	return "";
    }
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

