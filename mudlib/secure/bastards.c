/* Bastards.c takes care of suspension, banished sites and now also banished
 * playernames.
 * Baldrick, oct '95
 */

#include "access.h"
#include "mail.h"

static string *names;
static string def;

mapping access;  /* Site access control */

mapping suspended, banished;

int query_access(string *address, string ident);

void create() {
  names = ({ "god", "/global/lord",
             "root", "/global/player",
             "failsafe", "/global/failsafe",
             "old", "/global/player.old" });
  def = "/global/player";
  seteuid("Root");
  access = ([ ]);
  suspended = ([ ]);
  banished = ([ ]);
  restore_object(file_name(this_object()),1);
  move_object(this_object(), "/room/void");  /* Make it unclonable... */
} /* create() */

int check_access(object ob, int new) 
  {
  switch (query_access(explode(query_ip_number(ob), "."), 
                       query_ident(ob))) {
    case NO_NEW:
      if (new)
        write("Your site banned for new players.\n");
      return !new;
    case NO_ACCESS:
      write("Your site is banned to all players.\n");
      return 0;
    case ACCESS:
    default:
      return 1;
  }
} /* check_access() */

string query_player_ob(string name) 
  {
  int i;

  if (MAIL_TRACK->query_list(name)) 
    {
    write("Name is a mailing list.\n");
    return 0;
    }
  i = member_array(name, names);
  if (i != -1) 
    {
    return names[i+1];
    }
  if (banished[name])
    {
    write("This name is banished, pick a different one.\n");
    return 0;
    }
  if (suspended[name] > time()) 
    {
    write("You have been suspended until "+ctime(suspended[name])+".\n");
    return 0;
    }
  suspended = m_delete(suspended, name);
  if ("secure/master"->query_lord(name)) 
    {
    return "global/lord";
    }
  if (!check_access(previous_object(), 0))
    return 0;
  /* make sure there is a save-file */
  if(file_size("/players/" + name[0..0] + "/" + name + ".o") < 1)
    return def;
  /* I hope this is the right place to put this code in.
   * Baldrick, sept '93 */
  if ("/secure/thanes"->query_of(name))
    return "global/thane";
  if ("/secure/patrons"->query_patronage(name))
    return "global/patron";
  if (previous_object()->query_creator(name))
    return "global/creator";
  return def;
} /* query_player_ob() */

int query_prevent_shadow() { return 1; }

/*
 * Ok, acces checking stuff...
 */
mapping query_all_access() { return access + ([ ]); }

/*
 * Look up the address and find out if it is nice and floppy
 * Adress is of the format ({ "130", "95", "100", "2" })
 */
int query_access(string *address, string ident) {
  mixed rest;

  if (!pointerp(address) || sizeof(address) != 4)
    return ERROR;
  if (!(rest = access[address[0]]))
    return DEFAULT;
  address = address[1..4];
  while (sizeof(address)) {
    if (!rest[address[0]])
      if (!rest["*"])
        return DEFAULT;
      else
        rest = rest["*"];
    else
      rest = rest[address[0]];
    address = address[1..4];
  }
  if (rest[ident])
    return rest[ident];
  if (rest["*"])
    return rest["*"];
  return DEFAULT;
} /* query_access() */

static mixed add_access(mixed bing, string *address, string ident,
                        int level) {
  if (!mappingp(bing))
    bing = ([ ]);
  if (!sizeof(address)) {
    if (!level)
      bing = m_delete(bing, ident);
    else
      bing[ident] = level;
    if (!m_sizeof(bing))
      return 0;
    return bing;
  }
  bing[address[0]] = add_access(bing[address[0]], address[1..4], ident, level);
  if (!bing[address[0]])
    bing = m_delete(bing, address[0]);
  if (!m_sizeof(bing))
    return 0;
  return bing;
} /* add_access() */

int change_access(string *address, string ident, int level, string reason) {
  if (!"/secure/master"->high_programmer(geteuid(previous_object())) ||
      this_player() != this_player(1)) {
    notify_fail("Wrong euid.\n");
    return 0;
  }
  if (!pointerp(address) || sizeof(address) != 4 || !reason) {
    notify_fail("Invalid paramters.\n");
    return 0;
  }
  access = add_access(access, address, ident, level);
  if (!access)
    access = ([ ]);
save_object(file_name(this_object()),1);
  switch (level) {
    case NO_NEW :
      reason = "no new for "+reason;
      break;
    case NO_ACCESS :
      reason = "no access for "+reason;
      break;
    case ACCESS :
      reason = "access for "+reason;
      break;
    case 0 :
      reason = "deleted for "+reason;
      break;
  }
  write_file("/log/ACCESS",
             ident+"@"+implode(address, ".")+" set to "+reason+" by "+
             this_player()->query_name()+".\n");
  return 1;
} /* check_access() */

int suspend_person(string str, int tim) 
  {
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  if (file_size("/players/"+str[0..0]+"/"+str+".o") < 0)
    return 0;
  suspended[str] = time()+tim;
  save_object(file_name(this_object()),1);
  write_file("/log/SUSPEND", str+" suspended until "+ctime(time()+tim)+
                             " by "+this_player()->query_name()+".\n");
  return 1;
} /* suspend_person() */

int unsuspend_person(string str) 
  {
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  suspended = m_delete(suspended, str);
  save_object(file_name(this_object()),1);
  write_file("/log/SUSPEND", str+" unsuspended.\n");
  return 1;
} /* unsuspend_person() */

/* Banish code: 
 * Added by Baldrick for simplifying banishing.. 
 */

int banish_playername(string str, string reason)
  {
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  /*
  if (file_size("/players/"+str[0..0]+"/"+str+".o") < 0)
    return 0;
  */
  banished[str] = reason;
  save_object(file_name(this_object()),1);
  write_file("/log/BANISHED", str+" banished because of " + reason + 
                             " by "+this_player()->query_name()+".\n");
  return 1;
} /* banish player name */

int unbanish_playername(string str)
  {
  if (!"/secure/master"->query_lord(geteuid(previous_object())))
    return 0;
  banished = m_delete(banished, str);
  save_object(file_name(this_object()),1);
  write_file("/log/BANISHED", str+" unbanished.\n");
  return 1;
} /* unbanish playername */

