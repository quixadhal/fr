/* Hamlet, Mar 1996 */
#include <standard.h>
#include <cmd.h>
#include <man.h>

inherit CMD_BASE;

void setup(){
  position = 1;
}

string query_usage() { return "man <topic>\n"; }

string query_short_help() {
  return "man gives you the manual page for a given topic.\n"
         "If no argument is given, or the topic is a directory,\n"
         "the man menu system is entered.\n";
}
 
static int cmd(string str, object me) {
  object man_obj;

  man_obj = clone_object(MAN_OBJECT);
  
  if(!man_obj)
    tell_object(me,"It appears that the manual page displayer is broken.\n");
  else
    man_obj->do_query(str,me); 
  
  return 1;
} /* cmd() */
