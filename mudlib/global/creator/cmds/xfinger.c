/* Hamlet, Feb 1996 */
#include <standard.h>
#include <cmd.h>

inherit CMD_BASE;

void setup(){
  position = 1;
}

string query_usage() { return "xfinger [-m] [-l] <player>\n"
                       "       xfinger [-l] [<user>]@<ipname|ipnumber>"; }

string query_short_help() {
 return "xfinger implements the standard unix 'finger' command (with "
        "frills removed).\n\n"
        "As an argument, it can take either a player's name, or ip "
        "addresses in either alphabetic or numeric formats.\n\n"
        "Options:\n"
        "  -m   finger the whole machine instead of the specific userid "
        "when using a\n"
        "       playername.\n"
        "  -l   get the long finger information rather than the 1-liner.\n\n"
        "Examples:\n"
        "  xfinger hamlet\n"
        "  xfinger -l -m hamlet\n"
        "  xfinger @mamaclaus.opup.org\n"
        "  xfinger icharles@128.169.92.86";
 }
 
static int cmd(string str, object me) {
  object xfinger_cmd;
  string name;
  string data;
  object per;
  int MACHINE = 0;
  int WIDE = 0;
  string ipnum;
  string extrajunk = "";
  int WASMATCH=1;
  
  notify_fail("Must specify user or host.\n");
  
  if(!str)
    return 0;
  
  while(WASMATCH) {
    WASMATCH = 0;
    if(str[0..2] == "-m ") {
      MACHINE = 1;
      if(strlen(str) < 4)
        return 0;
      str = str[3..strlen(str)-1];
      WASMATCH = 1;
    }
    
    if(str[0..2] == "-l ") {
      WIDE = 1;
      if(strlen(str) < 4)
        return 0;
      str = str[3..strlen(str)-1];
      WASMATCH = 1;
    }
  }    
  
  if(str[0..0] != "@") {  /* It may be a player's name. */
    name = me->expand_nickname(str);
    if (per = find_player(lower_case(name))) {
      if(per->query_ident() && !MACHINE)
        data = per->query_ident() + "@";
      else
        data = "@";
      
      ipnum = query_ip_number(per);
      extrajunk = query_ip_name(per);

      if(ipnum == extrajunk)
        extrajunk = name;
      else
        extrajunk += " - "+name;
        
      data += ipnum;
    }
  }

  if(!data) { /* Nope, this was  @something ... not a player. */
    if(str[0..0] == "@")
      data = str;
    else
      data = "@"+str;
  }
  
  if(WIDE)
    data = "/W "+data;
      
  if (xfinger_cmd = clone_object("/secure/xfinger_cmd")) {
    if(xfinger_cmd->do_xfinger(data, me, extrajunk))
      write("Ok.. Please wait..\n");
    else
      write("xfinger: The name you passed must not have been valid.\n");
    return 1;
  } 
  else {
    notify_fail("Oops... xfinger_cmd didn't want to clone.\n");
    return 0;
  }
} /* cmd() */
