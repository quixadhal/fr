// /global/cmd/cmd_handler.c  -- Object based command handler

#include <standard.h>
#include <cmd.h>

int cmd_make_hash(int i);

#ifdef CMD_AURORA
static mapping cmd_dirs =
([
	"/global/player/cmds/":		({0,		"Player"}),
	"/global/creator/cmds/":	({CREATOR,	"Creator"}),
	"/global/lord/cmds/":		({LORD,		"Lord"}),
	"/net/cmds/":			({0,		"InterMUD network"}),
	"/global/cmd/cmds/":		({0,		"Command handler"}),
]);
#endif
#ifdef CMD_FR
static mapping cmd_dirs =
([
	"/global/player/cmds/":		({0,		"Player"}),
	"/global/creator/cmds/":    	({CREATOR_CMD,	"Creator"}),
	"/global/lord/cmds/":		({LORD_CMD,	"Lord"}),
	"/global/demi/cmds/":		({HIGH_LORD_CMD,"Demi-God"}),
	"/global/god/cmds/":		({HIGH_LORD_CMD,"God"}),
	"/net/cmds/":			({0,		"InterMUD network"}),
	"/global/cmd/cmds/":		({0,		"Command handler"}),
]);
#endif

static mapping cmd_hash = ([ ]);  	// For commands and their objects
static mapping cmd_aliases = ([ ]);	// For command aliases
static string last_dir = "";      	// Last directory a command was found
static string current_verb;		// Used by query_verb() efun

void create()
{
	seteuid(getuid());
	current_verb = 0;

	cmd_make_hash(0);
}

void dest_me()
{
	destruct(TO);
}

int clean_up()
{
	return 0;
}

// The simul for query_verb() queries this if efun::query_verb() == 0
string query_current_verb() { return current_verb; }

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

#ifdef CMD_AURORA
int cmd(string verb, string tail)
#endif
#ifdef CMD_FR
int cmd(string verb, string tail, object thisob)
#endif
{
	object ob;
	string s, euid;
	int ret;

#ifdef _CMD_DEBUG
	write("CMD_HANDLER: verb: "+verb+" tail: "+tail+"\n");
#endif

	seteuid("Root");
#ifdef CMD_AURORA
	euid = geteuid(TP);
#endif
#ifdef CMD_FR
	euid = geteuid(thisob);
#endif

	s = cmd_aliases[verb];
	if(stringp(s) && s!=0)
		verb = s;

	s = find_cmd(verb);

	if(!s)
		return 0;

	// Check their position now...
	switch(cmd_dirs[last_dir][0])
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
		if(!TP->query_creator())
			return 0;
		break;
	}
#endif
#ifdef CMD_FR
	{
	case HIGH_LORD_CMD:
               if(!MASTER->query_highprogrammer(euid))
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

	seteuid("CMD");
	current_verb = verb;
#ifdef CMD_AURORA
	ret = (int)ob->_cmd(tail);
#endif
#ifdef CMD_FR
	ret = (int)ob->_cmd(tail, thisob);
#endif
	current_verb = 0;

	if(ob->_query_dodest() || ob->_query_doclone())
		ob->dest_me();

	return ret;
}

int cmd_make_hash(int verbose)
{
	/* This goes and finds _all_ the valid commands in the listed
	 * paths, and also works out the command aliases from the 
	 * _CMD_ALIASES file in each directory.
	 */
	string *paths, s, *a;
        string *files;
	int i, j, k, l, count;

	seteuid("Root");
	cmd_hash = cmd_aliases = ([ ]);
	count = 0;

	paths = keys(cmd_dirs);

	for(i=0; i < sizeof(paths); i++)
	{
//		if(verbose) 
//  	 		log_file("CMD","Scanning directory: "+paths[i]+"\n");
                files = get_dir(paths[i]+"*.c");
//                if(verbose)
//			log_file("CMD", files);        
		for(j=0; j<sizeof(files); j++)
		{
			a = explode(files[j], ".");
                        s=implode(a[0..sizeof(a)-1], ".");
			if(verbose) write("    Command: "+s+"\n");
			cmd_hash[s] = 
			([
				"file":		paths[i]+s,
				"count":	0,
				"dir":		paths[i],
			]);
			count++;
		}

		s = read_file(paths[i]+"/_CMD_ALIASES");
		if(stringp(s) && s!=0 && s!="")
		{
			a = explode(s, "\n");
			for(j=0; j<sizeof(a); j++)
			{
				k = 0;
				files = explode(replace(a[j],"\t", " "), " ");
				if(sizeof(files) && files[0] == "alias") k++;
				if(sizeof(files) > k)
				{
					for(l=k+1; l<sizeof(files); l++)
					if(files[l] != files[k])
					{
						if(verbose) write("    Alias "+
							files[l]+" to "+
							files[k]+"\n");
						cmd_aliases[files[l]]= files[k];
					}
				}
			}
		}
	}
	seteuid("CMD");
	return count;
}

////

mapping query_cmds() { return cmd_dirs; }
mapping query_hash() { return cmd_hash; }
string query_last_dir() { return last_dir; }
mapping query_aliases() { return cmd_aliases; }
string query_alias(string verb) { return cmd_aliases[verb]; }
