#include <standard.h>
#include "udp.h"
/*
 * Someone replyed to our query and has sent us their mudlist.
 * Lets all go bing in the garden.
 */

void incoming_request(mapping info) {
  string *junk, *inf, name, value;
  int i, j;
  mapping new, old;

  junk = keys(info);
  for (i=0;i<sizeof(junk);i++) {
    inf = explode(info[junk[i]], "|");
    new = ([ ]);
    for (j=0;j<sizeof(inf);j++)
      if (sscanf(inf[j], "%s:%s", name, value) == 2)
        new[name] = value;
    if (!new["NAME"] || new["NAME"] == mud_name()) continue;
    old = NAMESERVER_CD->query_mud_info(new["NAME"]);
    if (!old)
      NAMESERVER_CD->set_mud_info(new["NAME"], new);
    else {
      inf = keys(new);
      for (j=0;j<sizeof(inf);j++)
        old[inf[j]] = new[inf[j]];
      NAMESERVER_CD->set_mud_info(new["NAME"], old);
    }
  }
} /* incoming_request() */

void create() {
  seteuid(getuid());
} /* create() */

void dest_me() { destruct(TO); }
