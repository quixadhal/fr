// global/psoul.c

// presumably this is the infamous "Pinkfish" soul

// 1995 Jun 15 Laggard      revised command priorities, now in commands.h
//                          move properties to new property.h
//                          moved reset_queue into its own routine,
//                           - called from player, and stop action.
//                          renamed and rewrote command_hb
//                           - progressive delay of queue times
//                           - short fast tests
//                          renamed and rewrote command_queue
//                           - expands aliases and history _before_ queuing
//                           - short fast tests
//                          removed all callouts
//                           - had too many, one per command
//                           - out of sync with heartbeats
//                           - broke say and write in command()
// 1995 Jun 28  Laggard     removed stop command, use restart instead
//                           - stop could be used to defeat move timing,
//                             because of need to execute true stop command
//                           - now sets time_left to 0, to force wait
//                           - no need to check for stop in final_check
//                          removed some older unused code

#include "commands.h"
#include "player.h"
#include "property.h"
 
inherit "/global/alias";
inherit "/global/nickname";

 
static int last_command;    // time of last command processed
static int time_left;       /* Time left for this round. */

private static string doing_it;  // queued command, don't queue it!

#define QUEUE_LIMIT 20
private static string  *queued_commands;
private static int  queue_depth;    /* Depth on the queue of the current lot of commands */


#define RUPT_WAIT_COUNT 4    // # heartbeats to wait

#define RUPT_FUNCTION   0
#define RUPT_OBJECT     1
#define RUPT_ARG        2
private static mixed *interrupter;  // interrupts normal command sequence
private static int    interrupting; // waiting


void create()
{
  time_left = ROUND_TIME;
  last_command = time();

  nickname::create();
} /* create() */
 

// not called anywhere??? {Laggard}
void no_time_left()
{
  time_left = -ROUND_TIME;
} /* no_time_left() */
 

// called from player
void soul_commands()
{
    add_action("soul_force_thingy", "SOUL_FORCE",   A_P_SOUL_FORCE);
//  add_action("reset_queue",       "stop",         A_P_STOP_QUEUE);   // use restart instead

    add_action("command_queue",     "*",            A_P_CHECK_TIME);
//  add_action("alias_com",         "*",            A_P_CHECK_ALIAS);  // now called from command_queue
    add_action("nosoul",            "nosoul",       A_P_NO_SOUL);
    add_action("soul_com",          "*",            A_P_SOUL);
    add_action("final_check",       "*",            A_P_CHECK_FINAL);

    this_object()->add_alias("soul");
    alias_commands();
    nickname_commands();
    history_commands();
} /* soul_commands() */
 
int nosoul(string str) {
  if (str == "on")
    this_object()->add_property("nosoul",1);
  else if (str == "off")
    this_object()->remove_property("nosoul");
  else
    if (this_object()->query_property("nosoul"))
      this_object()->remove_property("nosoul");
    else
      this_object()->add_property("nosoul",1);
  if (this_object()->query_property("nosoul"))
    write("Soul turned off.\n");
  else
    write("Soul turned on.\n");
  return 1;
} /* nosoul() */
 
int soul_force_thingy(string str) {
  string str1, str2;
 
  if (sscanf(str,"%s %s", str1, str2) != 2)
    str1 = str;
  if (!this_object()->query_property("nosoul")) {
    if (!find_object(SOUL_OBJECT))
      if (catch(call_other(SOUL_OBJECT, "??"))) {
        write("Soul errors!  Notify a wiz at once.\n");
        write("Use nosoul to turn the soul back on when it is fixed.\n");
        this_object()->add_property("nosoul",1);
        return 0;
      }
    SOUL_OBJECT->soul_command(str1,str2);
  }
  return 1;
} /* soul_force_thingy() */
 
int do_soul_force(string str) {
  return command("SOUL_FORCE "+str);
} /* do_soul_force() */
 
int alias_com(string str) {
  string str1, str2;
  if (sscanf(str,"%s %s", str1, str2) != 2)
    str1 = str;
  return exec_alias(str1, str2);
} /* alias_com() */
 
int soul_com(string str) {
  string str1, str2;
  int i;
  if (sscanf(str,"%s %s", str1, str2) != 2)
    str1 = str;
  if (!this_object()->query_property("nosoul")) {
    if (!find_object(SOUL_OBJECT))
      if (catch(call_other(SOUL_OBJECT, "??"))) {
        write("Soul errors!  Notify a wiz at once.\n");
        write("Use nosoul to turn the soul back on when it is fixed.\n");
        this_object()->add_property("nosoul",1);
        return 0;
      }
    i=(int)SOUL_OBJECT->soul_command(str1,str2);
    if (i)
      return 1;
  }
  return 0;
} /* soul_com() */
 
