#include <udp.h>
#include <inet.h>
 
#define	SYNTAX	"Syntax: mudlist [optional mudname]\n"

void wiz_commands() {
  add_action("do_mudlist", "mudlist");
  add_action("do_ping", "ping");
  add_action("do_support", "support");
} /* wiz_commands() */

int do_mudlist(string str) {
   mapping mudlist_cd, mudlist;
   mixed *muds, bing;
   string output, flag;
   int loop;
 
   /*	Obtain mapping containing mud data */
 
   mudlist_cd = NAMESERVER_CD->query_known_muds();
   mudlist = NAMESERVER->query_machines();
  mudlist = ([ ]);
 
   if(!mudlist_cd) {
     write("Mudlist:  No muds are presently stored in the mud name server.\n");
     return 1;
   }

   if (!str) str = ""; 
   /*
    * 	If mudname provided, search server's database for a match
    *	and display its cooresponding address
    */
   if (sscanf(str, "-%s", flag) == 1) {
     if (sscanf(flag, "%s %s", flag, str) != 2)
       str = "";
   }

   switch (flag) {
     case "query" :
/* We want to query the mudlist off this mud. */
       bing = mudlist_cd[str];
       if (stringp(bing))
         bing = mudlist_cd[bing];
       if (!bing) {
/* Might be an address... */
         if (sscanf(str, "%s %s", str, flag) != 2) {
           notify_fail("Syntax: mudlist query <mud_name/address port>\n");
           return 0;
         }
         (UDP_PATH+"mudlist_q")->send_mudlist_q(str, flag);
         write("Off it goes on its merry way.\n");
         return 1;
       }
       (UDP_PATH+"mudlist_q")->send_mudlist_q(bing["HOSTADDRESS"],
                                              bing["PORTUDP"]);
       write("Off it goes on its merry way.\n");
       return 1;
   } 
   if(str && str != "") {

     str = lower_case(str);
     bing = mudlist_cd[str];
     if (stringp(bing))
       bing = mudlist_cd[bing];

     if (mapp(bing)) {
       write(capitalize(str)+"\t\t" + bing["HOSTADDRESS"]+"("+
             bing["HOST"]+") "+bing["PORT"]+"\n"+
             "Mudlib: "+bing["MUDLIB"]+" ("+
             bing["VERSION"]+")\nTime last updated "+
             bing["TIME"]+"\n");
       return 1;
     }

     str = lower_case(str);

     if (mudlist[str]) {
        write(capitalize(str)+"\t\t"+mudlist[str]+"\n");
        return 1;
     }
     write("Requested mud is not listed in " + capitalize(MUD_NAME) +
           "'s name server.\n");
 
     return 1;
   }
 
   /*	Get list of all mud names within name server */
 
   muds = keys(mudlist_cd) + keys(mudlist);
 
   /*	Place mudlist into alphabetical format */
 
   muds = sort_array( muds, "compare", this_object() );
 
   output = sprintf("%-=24s%-=23s %-=8s\n", "Mud name\n========",
                           "Address\n=======", "Port\n====");
 
   /*	Loop through mud list and store one by one */
 
   for(loop=0; loop<sizeof(muds); loop++) {
     if (mapp(mudlist_cd[muds[loop]])) {
       output += sprintf("%-24s%-23s %4s\n", "(CD) "+capitalize(muds[loop]),
                 mudlist_cd[muds[loop]]["HOSTADDRESS"],
                 mudlist_cd[muds[loop]]["PORT"]);
     } else if (mudlist[muds[loop]]) {
       sscanf(mudlist[muds[loop]], "%s %s", str, flag);
       output += sprintf("%-24s%-23s %4s\n", capitalize(muds[loop]), str, flag);
     }
   }
 
   /*	Display dumped mudlist output through user's more pager */
 
   this_player()->more_string( output );
 
   return 1;
} /* cmd_mudlist() */
 
/*	Comparison function for alphabetical sorting */
 
int compare(string one, string two) {  return strcmp(lower_case(one), lower_case(two));  }


/*
 * Does a strange intermud ping thingy.
 */
int do_ping(string str) {
  string host, port;

  if (!str || sscanf(str, "%s %s", host, port) != 2) {
    notify_fail("Syntax: ping <host> <port>\n");
    return 0;
  }
  (UDP_PATH+"ping_q")->send_ping_q(host, port);
  write("Off goes the ping, long live the ping!\n");
  return 1;
} /* do_ping() */

int do_support(string str) {
  string protocol, mud, param, type;
  mapping minfo;

  if (!str || sscanf(str, "%s %s", mud, type) != 2) {
    notify_fail("Syntax: support <mud> <type> [param]\n");
    return 0;
  }
  minfo = NAMESERVER_CD->query_mud_info(mud);
  if (!minfo) {
    notify_fail("No such mud "+mud+".\n");
    return 0;
  }
  sscanf(type, "%s %s", type, param);
  (UDP_PATH+"support_q")->send_support_q(minfo["HOSTADDRESS"], minfo["PORTUDP"],
                                        type, param);
  write("Off it wombles into the wild blue yonder.\n");
  return 1;
} /* do_support() */
