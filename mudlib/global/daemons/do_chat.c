// Coded by Begosh@RotD 9th of July 1994
// Player, guild, cre, lord and god chat
 
 
#define CHECKER "global/checker"
#define WIMP_CHAT 10
#define CRE children("global/creator")+children("global/lord")+children("global/god")
#define LORD children("global/lord")+children("global/god")
#define GOD children("global/god")
 
int do_chat( string str, object obj )
{
    string class, prompt;
    object *receivers;
    int emoted, forced;
 
    class = query_verb();
    if(!str || str == "")
    {
        str = "Usage: "+class+" < message >";
        message( str, "", obj);
        return 1;
    }

    if( str[0] == '!' ) 
    { 
        forced = 1; 
        str = str[1..( strlen(str) - 1 )];
    }

    if( str[0] == '@' ) 
    { 
         emoted = 1;
         str = str[1..( strlen(str) - 1 )]; 
    }

 
    switch(class)
    {
        case "guild" :
          if( !obj->query_guild_ob() )
          {
              message("You are not a member of any guild.","",obj);
              return 1;
          }
            if( forced ) forced = 0;
          if( str == "off" || str == "on" )
          {
            if( str == "off" )
            {
                if( !obj->query_guild() )
                {
                    message("Ok. The guild-channel is now turned off.","",obj);
                    obj->set_guild(1);
                    return 1;
                }
                else
                {
                    message("You haven't turned the guild-channel on.","",obj);
                    return 1;
                }
            }
            else
            {
                if( !obj->query_guild() )
                {
                    message("The guild-channel is already on.","",obj);
                    return 1;
                }
                else
                {
                    message("Ok. The guild-channel is now turned on.","",obj);
                    obj->set_guild(0);
                    return 1;
                }
            }
          }
          else if( obj->query_guild() )
          {
              message("You doesn't have the guild-channel on.","",obj);
              return 1;
          }
          prompt = (string)obj->query_guild_ob();
     // Using prompt as a var here, then I  don't  need as many vars
          receivers = filter_array( users(), "check_guild", CHECKER, prompt );
        break;

       case "chat" :
          if( forced ) forced = 0;
         if( str == "off" || str == "on" )
         {
           if( str == "off" )
           {
               if( !obj->query_chat() )
               {
                   message("Ok. The chat-channel is now turned off.","",obj);
                   obj->set_chat(1);
                   return 1;
               }
               else
               {
                   message("You haven't turned the chat-channel on.","", obj);
                   return 1;
               }
           }
           else
           {
               if( !obj->query_chat() )
               {
                   message("The chat-channel is already on.","",obj);
                   return 1;
               }
               else
               {
                   message("Ok. The chat-channel is now turned on.","",obj);
                   obj->set_chat(0);
                   return 1;
               }
           }
         }
         else if( obj->query_chat() )
         {
             message("You doesn't have the chat-channel on.","",obj);
             return 1;
         }
         receivers = filter_array( users(), "check_chat", CHECKER );
      break;
 
      case "cre" :
           if( obj->check_earmuffs("creator-tell") )
           {
                message("You have creator-channel earmuffed!","",obj);
                return 1;
           }
           receivers = filter_array( CRE, "check_cre", CHECKER, forced );
      break;
 
      case "lord" :
           if( obj->check_earmuffs("lord-tell") )
           {
                message("You have lord-channel earmuffed!","",obj);
                return 1;
           }
             receivers = filter_array( LORD, "check_lord", CHECKER, forced );
      break;
 
      case "god" :
           if( obj->check_earmuffs("god-tell") )
           {
                message("You have god-channel earmuffed!","",obj);
                return 1;
           }
             receivers = filter_array( GOD, "check_god", CHECKER, forced );
      break;
 
     }
 
     if( forced  )
     {
         prompt = "You force-"+class+"-tell: ";
         message( str, prompt, obj );
         prompt = (string)obj->query_cap_name()+" [Forced-"+
                 class+"]: ";
         message( str, prompt, receivers, obj );
         return 1;
     }
     else if( emoted )
     {
         if( class == "chat" )
         {
             if( obj->query_channel_block() )
             {
                 message("You can't chat-emote.","", obj);
                 return 1;
             }
             else if(!obj->query_property("guest") &&
                     obj->query_level() > 10)
             {
                 if( (int)obj->adjust_social_points(-strlen(str))<0 )
                 {
                     message("You dont have enough social points.","",obj);
                     obj->adjust_social_points(strlen(str));
                     return 1;
                 }
             }
         }
 
         if( class == "guild" )
         {
             if( obj->query_channel_block() )
             {
                 message("You can't use guild-emote.","",obj);
                 return 1;
             }
             prompt = "["+
               capitalize((string)obj->query_guild_ob()->query_name())+"] ";
             str = (string)obj->query_cap_name()+" "+str;
             message( str, prompt, receivers );
             return 1;
         }
         else
         {
             prompt = "["+capitalize(class)+"] ";
             str = (string)obj->query_cap_name()+" "+str;
             message( str, prompt, receivers );
             return 1;
         }
     }
     else
     {
         if( class == "911" ) class = "emergency";
         if(class=="emergency") receivers = CRE;
         if( class == "chat" )
         {
             if( obj->query_channel_block() )
             {
                 message("You cannot chat here.","",obj);
                 return 1;
             }
             else if( !obj->query_property("guest") &&
                    obj->query_level() > 10)
             {
                 if((int)obj->adjust_social_points(-strlen(str))<0)
                 {
                     message("You don't have enough social points.","",obj);
                     obj->adjust_social_points( strlen(str) );
                     return 1;
                 }
             }
             else
             {
               if ((int)obj->adjust_social_points(-WIMP_CHAT)<0)
               {
                   message("You don't have enough social points.","",obj);
                   obj->adjust_social_points(WIMP_CHAT);
                   return 1;
               }
             }
           }
           if( class == "guild" )
           {
                if( obj->query_channel_block() )
               {
                   message("You can not guild-tell.","",obj);
                   return 1;
               }
               prompt = "You "+
                  (string)obj->query_guild_ob()->query_name()+"-tell: ";
               message( str, prompt, obj );
               prompt = (string)obj->query_cap_name()+" ["+
                       capitalize((string)obj->query_guild_ob()->query_name())+"]: ";
               message( str, prompt, receivers, obj );
               return 1;
           }
           else
           {
               prompt = "You "+class+"-tell: ";
               message( str, prompt, obj );
               prompt = (string)obj->query_cap_name()+" ["+
                       capitalize(class)+"]: ";
               message( str, prompt, receivers, obj );
               return 1;
           }
       }
       return 1;
}
