#include <standard.h>
#include <cmd.h>
inherit CMD_BASE;

void setup(){

position = 1;
}



static int cmd(string str, object me) {
  object *things, spam;
  int egg;


  if(!str) {
    notify_fail("More which file(s)/object?\n");
    return 0;
  }
  if(sizeof(things = this_player(1)->wiz_present(str, this_player(1)))) {
    str = file_name(things[0]);
    sscanf(str, "%s#%d", str, egg);
    if (file_size(str) <= 0)
      str += ".c";
  }
  return this_player(1)->more_file(str);
} /* do_more() */
 
