#include "udp.h"
#include "socket.h"
#include "inet.h"
/*
 * This has the list of cd muds that are known.  We get this from the
 * mudlist server when we boot.
 */

#define SAVEFILE "/net/save/nameserver_cd"

static object monitor;
mapping known_muds;
static int my_port, my_socket;

void create() {
  known_muds = ([ ]);
  seteuid(getuid());
  if(file_length(SAVEFILE+".o"))
    restore_object(SAVEFILE, 1);
  call_out("startup_udp", 5);
  call_out("do_pings", 30*60); /* Do this every 5 minutes */
} /* create() */

void send_startup_udp(string host, int port) {
  NAMESERVER->lookup_service("cd-udp", lower_case(MUD_NAME), "finish_lookup",
                             ({ host, port }));
  (UDP_PATH+UDP_MUDLIST_Q)->send_mudlist_q(host, port);
} /* send_startup_udp() */

void startup_udp() {
  send_startup_udp(MUDLIST_UDP[0], MUDLIST_UDP[1]);
} /* startup_udp() */

void do_pings() {
  int i;
  string *muds, ping_packet;

  call_out("do_pings", 5*60);
/* Both to keep us alive in tehir arrays and to check on dead muds. */
  muds = keys(known_muds);
  for (i=0;i<sizeof(muds);i++) {
    if (!mapp(known_muds[muds[i]])) continue;
    known_muds[muds[i]][UDP_NO_CONTACT] = known_muds[muds[i]][UDP_NO_CONTACT]+1;
    PING_Q->send_ping_q(known_muds[muds[i]]["HOSTADDRESS"],
                        known_muds[muds[i]]["PORTUDP"]);
    if (known_muds[muds[i]][UDP_NO_CONTACT] >= MAX_RETRYS) {
      map_delete(known_muds, muds[i]);
    }
  }
} /* do_pings() */

void finish_lookup(string service, string addr, int port, mixed *args) {
  string host;
  int dport;

  host = args[0];
  dport = args[1];
  my_port = port;
  this_object()->send_udp(host, dport, "@@@"+UDP_STARTUP+
                                       this_object()->start_message()+
                                       "@@@\n");
  if (!my_socket) {
    my_socket = socket_create(DATAGRAM, "read_callback", "close_callback");
    if (my_socket <= 0)
      return ;
    if (socket_bind(my_socket, port) <= 0)
      socket_close(my_socket);
  }
} /* finish_lookup() */

string start_message() {
  return "||NAME:"+capitalize(MUD_NAME)+
         "||VERSION:10.10"+
         "||MUDLIB:Discworld"+
         "||HOST:"+query_host_name()+
         "||PORT:"+( (["aurora":"3000","aurora-2":"4000"])[MUD_NAME] )+
         "||PORTUDP:"+my_port+
         "||TIME:"+ctime(time());
} /* start_message() */

void send_udp(string host, int port, string msg) {
  int sock;

  if (monitor) tell_object(monitor, "Sending "+msg);
  sock = socket_create(DATAGRAM, "read_callback", "close_callback");
  if (sock <= 0) {
    log_file("CD_NAMESERVER", "Failed to open socket to "+host+" "+port+"\n");
    return ;
  }
  socket_write(sock, msg, host+" "+port);
  socket_close(sock);
} /* send_udp() */

void read_callback(int sock, string msg, string addr) {
  string func, rest, *bits, name, arg;
  mapping args;
  int i;

  if (monitor) tell_object(monitor, "Got "+msg);
  if (!sscanf(msg, "@@@%s||%s@@@%*s", func, rest)) {
    if (!sscanf(msg, "@@@%s@@@%*s", func)) {
      return ;
    }
    rest = "";
  }
  sscanf(addr, "%s %*s", addr);
  bits = explode(rest, "||");
  args = ([ ]);
  for (i=0;i<sizeof(bits);i++) {
    if (sscanf(bits[i], "%s:%s", name, arg) == 2) {
      args[name] = arg;
    }
  }
  args["HOSTADDRESS"] = addr;
  if (mapp(known_muds[args["NAME"]]))
    known_muds[args["NAME"]][UDP_NO_CONTACT] = 0;
/* Ok, now we need to lookup the command and execute it... */
  if (file_size(UDP_PATH+func+".c") > 0)
    (UDP_PATH+func)->incoming_request(args);
/* Otherwise, we just ignore it... */
} /* read_callback() */

mapping query_known_muds() { return known_muds + ([ ]); }

void set_mud_info(string name, mapping junk) { 
  if (previous_object() != this_object() &&
      file_name(previous_object())[0..strlen(UDP_PATH)-1] != UDP_PATH)
    return ;
  known_muds[name] = junk;
  if (lower_case(name) != name)
    known_muds[lower_case(name)] = name;
  call_out("save_me", 0);
}

void save_me()
{
  seteuid(geteuid());
  save_object(SAVEFILE, 1);
} /* set_mud_info() */

void zap_mud_info(string name, mapping junk) { 
  if (previous_object() != this_object() &&
      file_name(previous_object())[0..strlen(UDP_PATH)-1] != UDP_PATH)
    return ;
  map_delete(known_muds, name);
} /* zap_mud_info() */

mapping query_mud_info(string name) {
  mixed bing;

  bing = known_muds[name];
  if (stringp(bing))
    return known_muds[bing];
  return bing;
} /* query_mud_info() */

int query_my_port() { return my_port; }

void set_monitor(object ob) { monitor = ob; }
object query_monitor() { return monitor; }