// Chatsystem Version 1.6
// By Begosh
// Added in some code to force load set_channel, Dyraen 17apr95

#include "standard.h"
#define IS_LORD "/secure/master"->query_lord( geteuid( TP ) )
#define RACE TP->query_race_ob()->query_name()
#define GUILD TP->query_guild_ob()
#define GOD children("global/god")
#define IS_GOD member_array( TP, GOD ) != -1
#define LORD children( "/global/lord" ) + GOD
#define DEMI filter_array( LORD , "d_check", TO )
#define IS_DEMI "/secure/master"->high_programmer( geteuid( TP ) )
#define CRE children( "global/creator" ) + LORD
#define L_CHAN (["god":1,"demi":2,"meet":3,"lord":3,"forger":3,"cre":4,"chat":5,"guild":5, "race":5 ])
#define SNAME TP->query_short()
static mapping new_channels = ([ ]);

void create() {
object ob;
string sc;

  seteuid("Root");
  sc = "/global/set_channel";
  if(!(ob = find_object(sc))) {
    catch(sc->FORCE_LOAD());
    ob = find_object(sc);
  }
} /* create() */

string *query_channels()
{
    return keys(L_CHAN+new_channels);
}

mapping channels()
{
    return L_CHAN + new_channels;
}

int add_channel( string str, int permission )
{
    if( sizeof( new_channels ) > 60 ) return 0;
    switch( permission )
    {
        case 1 : if( IS_GOD ) break; return 0;
        case 2 : if( IS_DEMI ) break; return 0;
        case 3 : if( IS_LORD ) break; return 0;
        case 4 : if( TP->query_creator() ) break; return 0;
    }

    if( L_CHAN[str] || new_channels[str] ) return 0;
    new_channels += ([ str:permission ]);
    return 1;
}

int remove_channel( string str ) 
{
    if( new_channels[str] )
    {
    int i;
        i = new_channels[str];
        switch( i )
        {
            case 1 : if( IS_GOD ) break; return 0;
            case 2 : if( IS_DEMI ) break; return 0;
            case 3 : if( IS_LORD ) break; return 0;
            case 4 : if( TP->query_creator() ) break; return 0;
        }
        map_delete( new_channels, str);
        return 1;
    }
    else return 0;
}

int d_check(object ob) 
{    
    return "/secure/master"->high_programmer( geteuid( ob ) );
}

static nomask varargs mixed *filter_check( string verb, string str,
                                           object *checks )
{
    int i, ival;
    object *tmp = ({ });
    if( !sizeof(checks) ) checks = users();
    switch( str[0] )
    {
        case '!' :
            str = str[1..strlen(str)-1];
            message(str,"You force-"+verb+"-tell: ", TP);
            verb = "[Forced-"+CAP(verb)+"] "+SNAME+":";
            return ({ checks, verb, str });

        case '@' :
            for( i = 0; i<sizeof(checks); i++ )
            {
               if( catch( checks[i]->query_channels()[verb] ) ) continue;
               if(!checks[i]->query_channels()[verb]) continue;
               else if(checks[i]->query_channels()[verb] == "on")
                   tmp += ({ checks[i] });
            }
            str = SNAME+" "+str[1..strlen(str)-1];
            verb = "["+CAP(verb)+"] ";
            message( str, verb, TP );
            return ({ tmp, verb, str });

        case '?' :
            for( i = 0; i<sizeof(checks); i++ )
            {
               if( catch( checks[i]->query_channels()[verb] ) ) continue;
               if( checks[i]->query_channels()[verb] )
                {
                    if(  ( ival = (checks[i]->query_invis()) ) != 0  )
                    {
                        if(ival<2 && TP->query_creator())
                            tmp += ({ checks[i] });
                        if(ival>1 && TP->query_lord())
                            tmp += ({ checks[i] });
                    } 
                    else tmp += ({checks[i]});
                }
            }
            return ({ tmp, verb, str });

        default  :
            for( i = 0; i<sizeof(checks); i++ )
            {
               if( catch( checks[i]->query_channels()[verb] ) ) continue;
               if( !checks[i]->query_channels()[verb] ) continue;
               else if( checks[i]->query_channels()[verb] == "on" )
                   tmp += ({ checks[i] });
            }

            message(str, "You "+verb+"-tell: ", TP );
            verb = "["+CAP(verb)+"] ";
            return ({ tmp, verb,  SNAME + " : "+ str });
    }
}

