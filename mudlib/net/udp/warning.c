#include <standard.h>
#include "udp.h"
/*
 * The udp warning service... Hmmm...
 */

STDOB

void incoming_request(mapping info) {
  event(users(), "inform", "UDP warning from "+info["NAME"]+
        info["MSG"]+" Fakehost: "+
        info["FAKEHOST"], "udp-warning");
} /* incoming_request() */
