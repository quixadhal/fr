#include <standard.h>
#include "udp.h"
/*
 * Finger a wiz on another mud.
 */

void create() { SETEUID; }
void dest_me() { destruct(this_object()); }

void send_gfinger_q(string mud, string wiz) {
  mapping minfo;

  if (mud == mud_name())
    return ;
  minfo = NAMESERVER_CD->query_mud_info(mud);
  if (!minfo)
    return ;
  NAMESERVER_CD->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
                          "@@@"+UDP_GFINGER_Q+
                          "||NAME:"+mud_name()+
                          "||PORTUDP:"+NAMESERVER_CD->query_my_port()+
                          "||PLAYER:"+wiz+
                          "||ASKWIZ:"+this_player()->query_name()+
                          "@@@\n");
} /* send_gtell() */

void incoming_request(mapping info) {
  string finger;

  if (info["NAME"] && info["PORTUDP"]) {
    if (info["NAME"] == mud_name())
      return ;

    if (!NAMESERVER_CD->query_mud_info(info["NAME"]))
      PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

    finger = "/secure/finger"->finger_info(lower_case(info["PLAYER"]));
    if (!finger) finger = "I am most dreadfully sorry, but "+info["PLAYER"]+
                          "has not visited here yet.  Try again later :)\n";
    NAMESERVER_CD->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
                        "@@@"+UDP_GFINGER_A+
                        "||NAME:"+mud_name()+
                        "||PORTUDP:"+NAMESERVER_CD->query_my_port()+
                        "||ASKWIZ:"+info["ASKWIZ"]+
                         "||MSG:"+finger+
                        "@@@\n");
  }
} /* incoming_request() */
