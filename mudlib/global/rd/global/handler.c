#include "login_handler.h";
#define HANDLER "/secure/login";
status review(mixed show_defaults)
{
return (status) HANDLER->review(this_object(), show_defaults);
}
status set(string param)
{
string name,value;
if(!param)
{
notify_fail("Usage : set <whatever> <message>\n");
return 0;
}
sscanf(param, "%s %s", name, value);
return set_env(name, value);
}
