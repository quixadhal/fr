// cmd handler test ob

#include <aurora/standard.h>
#include <aurora/cmd.h>

inherit "std/object";

void setup()
{
	set_name("handler");
	add_adjective("command");
	set_short("Command handler");
	set_long("Command handler.. handles commands :)\n");

	set_weight(1);
	set_value(1);
}

void init()
{
	::init();

	add_action("do_cmd", "*", -10000);
}

int do_cmd(string tail)
{
	string verb, t;

	sscanf(tail, "%s %s", verb, t);
	if(!verb)
		verb = tail;

	return (int)CMD_HANDLER->cmd(verb, t);
}
