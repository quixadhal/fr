/*
 * master.c
 * 1998-05 hacking it a bit, removing add_(high)_lord and 
 * the positions mapping. Baldrick.
 */

#define ROOT "Root"
#define BACKBONE "Root"

#include "/include/log.h"

#define HIGHLords (["baldrick":1, ROOT:1, ])

#ifdef VERSION
#define version() VERSION
#endif

#define READ_MASK 1
#define WRITE_MASK 2
#define GRANT_MASK 4

#define LORD 1
#define HIGH_LORD 2
/*
 * nosave inherit "std/simul_efun";
 */

string *preload;
string *call_out_preload;
string *gods;
mapping permissions;
nosave mapping HighLords;
nosave int done;
nosave mapping checked_master;
nosave mapping snoop_list;

void create() {
  permissions = ([ ]);
  gods = ({});
  checked_master = ([ ]);
  snoop_list = ([ ]);
  HighLords = HIGHLords;
  call_out("load_object", 0);
} /* create() */


void create2()
  {
  gods = "/secure/gods.c"->query_gods() + 
         "/secure/lords.c"->query_lords();
  }

/*
 * This function is called every time a player connects.
 * input_to() can't be called from here.
 */
object connect() {
  object ob;
  if (!find_object("/secure/login")) {
      log_file("REBOOT", "Mud rebooted at "+ctime(time())+"["+time()+"]"+"\n");
  }
 
  printf("LPmud version: "+version()+".\n" + MUDLIB_VERSION + "\n");
  ob = clone_object("/secure/login");
  printf("\n");
  return ob;
} /* connet() */

int high_programmer(string str) {

  if (str == ROOT) return 1;
  if (str == "Admin") return 1;
  /* This has to be a hack.. Baldrick, */
  if ( member_array(str, gods) != -1 )
    return 1;
  if ( !"/secure/mudlibber"->query_mudlibber(str) ) 
    return 0;
   else 
    return 1;
} /* high_programmer() */

int query_high_programmer(string str) {
  return high_programmer(str);
}

int query_lord(string str) {
  if (str == ROOT) return 1;
  if ( member_array(str, gods) >=0 )
    return 1;
   else 
    return 0;
} /* query_lord() */

int query_only_lord(string str) {
  if ( member_array(str, gods) >=0 )
    return 1;
   else 
    return 0;
} /* query_only_lord() */

int query_high_lord(string str) {
  return query_only_lord(str);
}

string *query_lords() {
  return gods;
} /* query_lords() */

string *high_programmers() {
  return gods + "/secure/alchemists.c"->query_alchemists();
} /* high_programmers() */

int check_permission(string euid, string *path, int mask);

int valid_load(string path, mixed euid, string func) {return 1;}

string get_root_uid() { return ROOT; }
string get_bb_uid() { return BACKBONE; }

string *define_include_dirs() {
  return ({ "/include/%s" });
} /* define_include_dirs() */

int valid_trace() { return 1; }

void shut(int min) {
  "/obj/shut"->shut(min);
} /* shut() */

void remove_checked_master(string name) {
  map_delete(checked_master, name);
} /* remove_checked_master() */

// Wonderflug 96, Secure this baby.
mapping query_checked_master() { return checked_master + ([ ]); }

#include "/secure/master/permission.c"
#include "/secure/master/crash.c"
/* This should probably be here, trying without. Baldrick, jan '97
trace();
*/
#include "/secure/master/create_dom_creator.c"
#include "/secure/master/create_me.c"
#include "/secure/master/creator_file.c"
#include "/secure/master/dest_env.c"
#include "/secure/master/ed_stuff.c"
#include "/secure/master/logging.c"
#include "/secure/master/error_handler.c"
#include "/secure/master/parse_command.c"
#include "/secure/master/preload.c"
#include "/secure/master/query_pl_level.c"
#include "/secure/master/retire.c"
#include "/secure/master/simul_efun.c"
#include "/secure/master/snoop.c"
#include "/secure/master/valid_exec.c"
#include "/secure/master/valid_hide.c"
#include "/secure/master/valid_ident.c"
#include "/secure/master/valid_link.c"
#include "/secure/master/valid_override.c"
#include "/secure/master/valid_read.c"
#include "/secure/master/valid_seteuid.c"
#include "/secure/master/valid_shadow.c"
#include "/secure/master/valid_socket.c"
#include "/secure/master/valid_write.c"
#include "/secure/master/virtual_objects.c"
#include "/secure/master/valid_save_binary.c"
