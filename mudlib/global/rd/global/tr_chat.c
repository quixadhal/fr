// Chatsystem Version 1.4
// By Begosh
// Modified by Skaflock
// Further Modifed by Dyraen - Added Demi Channel
//        Dec '94            - Added Channel 'Who' 

/*  Essentially what I am trying to do with these modifications is set it
        so that newbies will not have a chan_chat property at all, and
        so will not be able to chat, while those that have completed
        the quest (or have chat because they were already here and had it),
        have a property chan_chat equal to "on" (have it on), "off" (have it
        turned off), or "nope" (they have had it taken away).
*/

#include "standard.h"
#define GUILD TP->query_guild_ob()
#define GOD children("global/god")
#define DEMI filter_array(children("global/lord"),"d_check",this_object())+GOD
#define LORD children( "global/lord" )+ GOD
#define CRE children( "global/creator" ) + LORD
#define L_CHAN ({"god", "demi", "lord", "cre", "guild", "chat" })

static string *new_channels=({});

string *query_channels()
{
    return L_CHAN+new_channels;
}

int add_channel( string str )
{

    if( member_array( str, L_CHAN ) != -1 )
    {
        message("%^RED%^That is not a channel that is standard channel, " +
            "you may not another one like that.\n", "", TP );
        return 1;
    }

    if( member_array( str, new_channels ) != -1 )
    {
        message("%^RED%^That channel already excists, therefor " +
            "you may not add that one.\n", "", TP );
        return 1;
    }

    new_channels += ({ str });
    message("%^BOLD%^"+capitalize( str )+" has been added.\n", "", TP );
    TP->add_property("chan_"+str, "on" );
 
   return 1;
}

int d_check(object ob) {    
  return "/secure/master"->high_programmer(geteuid(ob));
}

static nomask varargs mixed *filter_check( string verb, string str,
                                           object *checks )
{
    int i;
    object *tmp, *all;
//  Added 'all' so I could have one for case "!" another for the rest.
//  That way, in the other cases I'm doing one check, not three.

    if( !sizeof(checks) ) checks = users();
    all = checks;
         tmp = ({ });
    switch( str[0] )
    {
        case '!' :
            str = str[1..strlen(str)-1];
            message(str,"%^RED%^You force-"+verb+"-tell:%^RESET%^ ", TP);
            verb = CNAME+"%^RED%^ [Forced-"+CAP(verb)+"]:%^RESET%^ ";
            return ({ all, verb, str });
        case '@' :
            for( i = 0; i<sizeof(checks); i++ )
            {
               if(((string)checks[i]->query_property("chan_"+verb) == "on")
                || ((int)checks[i]->query_property("chan_"+verb) == 1) )
               tmp += ({ checks[i] });
            }
            str = CNAME+" "+str[1..strlen(str)-1];
            verb = "["+CAP(verb)+"] ";
            message( str, verb, TP );
            return ({ tmp, verb, str });
        default  :
            for( i = 0; i<sizeof(checks); i++ )
            {
               if(((string)checks[i]->query_property("chan_"+verb) == "on")
                || ((int)checks[i]->query_property("chan_"+verb) == 1) )
               tmp += ({ checks[i] });
            }
            message(str, "You "+verb+"-tell: ", TP );
            verb = CNAME+" ["+CAP(verb)+"]: ";
            return ({ tmp, verb, str });
    }
}

