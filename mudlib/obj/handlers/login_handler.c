// 24 Sept 1993 Chrisy -
//    Changed all vairables "function" to funct". MAkes MudOS hiccup :)

inherit "std/object";

#include "login_handler.h"

#define SAVE_NAME "/save/login_handler"
/* 4 days.  I hope... */
#define TIME_OUT (60*60*24*4)

string *names;
mixed *functions;
mixed *objects;
static string *players_on;
static int number_players;
int immortal_lockout;
string *allowed_immorts;


void create() {
  names = ({ });
  functions = ({ });
  seteuid("Room");
  objects = ({ });
  immortal_lockout=0;
  allowed_immorts=({ });
  restore_object(SAVE_NAME,1);
  players_on = ({ });
  number_players = 0;
} /* create() */

int add_login_call(string player, mixed funct, mixed obj) {
  int pos, retval;

  if((pos = member_array(player, names)) != -1) {
    if(pointerp(funct) && pointerp(obj)) {
      if(sizeof(funct) != sizeof(obj))
        return 0;
      functions[pos] += funct;
      objects[pos] += obj;
    }
    else {
      if(pointerp(funct) || pointerp(obj))
        return 0;
      if(!functions) {
        functions = ({ });
        objects = ({ });
      }
      functions[pos] += ({ funct });
      objects[pos] += ({ obj });
    }
  }
  else {
    if(pointerp(funct) && pointerp(objects)) {
      if(sizeof(funct) != sizeof(obj))
        return 0;
      if(!functions) {
        functions += ({ });
        objects += ({ });
      }
      names += ({ player });
      functions += ({ funct });
      objects += ({ obj });
    }
    else {
      if(pointerp(funct) || pointerp(obj))
        return 0;
      names += ({ player });
      functions += ({ ({ funct }) });
      objects += ({ ({ obj }) });
    }
  }
  catch(save_object(SAVE_NAME,1));
  return 1;
} /* add_login_call() */

int remove_login_call(string player, mixed funct, mixed obj) {
  int pos, loop;

  if((pos = member_array(player, names)) == -1)
    return 0;
  if(stringp(funct) || stringp(obj)) {
    funct = ({ funct });
    obj = ({ obj });
  }
  if(stringp(funct) || stringp(obj))
    return 0;
  if(sizeof(funct) != sizeof(obj))
    return 0;
  printf("%d,  %O\n", pos, functions[pos]);
  for(loop = 0; loop < sizeof(functions[pos]); loop++) {
    int where;

    if((where = member_array(funct[pos], functions[pos])) ==
                member_array(obj[pos], objects[pos])) {
      functions[pos] = delete(functions[pos], where, 1);
      objects[pos] = delete(objects[pos], where, 1);
      loop--;
    }
  }
  if(!sizeof(functions[pos])) {
    names = delete(names, pos, 1);
    functions = delete(functions, pos, 1);
    objects = delete(objects, pos, 1);
  }
  catch(save_object(SAVE_NAME,1));
  return 1;
} /* remove_login_call() */

string *query_names() { return names; }
mixed *query_functions() { return functions; }
mixed *query_objects() { return objects; }

int player_logon(string player) {
  int pos, loop;

  if(lower_case(player) != (string)previous_object()->query_name())
    return 0;
  if((pos = member_array(player, players_on)) != -1)
    log_file("LOGIN", player+" logged in but was already on.\n");
   else
    players_on += ({ player });

  if((pos = member_array(player, names)) != -1) 
    {
    for(loop = 0; loop < sizeof(functions[pos]); loop++)
      call_out("do_call", 0, ({ functions[pos][loop], objects[pos][loop],
               player, LOGIN }) );
    }
  if((pos = member_array("all", names)) != -1) 
    {
    for(loop = 0; loop < sizeof(functions[pos]); loop++)
      call_out("do_call", 0, ({ functions[pos][loop], objects[pos][loop],
               player, LOGIN }) );
    }
} /* player_login() */

void do_call(mixed data) {
  call_other(data[1], data[0], data[2], data[3]);
} /* do_call() */

int player_logout(string player) {
  int pos;

  if((pos = member_array(player, players_on)) == -1)
    return 0;
  players_on = delete(players_on, pos, 1);
  if((pos = member_array(player, players_on)) != -1) {
    int loop;
 
    for(loop = 0; loop < sizeof(functions[pos]); loop++)
      call_out("do_call", 0, ({ functions[pos][loop], objects[pos][loop],
               player, LOGOUT }));
  }
  return 1;
} /* player_logout() */

string *query_players_on() { return players_on; }



/* immortal lockout thingy for OMIQS ...
   I hope this doesn't screw up anybody elses plans ...
   Sojan
*/

void enable_immort_lockout()
{
  if(!"/secure/master"->high_programmer(geteuid(previous_object()))) return;
  immortal_lockout=1;
  catch(save_object(SAVE_NAME, 1));
  write("Immortal Lockout enabled, please remember to disable once you have finished.\n");
  return;
}

void disable_immort_lockout()
{
  if(!"/secure/master"->high_programmer(geteuid(previous_object()))) return;
  immortal_lockout=0;
  catch(save_object(SAVE_NAME, 1));
  write("Immortal lockout disabled.\n");
  return;
}

int query_immort_lockout(string name)
{
  if(member_array(name, allowed_immorts)>-1) return 0;
  return immortal_lockout;
}

void add_allowed_immort(string name)
{
  if(!"/secure/master"->high_programmer(geteuid(previous_object()))) return;
  allowed_immorts+= ({ name, });
  catch(save_object(SAVE_NAME, 1));
  return;
}

int trai(string ele, string name)
{
  return ele!=name;
}

void remove_allowed_immort(string name)
{
  string *bing;
  if(!"/secure/master"->high_programmer(geteuid(previous_object()))) return;
  bing=filter_array(allowed_immorts, "trai", this_object(), name);
  allowed_immorts=bing;
  catch(save_object(SAVE_NAME, 1));
  return;
}
