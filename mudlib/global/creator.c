/* this is the creator player object. 
 * Baldrick.
 */

inherit "/global/wiz_file_comm";

#define NO_SWAP
#define ECHO_ALLOWED

void load_login();
#ifndef NO_SWAP

 // string o_type, g_title;

static string omsgin, omsgout, ommsgin, ommsgout;
static int oxp, omax_deaths=18, odeaths;
static mixed *oskills;
static mapping oprop;
static mapping ospells;

/* I wonder if I don't use static in these definitions, will it be saved in
 * player.o ? Baldrick. 
 * Yup, I'll learn.. :=)*/

enable_wizard();

int look_me(string str) {
  if (!str && environment())
    write(virtual_file_name(environment()) + "\n");
  return ::look_me(str);
} /* look_me() */

int do_glance(string str) {
  if (!str && environment())
    write(virtual_file_name(environment()) + "\n");
  return ::do_glance(str);
} /* do_glance() */

static void swap_entryexit() 
{
  string tmin, tmout, tmmin, tmmout;
  int txp, tdeaths, tmax_deaths;
  mixed tskills, tprop, tspells;

  tmin = msgin;
  tmout = msgout;
  tmmin = mmsgin;
  tmmout = mmsgout;
  msgin = omsgin;
  msgout = omsgout;
  mmsgin = ommsgin;
  mmsgout = ommsgout;
  omsgin = tmin;
  omsgout = tmout;
  ommsgin = tmmin;
  ommsgout = tmmout;
  txp = xp;
  xp = oxp;
  oxp = txp;
  tskills = skills;
  skills = oskills;
  oskills = tskills;
  tspells = spells;
  spells = ospells;
  ospells = tspells;
  tdeaths = deaths;
  deaths = odeaths;
  odeaths = tdeaths;
  tmax_deaths = max_deaths;
  max_deaths = omax_deaths;
  omax_deaths = tmax_deaths;
}
#else
void swap_entryexit() {
}
#endif


void move_player_to_start(string bong, int new_pl) {
  string temp;

  if(!sscanf(file_name(previous_object()), "/secure/login#%s", temp))
    return 0;
  cat("doc/CREATORNEWS");
  ::move_player_to_start(bong, new_pl);
  if(query_invis())
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  swap_entryexit();
#ifndef NO_SWAP
  xp = oxp;
#endif
  add_action("visible", "vis");
  add_action("invisible", "invis");
  load_login();
   /* Added by Asmodean cause Aragorn taught him how :) */
   enable_wizard();
}

void load_login() 
{
   string f, g;
   int i;
   while (f=read_file("/w/"+name+"/.login", i)) 
   {
      if (sscanf(f, "%s\n", g) == 1)
         command(g);
      i++;
   }
}

string short(int dark) {
  if (query_invis())
    if(!this_player() || this_player()->query_creator())
      return "*"+::short(dark)+"*";
    else
      return 0;
  else
    return ::short(dark);
}

int visible() {
  if(!query_invis()) {
    notify_fail("You are already visible.\n");
    return 0;
  }
  write("You appear.\n");
  say(query_cap_name()+" suddenly appears.\n", this_player());
  set_invis(0);
  return 1;
}

int invisible() {
  if(query_invis()) {
    notify_fail("You are already invisible.\n");
    return 0;
  }
  write("You disappear.\n");
  say(query_cap_name()+" suddenly disappears.\n", this_player());
  set_invis(1);
  return 1;
}

void save_me() {
  swap_entryexit();
  ::save_me();
  swap_entryexit();
}

int query_creator() { return 1; }
nomask int query_lord() { return 0; }
// people like to shadow this to snoop the demi channel.... Hpj
int query_app_creator() { return app_creator; }
int query_creator_playing() { return 0; }

string query_gtitle() 
{ 
  return "the Builder"; 
}

string query_object_type() {
  return "B";
}  /* query_object_type() */

