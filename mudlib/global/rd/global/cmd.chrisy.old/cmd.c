// /global/cmd/cmd.c -- Inherit for object-based commands
// Prelimianary bodge version 4th August 1994 Chrisy

#include <standard.h>
#include <cmd.h>

static int position = 0, dodest = 0, doclone = 0;

void create()
{
	seteuid(getuid());

	TO->setup();
}

void dest_me()
{
	destruct(TO);
}

void clean_up()
{
	dest_me();
}

void setup() { return; }

static int cmd(string tail, mixed thisob) { return 0; }

string query_usage() { return 0; }
string query_short_help() { return 0; }

int _cmd(string tail, mixed thisob)
{
  string euid;

  // Set the euid to that of either the creator, or to PLAYER.
  seteuid(euid = geteuid(TP));

#ifdef _CMD_DEBUG
  write("_cmd:  euid(TO): "+euid(TO)+"  euid(TP): "+euid(TP)+"\n");
#endif

  // Will check who is using command and if allowed here sort of :)
  switch(position)
  {
case HIGH_LORD_CMD:
    if(!MASTER->query_highlord(euid))
      return 0;
    break;

case LORD_CMD:
    if(!MASTER->query_lord(euid))
      return 0;
    break;

case CREATOR_CMD:
    if(!TP->query_creator())
      return 0;
    break;
  }

	return cmd(tail, thisob);
}

int _query_position() { return position; }
int _query_dodest() { return dodest; }
int _query_doclone() { return doclone; }
