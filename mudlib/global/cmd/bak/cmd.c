// /global/cmd/cmd.c -- Inherit for object-based commands

#include <standard.h>
#include <cmd.h>

static int position = 0, dodest = 0, doclone = 0;
static object command_giver;

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

#ifdef CMD_AURORA
static int cmd(string tail) { return 0; }
#endif
#ifdef CMD_FR
static int cmd(string tail, object thisob) { return 0; }
#endif

string query_usage() { return 0; }
string query_short_help() { return 0; }

#ifdef CMD_AURORA
int _cmd(string tail)
#endif
#ifdef CMD_FR
int _cmd(string tail, object thisob)
#endif
{
  string euid;
  int ret;

  if(previous_object() != find_object(CMD_HANDLER))
    return 0;

#ifdef CMD_AURORA
  command_giver = TP;
#endif
#ifdef CMD_FR
  command_giver = thisob;
#endif

  // Set the euid to that of either the creator, or to PLAYER.
  seteuid(euid = geteuid(command_giver));

  // Will check who is using command and if allowed here sort of :)
  switch(position)
#ifdef CMD_AURORA
  {
  case HIGH_LORD:
    if(!MASTER->query_highlord(euid))
      return 0;
    break;

  case LORD:
    if(!MASTER->query_lord(euid))
      return 0;
    break;

  case CREATOR:
    if(!command_giver->query_creator())
      return 0;
    break;
  }
#endif
#ifdef CMD_FR
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
		if(!thisob->query_creator())
			return 0;
		break;
	}
#endif

#ifdef CMD_AURORA
	ret = (int)TO->cmd(tail);
#endif
#ifdef CMD_FR
	ret = cmd(tail, thisob);
#endif

	seteuid(getuid());

	return ret;
}

int _query_position() { return position; }
int _query_dodest() { return dodest; }
int _query_doclone() { return doclone; }
