// /global/cmd/cmds/cmd.c (confusing hey? :)
// Gives info on command handler, commands etc :)

#include <standard.h>
#include <cmd.h>

inherit CMD_BASE;

static mapping cmd_dirs, cmd_hash;
static string last_dir, file;

void setup()
{
  position = CREATOR_CMD;
}

string query_usage()
{
  return "command";
}

string query_short_help()
{
  return "Find information on a specified command";
}

static int cmd(string tail, object me)
{
  string str, *s;

  if(!tail || tail=="")
  {
    notify_fail("Get information on what command?\n");
    return 0;
  }

  str = "";
  s = ({ });

  file = CMD_HANDLER->find_cmd(tail);

  if(!file || file=="")
  {
    write("Command '"+tail+"' was not found.\n");
    return 1;
  }

  cmd_dirs = (mapping)CMD_HANDLER->query_cmds();
  cmd_hash = (mapping)CMD_HANDLER->query_hash();
  last_dir = (string)CMD_HANDLER->query_last_dir();

  s += ({ "Command: "+tail });
  s += ({ "File: "+file });
  s += ({ "Directory: "+last_dir });
  s += ({ "Command type: "+cmd_dirs[last_dir] });
  s += ({ "Access count: "+cmd_hash[tail]["count"] });

  write("Command '"+tail+"' was found in: "+file+"\n"+
    "Directory: "+last_dir+"\t\t"+cmd_dirs[last_dir]+" command\n"+
    "Access count: "+cmd_hash[tail]["count"]+"\n");

  return 1;
}