int soul_com_force(string str) {
  string str1,str2;
  if (file_name(previous_object()) != SOUL_OBJECT)
    return 0;
  command(str);
  return 1;
  if (sscanf(str, "%s %s", str1, str2) != 2)
    str1 = str;
  SOUL_OBJECT->soul_command(str1, str2);
} /* soul_com_force() */
 
void do_soul(string str, mixed bing) {
  say(str, bing);
} /* do_soul() */
 
int query_time_left() { return time_left; }
 
int adjust_time_left(int i) { return time_left += i; }


/*
 * This should be called each heart beat.
 */
static void command_hb()
{
    string str;

    if (interrupting)
    {
        if ( --interrupting <= 0 )
        {
            catch(call_other(interrupter[RUPT_OBJECT], interrupter[RUPT_FUNCTION],
                                                    0, interrupter[RUPT_ARG]));
            interrupter = 0;
            interrupting = 0;
        }
        return;
    }

    if ( time_left > 0 )
    {
        int save_depth;

        time_left = ROUND_TIME;         // cap idle command time

        while ( time_left > 0  &&  queue_depth )
        {
            str = queued_commands[0];
            time_left -= DEFAULT_TIME;   // ensure other players get turns

            doing_it = str;
            queue_depth = 1;  // in case it spawns more commands 
            catch(command(str));
            queue_depth = sizeof(queued_commands);
            doing_it = 0;
            
            if ( queue_depth > 1 )
            {
                // remove the completed command from the list
                queued_commands = queued_commands[1..(--queue_depth)];
            }
            else
            {
                queued_commands = 0;
                queue_depth = 0;
            }
        }
    }
    else
    {
        time_left += ROUND_TIME;
    }
}  /* command_hb */
 

// this is a strange little utility to give delayed reactions,
// in the middle of a command stream.  Only one allowed.
void set_interupt_command(string func, mixed ob, mixed arg)
{
    if ( interrupting )
    {
        catch(call_other(interrupter[RUPT_OBJECT], interrupter[RUPT_FUNCTION],
                         -time_left, interrupter[RUPT_ARG]));
    }
    interrupting = RUPT_WAIT_COUNT;
    interrupter = ({ func, ob, arg });
} /* set_interupt_command() */
 

// stop and restart intercept {Laggard}
int reset_queue(string str)
{
    if (interrupting)
    {
        catch(call_other(interrupter[RUPT_OBJECT], interrupter[RUPT_FUNCTION],
                         -time_left, interrupter[RUPT_ARG]));
        interrupter = 0;
        interrupting = 0;
    }

    if ( queue_depth )
    {
        write("Removed queue.\n");
        queued_commands = 0;
        queue_depth = 0;
    }

    time_left = 0;
    return 0;  // pass on to next command
}


int command_queue(string str)
{
  mixed ret_val;

  last_command = time();

  // toss commands while passed out
  if ( (ret_val = this_object()->query_property(PASSED_OUT_PROP)) )
  {
    ret_val = ((int)ret_val==1)?"unconcious":ret_val;
    write("You can't do anything while you are "+(string)ret_val+".\n");
    return 1;
  }

  if ( doing_it == str )
  {
    // don't alias or requeue commands already queued {Laggard}
    return 0;
  }

  // expand aliases and history before checking time and queuing.
  // avoids doing such expansion in heart_beats {Laggard}

  str = replace_string(str,"@@",""); /* line from aragorn's head! */
  add_history(str);

  if ( alias_com(str) ) 
  {
    return 1;
  }

#ifndef QUEUE_ALL
  if ( time_left > 0  &&  !queue_depth  &&  !interrupting )
  {
    time_left -= DEFAULT_TIME;
    return 0;
  }
#endif

  if ( queue_depth <= 0 )
  {
    queued_commands = ({ str });
    queue_depth = 1;
    set_heart_beat(1);                    // ensure heart_beat is going
  }
  else if ( queue_depth < sizeof( queued_commands ) )
  {
    // this command came from a queued command, maintain order {Laggard}
    queued_commands = queued_commands[0..(queue_depth - 1)] + ({ str })
                    + queued_commands[queue_depth .. sizeof(queued_commands)];
    queue_depth++;
  }
  else if ( queue_depth < QUEUE_LIMIT )
  {
    queued_commands += ({ str });
    queue_depth++;
  }
  else
  {
    write("Too many queued commands.  Restart will free queue.\n"
        + "Discarding "+str+".\n");
  }
  return 1;
} /* command_queue() */
 

int final_check(string str)
{
  time_left += DEFAULT_TIME;  // give back time taken in command_queue above
  return 0;
} /* final_check() */
