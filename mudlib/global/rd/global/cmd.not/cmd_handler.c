// /global/cmd/cmd_handler.c  -- Object based command handler
// Preliminary bodge version 4 aug 1994 Chrisy

//#include <aurora/standard.h>
//#include <aurora/cmd.h>
#include "standard.h"
#include "cmd.h"

static mapping cmd_dirs =
([
	"/global/player/cmds/" : "Player",
	"/global/creator/cmds/" : "Creator",
	"/global/lord/cmds/" : "Lord",
"/global/demi/cmds/" : "Demi",
"/global/god/cmds/"  : "God",
	"/net/cmds/" : "InterMUD network",
	"/global/cmd/cmds/" : "Command handler",
]);

static mapping cmd_hash = ([ ]);  // For commands already found
static string last_dir = "";      // Last directory a command was found in

void create()
{
	seteuid(getuid());
}

void dest_me()
{
	destruct(TO);
}

int clean_up()
{
	return 0;
}

// The real code :)

string find_cmd(string verb)
{
	// Try to find the command for 'verb', or return 0
	// if not found. Remember it's location..

	string s, *dirs;
	int i;

	if(cmd_hash[verb])
	{
		last_dir = cmd_hash[verb]["dir"];
		return cmd_hash[verb]["file"];
	}

	dirs = m_indices(cmd_dirs);

	for(i=0; i<sizeof(dirs); i++)
	{
		s = dirs[i] + verb;
		if(file_size(s+".c") > 0)
		{
			last_dir = dirs[i];
			cmd_hash[verb] = ([ "file" : s, "count" : 0 ]);
			cmd_hash[verb]["dir"] = last_dir;
			return s;
		}
	}
	return 0;
}

int cmd(string verb, string tail, object thisob)
{
	object ob;
	string s;
	int ret;

#ifdef _CMD_DEBUG
	write("CMD_HANDLER: verb: "+verb+" tail: "+tail+"\n");
#endif

	s = find_cmd(verb);

	if(!s)
		return 0;

	cmd_hash[verb]["count"]++;

	if(!(ob = find_object(s)))
	{
		catch(s->FORCE_LOAD());
		ob = find_object(s);
	}
	if(!ob)
	{
		notify_fail("Error loading command.\n");
		return 0;
	}

	if(ob->_query_doclone())
		ob = clone_object(s);

	ret = (int)ob->_cmd(tail,thisob);

	if(ob->_query_dodest() || ob->_query_doclone())
		ob->dest_me();

	return ret;
}
////

mapping query_cmds() { return cmd_dirs; }
mapping query_hash() { return cmd_hash; }
string query_last_dir() { return last_dir; }
