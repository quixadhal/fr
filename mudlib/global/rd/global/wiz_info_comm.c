#define MASTER "/secure/master"
#define PEOPLER "/obj/handlers/peopler"
#define traceprefix(x)
#define trace(x)

#define C_NAME 0
#define C_DATA 1
#define C_OBJ 2
#define C_FUNC 3

// 24 Jul 95 Dyraen     I put the command gauge back in here as
//                      it cannot work as an external command.
 
varargs object *wiz_present(string str, object onobj, int nogoout);
string desc_object(mixed o);
string desc_f_object(object o);

static void wiz_commands() {
  add_action("do_gauge", "ga*uge");
  add_action("comm_info","comi*nfo");
} /* wiz_commands() */
     
/*
** commands in the app_commands will go to all players with
** level >= 20. This includes players who have opted to
** remain players rather than advancing to wizard. As such
** we must be careful in what we place here
*/
 
static void app_commands() {
} /* app_commands() */
 
/* These commands go to ALL players. Note that master.c
** gives only limited read/write access to dirs anyway,
** so the apparent security problems are NOT a problem
*/
 
static all_commands() {
} /* all_commands() */
 
static int do_gauge(string str) {
  int eval_cost;
  if (this_player(1) != this_object()) return 0;
  if(!str) {
    notify_fail("Usage : gauge command.\n");
    return 0;
  }
  eval_cost = command(str);
  write("\nThe command '" + str + "' took: " + eval_cost + " CPU cycles.\n");
  return 1;
} /* do_gauge() */

static string do_find_comm(string func, object ob) {
  string s, ping;
  object fish;
  s = "";
  if(ping = function_exists(func, ob))
      s += " found in " + ping;
    else
      s += " not found";
  fish = ob;
  while(fish = shadow(fish, 0))
    if(function_exists(func, fish))
      s += " shadowed by " + file_name(fish);
  s += ".\n";
  return s;
} /* do_find_comm() */

/*** By Dyraen@Rod ***/
int comm_info(string str) {
object on;
string *comms, xtra, s1, s2;
int i;
 
  if (str) {
    sscanf(str,"%s %s",s1,s2);
    if (s2) {
      s2 = this_player()->expand_nickname(s2);
      on = find_player(s2);
      str = s1;
    }
  }
  if (on)
    comms = on->query_commands();
  else
    comms = commands();

  if (!str || str == "0")
    for(i=0;i<sizeof(comms);i++) {
      if (comms[i][C_NAME] == "") comms[i][C_NAME] = "*";
      xtra = do_find_comm((string)comms[i][C_FUNC],(object)comms[i][C_OBJ]);
      write(comms[i][C_NAME]+"["+comms[i][C_DATA]+"] "+
            file_name(comms[i][C_OBJ])+"->"+comms[i][C_FUNC]+"()"+
            xtra);
    }
  for(i=0;i<sizeof(comms);i++) {
    if (comms[i][C_NAME] == "") comms[i][C_NAME] = "*";
    if (str == comms[i][C_NAME]) {
      xtra = do_find_comm((string)comms[i][C_FUNC],(object)comms[i][C_OBJ]);
      write(comms[i][C_NAME]+"["+comms[i][C_DATA]+"] "+
            file_name(comms[i][C_OBJ])+"->"+comms[i][C_FUNC]+"()"+
            xtra);
    }
  }
  return 1;
} /* comm_info() */
