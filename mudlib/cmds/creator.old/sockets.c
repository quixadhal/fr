#include <standard.h>
#include <cmd.h>
inherit CMD_BASE;

void setup()
{
position = 1;
}

protected int cmd(string str, object me) {
write(dump_socket_status());
  return 1;
} /* do_sockets() */
 