int do_chat( string str )
{
    string verb;
    mixed *Gval;
    int i;
    mapping channels;

    verb = query_verb();

    if( !L_CHAN[verb] && !new_channels[verb] ) return 0;
    i = channels()[verb];
    switch( i )
    {
       case 1 : if( IS_GOD ) break; return 0;
       case 2 : if( d_check( TP ) ) break; return 0;
       case 3 : if( IS_LORD ) break; return 0;
       case 4 : if( !TP->query_creator() ) return 0;
    }
    
    if( verb == str )
    {
         message("%^RED%^Syntax: "+verb+" [ @ <string>| !<string> | ? | "+
             "<string>]\n", "", TP );
         return 1;    
    }

    str = str[ ( strlen( verb ) + 1 ) ..strlen( str ) - 1 ];

    if( str[0] == '!' && i > 4 ) str = " " + str;

    if( verb == "guild" )
    {   
        if( !GUILD )
        {     
             message("You are not a member of any guild.\n","",TP);
             return 1;
        }
        verb = GUILD->query_name();
    }

    if( verb == "race" ) verb = RACE;
    
    channels = TP->query_channels();
    if( verb == "chat" && !channels[verb] ) return 0;
    if( channels[verb] == "nope" ) return 0;
    
    if( channels[verb] )
    {
      // Altered the line below to allow people to turn channels
      // back on.  Dyraen.
         if( channels[verb] == "off" && str != "on")
         {
             message("You do not have "+verb+" channel on\n","", TP );
             return 1;
         }
    }
    if( str == "on" || str == "off" )
    {
       if( new_channels[verb] )  TP->add_t_channel( verb, str );
          else TP->add_channel( verb, str );
       message("You turn "+str+" the "+ verb + " channel.\n","", TP );
       return 1;
    }

    if( !channels[verb] ) 
    {
        message("You do not have that channel turned on.\n","", TP);
        return 1;
    }

    switch( i )
    {
        case 1:
            Gval = filter_check( verb, str, GOD );
            break;
        case 2:
            Gval = filter_check( verb, str, DEMI );
	    break;
        case 3:
            Gval = filter_check( verb, str, LORD );
            break;
        case 4:
            Gval = filter_check( verb, str, CRE );
        break; //BREAK GODDAMIT!!! ARGH!!!
        default :
            Gval = filter_check( verb, str );
    } 
    if( Gval[2][0] != '?' ) 
    {
        if( verb == "meet" ) log_file( "meeting", Gval[1]+Gval[2]+"\n");
        message( Gval[2], Gval[1], Gval[0], TP );
    }
    else if ( Gval[2][0] == '?' )
    {
    string n_list="";
        for(i=0;i<sizeof(Gval[0]);i++)
        {
	    if( Gval[0][i]->query_invis() == 2 )
            {
                n_list += sprintf("%12-s %20-s %-s\n", "[Superinvis]", 
                    Gval[0][i]->query_short(), 
                    ( Gval[0][i]->query_channels()[verb] !="off" ?
                      "[Listening]" : "[Not listening]" ) );
            }

            else if( Gval[0][i]->query_invis() != 0 )
            {
                n_list += sprintf("%12-s %20-s %-s\n", "[Invis]", 
                    Gval[0][i]->query_short(), 
                    ( Gval[0][i]->query_channels()[verb]!="off" ?
                      "[Listening]":"[Not listening]" ) );
            } else
            {
                n_list += sprintf( "%12-s %20-s %-s\n", "[Online]", 
                    Gval[0][i]->query_short(), 
                    ( Gval[0][i]->query_channels()[verb]!="off" ?
                      "[Listening]":"[Not listening]" ) );
            }

        }
        message( sprintf( "%-s\n",n_list ), "", TP );	
    }
    return 1;
}
