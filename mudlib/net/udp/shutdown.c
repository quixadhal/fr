#include <standard.h>
#include "udp.h"
/*
 * Some mud or rather has decied to tell us it is shuting down...
 */
void incoming_request(mapping info) {
  NAMESERVER_CD->zap_mud_info(info["NAME"]);
} /* incoming_request() */

void create() {
  seteuid(getuid());
} /* create() */

void dest_me() { destruct(TO); }
