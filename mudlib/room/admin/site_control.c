#include "access.h"
#include "path.h"
inherit "/std/room";
#define MASTER "/secure/master"

void setup() {
  string *doms, com;
  int i;
  
  set_light(100);
  set_short("Site access control room");
  set_long("This room allows Demi-Gods and higher to easily remove "+
   "troublesome players and even creators.  You can also banish a site "+
   "from here entirely, but be absolutely certain that is approved by "+
   "a God before you do so (or face demotion).\n\n"+
"Available commands:\n"+
"sitebanish <ip> <ident> <how> <why> :  Banish a site.\n"+
"playerbanish <playername> <reason>  : Banish a name.\n"+
"access                         :  Show the current access of various sites.\n"+
"suspend <player> <time>        :  Suspend someones access for <time> hours.\n"+
"unsuspend <player>             :  Unsuspend someones access.\n");

add_exit("north", HEAVEN+"admin3","door");
  seteuid("Admin");
} /* setup() */

void init() {
  ::init();
  if ("/secure/master"->high_programmer(geteuid(previous_object())))
    add_action("do_sitebanish", "sitebanish"); /* Site banishing... */
  add_action("do_access", "access"); /* Show the current access list. */
  add_action("do_suspend", "suspend");
  add_action("do_unsuspend", "unsuspend");
  add_action("do_playerbanish", "playerbanish");
  add_action("do_unplayerbanish", "unplayerbanish");
} /* init() */

int print_access(string bit, mapping bing, int depth, int cols) {
  mixed *bits;
  int i;

  if (this_player() != this_player(1))
    return 0;
  bits = m_indices(bing);
  if (depth == 4) {
/* Do the ident printing... */
    for (i=0;i<sizeof(bits);i++)
      switch (bing[bits[i]]) {
        case NO_NEW :
          printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
                             " set to no new characters.\n");
          break;
        case NO_ACCESS :
          printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
                             " set to no characters.\n");
          break;
        case ACCESS :
          printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
                             " set to normal access.\n");
          break;
    }
    return 1;
  }
  for (i=0;i<sizeof(bits);i++)
    print_access(bit+"."+bits[i], bing[bits[i]], depth+1, cols);
  return 1;
} /* print_access() */

int do_access() {
  mixed bing;

  if (this_player() != this_player(1))
    return 0;
  bing = (mixed)"/secure/bastards"->query_all_access();
  if (!m_sizeof(bing)) {
    notify_fail("No access control defined.\n");
    return 0;
  }

  print_access("", bing, 0, (int)this_player()->query_cols());
  return 1;
} /* do_access() */

int do_sitebanish(string str) 
  {
  string ip, ident, reason;
  int level;

  if (this_player() != this_player(1))
    return 0;
/*  if (!"/secure/master"->high_programmer(geteuid(previous_object())))
  {
    notify_fail("You need to be Demi-God or higher to banish.\n");
    return 0;
  }*/
  notify_fail("Syntax: banish <ip number> <ident> <severity> <reason>\n"+
              "        <severity> :  0 delete ident,   1 normal access,\n"+
              "                      2 no new players, 3 No access.\n");
  if (!str)
    return 0;
  if (sscanf(str, "%s %s %d %s", ip, ident, level, reason) != 4)
    return 0;

  if (!"/secure/bastards"->change_access(explode(ip, "."), ident, level,
                                         reason))
    return 0;
  write("Access permisions changed.\n");
  return 1;
} /* do_banish() */

int do_suspend(string str) 
  {
  string name;
  int tim;

  if (this_player() != this_player(1))
    return 0;
  if (!"/secure/master"->query_lord(geteuid(this_player())))
  {
    notify_fail("You need to be a Demi-God or higher to suspend someone.\n");
    return 0;
  }
  if (sscanf(str, "%s %d", name, tim) != 2) {
    notify_fail("Syntax: suspend <name> <time>\nWhere time is in hours.\n");
    return 0;
  }
  notify_fail("We failed!\n");
  if (!"/secure/bastards"->suspend_person(name, tim*60*60))
    return 0;
  write(name+" suspended until "+ctime(time()+tim*60*60)+"\n");
  return 1;
} /* do_suspend() */

int do_unsuspend(string str) {
  if (this_player() != this_player(1))
    return 0;
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  notify_fail("We failed!\n");
  if (!"/secure/bastards"->unsuspend_person(str))
    return 0;
  write(str+" unsuspended.\n");
  return 1;
} /* do_unsuspend() */

/* Playerbanishing.. 
 * Added by Baldrick oct '94
 */

int do_playerbanish(string str) 
  {
  string name, reason;

  if (this_player() != this_player(1))
    return 0;
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
  {
    notify_fail("You need to be a Demi-God or higher to banish someone.\n");
    return 0;
  }
  if (sscanf(str, "%s %s", name, reason) != 2) 
    {
    notify_fail("Syntax: playerbanish <name> <reason>\n");
    return 0;
    }
  /* ???? why? */
  notify_fail("We failed!\n");
  if (!"/secure/bastards"->banish_playername(name, reason))
    return 0;
  write(name+" banished because of "+reason+".\n");
  return 1;
} /* do_playerbanish */

int do_unplayerbanish(string str) 
  {
  if (this_player() != this_player(1))
    return 0;
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  notify_fail("We failed!\n");
  if (!"/secure/bastards"->unbanish_playername(str))
    return 0;
  write(str+" unbanished.\n");
  return 1;
} /* do_unsuspend() */
