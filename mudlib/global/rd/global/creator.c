/* this is the creator player object */
inherit "/global/wiz_file_comm";

#define MAX_IRANK 5
string dtitle, mast, *domains;
 
#define NO_SWAP
// #define ECHO_ALLOWED
 
#ifndef NO_SWAP
static string omsgin, omsgout, ommsgin, ommsgout;
static int oxp, omax_deaths=9, odeaths;
static mixed *oskills;
static mapping oprop;
static mapping ospells;
 
int look_me(string str) {
  if (!str && environment())
    write(file_name(environment()) + "\n");
  return ::look_me(str);
} /* look_me() */
 
int do_glance(string str) {
  if (!str && environment())
    write(file_name(environment()) + "\n");
  return ::do_glance(str);
} /* do_glance() */
 
/* This function is used to try to prevent people logged in as a creator from
 * toying with the bits of them that may be useful as a player.  I am sure
 * there are still holes in it, but they can be removed gradually as creators
 * discover them for you.
 */
static void swap_entryexit() {
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
/*
  tprop = map_prop;
  map_prop = oprop;
  oprop = tprop;
 */
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
 
void move_player_to_start(string bong, int new_pl, string c_name) {
  string temp;
 
  if(!sscanf(file_name(previous_object()), "/secure/login#%s", temp))
    return 0;
  cat("doc/CREATORNEWS");
  ::move_player_to_start(bong, new_pl, c_name);
  if(query_invis())
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  if (channels["cre"] == "off" || !channels["cre"])
    message("==| Cre Channel is OFF |==\n","",this_object());
  swap_entryexit();
#ifndef NO_SWAP
  xp = oxp;
#endif
  add_action("visible", "vis");
  add_action("invisible", "invis");
  enable_wizard();
}
 
string short(int dark) {
  if (query_invis())
    if(!this_player() || this_player()->query_creator())
      return ::short(dark) + " (invis)";
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
say(this_player()->query_cap_name() + " suddenly appears from nowhere.\n");
  invis = 0;
  return 1;
}
 
int invisible(string str)
{
/*
  if(query_invis()) {
    notify_fail("You are already invisible.\n");
    return 0;
  }
*/
  if(str && str!="1")
  {
    notify_fail("Invis what?\n");
    return 0;
  }
  if (!query_invis()) {
    write("You disappear.\n");
    say(this_player()->query_cap_name() + " suddenly disappears.\n");
  }
  switch(str)
  {
  case "1":
      invis = -1;
      break;
  default:
    invis = 1;
    break;
  }
  write(query_invis_string()+".\n");
  return 1;
}
 
//Modified by Parallax (11/4/94) to allow echo and echoto for creator 
//ranks 4 and 5
 
#ifndef ECHO_ALLOWED
int do_echo(string str) {
  if(this_player()->query_rank() < 4) 
  {
  write("You are a creator now.\n");
  return 1;
  }
}
 
int do_echo_to(string str) {
  if(this_player()->query_rank() < 4) 
  {
  write("You are a creator now.\n");
  return 1;
  }
}
 
int do_echo_all(string str) {
  write("You are a creator now.\n");
  return 1;
}
 
int do_emote_all(string str)
{
write("You are a creator now.\n");
return 1;
}
#endif
 
 
void save_me() {
  swap_entryexit();
  ::save_me();
  swap_entryexit();
}
 
int query_creator() { return 1; }
int query_app_creator() { return app_creator; }
int query_creator_playing() { return 0; }
 
string query_object_type() {
  if((int)this_object()->query_rank() == 0){
     return "I";
  }
  if((int)this_object()->query_rank() == 1){
    return "I1";
  }
  if((int)this_object()->query_rank() == 2){
     return "I2";
  }
  if((int)this_object()->query_rank() == 3){
     return "I3";
  }
  if((int)this_object()->query_rank() == 4){
     return "I4";
  }
  if((int)this_object()->query_rank() == MAX_IRANK){
     return "I5";
  }
}
 
/* query_rank added for ranks by Kelaronus 7/24/94 */
int query_rank(){
  return rank;
}

/* do_advance added for ranks by Kelaronus 7/24/94 */
do_advance(){
  if((int)this_object()->query_rank() < 3){
    if(this_player()->query_lord() == 1){
      rank = rank + 1;
      message("You have been promoted to rank "+this_object()->query_rank()+
              " by "+this_player()->query_cap_name()+".\n",
               "", this_object());
      message(this_object()->query_cap_name()+" promoted to rank "+
              this_object()->query_rank()+".\n", "", this_player());
      log_file("RANKS", sprintf("Promoted "+this_object()->query_cap_name()+
      " to the rank of "+this_object()->query_rank()+
      ": %15-s %s\n", this_player()->query_cap_name(), ctime(time())));
      return rank;
    }
    else {
      return 0;
    }
  }
  else {
    if("/secure/master"->high_programmer(geteuid(this_player()))){
      if((int)this_object()->query_rank() >= MAX_IRANK){
        notify_fail("This immortal is the highest rank already.\n");
        return 0;
      }
      else {
        rank = rank + 1;
        message("You have been promoted to rank "+this_object()->query_rank()+
                " by "+this_player()->query_cap_name()+".\n",
                "", this_object());
        message(this_object()->query_cap_name()+" promoted to rank "+
                this_object()->query_rank()+".\n", "", this_player());
        log_file("RANKS", sprintf("Promoted "+this_object()->query_cap_name()+
        " to the rank of "+this_object()->query_rank()+
        ": %15-s %s\n", this_player()->query_cap_name(), ctime(time())));
        return rank;
      }
    }
    else {
      return 0;
    }
  }
}
 
/* do_reduce added for ranks by Kelaronus 7/24/94 */
do_reduce(){
   if("/secure/master"->high_programmer(geteuid(this_player()))){
     if((int)this_object()->query_rank() == 0){
        notify_fail("This immortal is the lowest rank already.\n");
        return 0;
        }
      else {
        rank = rank - 1;
       message("You have been demoted to rank "+this_object()->query_rank()+
               " by "+this_player()->query_cap_name()+".\n",
               "", this_object());
            message(this_object()->query_cap_name()+" demoted to rank "+
                    this_object()->query_rank()+".\n", "", this_player());
        log_file("RANKS", sprintf("Demoted "+this_object()->query_cap_name()+
        " to the rank of "+this_object()->query_rank()+
        ": %15-s %s\n", this_player()->query_cap_name(), ctime(time())));
        return rank;
        }
    }
}
 
/* query_gtitle modified for ranks by Kelaronus 7/24/94 */
string query_gtitle()
{
  int i;

  domains = get_dir("/d/");
  for(i=0; i<sizeof(domains); i++) {
    if(domains[i] != "chaos"){
      mast = "/d/" + domains[i] + "/master";
      if(mast->query_member(geteuid(this_object()))){
	if(domains[i] == "omiq"){
	  dtitle = "High Adventure";
	}
          else if (domains[i] == "trams") dtitle = "Life";
	else {
	  dtitle = capitalize(domains[i]);
	}
        if((int)this_object()->query_rank() < 1){
	  return "the Immortal, Novice of "+dtitle;
	}
	if((int)this_object()->query_rank() == 1){
	  return "the Immortal, Noble of "+dtitle;
	}
        if((int)this_object()->query_rank() == 2){
	  return "the Immortal, Guardian of "+dtitle;
	}
	if((int)this_object()->query_rank() == 3){
	  return "the Immortal, Warder of "+dtitle;
	}
	if((int)this_object()->query_rank() == 4){
	  return "the Immortal, Keeper of "+dtitle;
	}
	if((int)this_object()->query_rank() == 5){
	  return "the Immortal, UnderLord of "+dtitle;
	}
      }
    }
  }
  if((int)this_object()->query_rank() == 0){
    return "the Immortal, Renegade Novice";
  }
  if((int)this_object()->query_rank() == 1){
    return "the Immortal, Renegade Noble";
  }
  if((int)this_object()->query_rank() == 2){
    return "the Immortal, Renegade Guardian";
  }
  if((int)this_object()->query_rank() == 3){
    return "the Immortal, Renegade Warder";
  }
  if((int)this_object()->query_rank() == 4){
    return "the Immortal, Renegade Keeper";
  }
  if((int)this_object()->query_rank() == 5){
    return "the Immortal, Renegade UnderLord";
  }
}