int do_chat( string str )
{
    object *online;
    string verb, whostr;
    mixed *Gval;
    int cols, i;

    verb = query_verb();

    if( ( member_array( verb, L_CHAN ) == -1 ) ||
        ( member_array( verb, new_channels ) == -1 ) ) return 0;
 
    if( !str || str =="" )
    {
    online = ({ });
         switch(verb) {
           case "god" :
             online = GOD;
             break;
           case "demi" :
             online = DEMI;
             break;
           case "lord" :
             online = LORD;
             break;
           case "cre" :
             online = CRE;
             break;
           case "guild" :
             if (!GUILD) {
               message("You are not a member of any guild.\n","",TP);
               return 1;
             }
             verb = (string)GUILD->query_name();
             for (i=0;i<sizeof(users());i++)
               if (users()[i]->query_property("chan_"+verb))
                 online += ({ users()[i] });
             break;
           default :
             for (i=0;i<sizeof(users());i++)
               if (users()[i]->query_property("chan_chat"))
                 online += ({ users()[i] });
         }
         cols = (int)TP->query_cols();
         whostr = "";
         
         if (!this_player()->query_creator())
           for (i=0;i<sizeof(online);i++) {
             if (online[i]->query_invis())
               continue;
             if (((string)online[i]->query_property("chan_"+verb) == "on") ||
                 ((int)online[i]->query_property("chan_"+verb) == 1 ))
               whostr += "*"+online[i]->query_cap_name()+"\n";
             else
               whostr += online[i]->query_cap_name()+"\n";
           }

         if ((this_player()->query_creator()) &&
             (!this_player()->query_lord()))
           for (i=0;i<sizeof(online);i++) {
             if ((string)online[i]->query_cap_name() == "Object")
               continue;
             if ((int)online[i]->query_invis() == 2)
               continue;
             if (((string)online[i]->query_property("chan_"+verb) == "on") ||
                 ((int)online[i]->query_property("chan_"+verb) == 1 ))
               whostr += "*"+online[i]->query_cap_name()+"\n";
             else
               whostr += online[i]->query_cap_name()+"\n";
           }

         if (this_player()->query_lord())
           for (i=0;i<sizeof(online);i++) {
             if ((string)online[i]->query_cap_name() == "Object")
               continue;
             if (((string)online[i]->query_property("chan_"+verb) == "on") ||
                 ((int)online[i]->query_property("chan_"+verb) == 1 ))
               whostr += "*"+online[i]->query_cap_name()+"\n";
             else
               whostr += online[i]->query_cap_name()+"\n";
           }

         write(sprintf("\n%*#-s\n",cols,whostr));
         return 1;    
    }
    if( str[0]=='!' && 
        ( verb != "lord" && verb != "cre" && verb != "demi" 
          && verb != "god" ) ) str = " "+str;

    if( verb == "guild" )
    {
        if( !GUILD )
        {
             message("You are not a member of any guild.\n","",TP);
             return 1;
        }
        verb = (string)GUILD->query_name();
    }
//  ADDING THIS BIT
    if( (verb == "chat") && (!TP->query_property("chan_chat")) )
    {
        message("You do not have that channel.\n","",TP);
        return 1;
    }
//  END ADDED BIT
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
                        TP->add_property("chan_"+verb,"off");
//  MODIFIED THE ABOVE LINE
                   return 1;
            break;
            case "on" :
                   message("Ok, you turn on the "+verb+"-channel.\n","",TP);
                   TP->add_property( "chan_"+verb, "on" );
                   return 1;
            break;
            default : message("Something bad just happened, " +
                              "contact a creator.\n","",TP  );
       }
    }

    if ( (string)TP->query_property("chan_"+verb) == "off" )
//  MODIFIED THE ABOVE LINE
    {
        message("You don't have that channel on.\n","",TP);
        return 1;
    }
    switch( verb )
    {
        case "god"   :
            Gval = filter_check( verb, str, GOD );
            break;
        case "demi"  :
            Gval = filter_check( verb, str, DEMI );
            break;
        case "lord"  :
            Gval = filter_check( verb, str, LORD );
            break;
        case "cre"   :
            Gval = filter_check( verb, str, CRE );
        break; //BREAK GODDAMIT!!! ARGH!!!
        default      :
            Gval = filter_check( verb, str );
    }
    message( Gval[2], Gval[1], Gval[0], TP );
    return 1;
}
