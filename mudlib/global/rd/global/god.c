/* this is the lord player object */

inherit "/global/wiz_file_comm";

string *allowed;

void load_login();

void create() {
  ::create();
  creator = 1;
  app_creator = 1;
  allowed = ({ });
} /* create() */

void move_player_to_start(string bong, int bing, string c_name) {
  cat("doc/CREATORNEWS");
  cat("doc/LORDNEWS");
  creator = 1;
  app_creator = 1;
  ::move_player_to_start(bong, bing, c_name);
  if(query_invis())
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  if (channels["cre"] == "off" || !channels["cre"])
    message("==| Cre Channel is OFF |==\n","",this_object());
  if (channels["lord"] == "off" || !channels["lord"])
    message("==| Lord Channel is OFF |==\n","",this_object());
  if (channels["demi"] == "off" || !channels["demi"])
    message("==| Demi Channel if OFF |==\n","",this_object());
  if (channels["god"] == "off" || !channels["god"])
    message("==| God Channel if OFF |==\n","",this_object());
  add_action("visible", "vis");
  add_action("invisible", "invis");
  add_action("promote", "promote");
  add_action("do_demote", "demote");
  add_action("new_domain", "new_domain");
  add_action("do_heart_beat", "heart_beat");
  add_action("do_allow", "allow");
  add_action("do_disallow", "disallow");
  add_action("codechange","codechange");

load_login();
  /* Added by Aragorn. */
  enable_wizard();
   add_action("olavcheck","olavcheck");
 /* added by Kelaronus */
  add_action("rpromote","rpromote");
  add_action("rdemote", "rdemote");

} /* move_player_to_start() */

void load_login(){
string *strs;
int n;
if(read_file("/w/"+name+"/.login")){
strs=explode(read_file("/w/"+name+"/.login"),"\n");
for(n=0;n<sizeof(strs);n++)
command(strs[n]);
}
}

int codechange(string str) {
   if (!str || str=="") return notify_fail("Usage : codechange <text>\n");
   log_file("Codechange",ctime(time())+" : "+
                  (string)this_player()->query_name()+"\n"+str+"\n");
   write("Ok.\n");
   return 1;
}

int do_heart_beat() {
  heart_beat();
  return 1;
} /* do_heart_beat() */

string short(int dark) {
  if (query_invis() == 2) return 0;
  if (query_verb() == "dest")
    return ""+this_object();
  if (query_invis())
    if(!this_player() || this_player()->query_creator())
      return ::short(dark) + " (invis)";
    else
      return 0;
  else
    return ::short(dark);    
  return 0;
} /* short() */

string long(string name, int dark) {
  if(query_invis())
    return 0;
  else
    return ::long(name, dark);
} /* long() */

static int visible() {
  if(!query_invis()) {
    notify_fail("You are already visible.\n");
    return 0;
  }
  write("You appear.\n");
  say(this_player()->query_cap_name() + " suddenly appears from nowhere.\n");
  invis = 0;
  return 1;
} /* visible() */

static int invisible(string str) {
/*
  if(query_invis()) {
    notify_fail("You are already invisible.\n");
    return 0;
  }
*/
  if (!query_invis()) {
    write("You disappear.\n");
    say(this_player()->query_cap_name() + " suddenly disappears.\n");
  }
  switch(str)
  {
  case "2":
    invis = 2;
    break;
  case "1":
    invis = -1;
    break;
  default:
    invis = 1;
    break;
  }
  write((string)this_object()->query_invis_string()+".\n");
  return 1;
} /* invisible() */

int query_hidden(){return invis;}

int query_creator() { return 1; }

int query_lord() { return 1; }

nomask int query_god() { return 1; }

int high_programmer(){return 1;}

int god(){return 1;}

static int promote(string str) {
if(this_player() != this_object())
    return 1;
  if (!str) {
    notify_fail("Usage: promote <person>\n");
    return 0;
  }
  return (int)"/secure/master"->create_creator(str);
} /* promote() */

/* rpromote added for ranks by Kelaronus 7/24/94 */
int rpromote(string str){
  object targ;
  if(!str || str==""){
    notify_fail("Usage : rpromote <immortal>\n");
    return 0;
   }
  targ = find_player(str);
  if(!targ){
    write("That Immortal isn't around right now.\n");
    return 1;
   }
  targ->do_advance();
  return 1;
}

/* rdemote added for ranks by Kelaronus 7/24/94 */
int rdemote(string str){
  object targ;
  if(!str || str == ""){
    notify_fail("Usage : rdemote <immortal>\n");
    return 0;
   }
  targ = find_player(str);
  if(!targ){
    write("That Immortal isn't around right now.\n");
    return 1;
   }
  targ->do_reduce();
  return 1;
}

static int do_demote(string str) {
  if (this_player(1) != this_player())
    return 0;
  if (!str) {
    notify_fail("Syntax: demote <person> <reason>\n");
    return 0;
  }
  return (int)"/secure/master"->demote_creator(str);
} /* do_demote() */

static int new_domain(string str) {
  string s1, s2;
  if (this_player(1) != this_object())
    return 1;
  notify_fail("Usage: new_domain <domain> <lord>\n");
  if (!str)
    return 0;
  if (sscanf(str, "%s %s", s1, s2) != 2)
    return 0;
  return (int)"/secure/master"->create_domain(s1, s2);
} /* new_domain() */

int query_creator_playing() { return 0; }

/*
void dest_me() {
  if (!this_player(1) || (this_player(1) != this_object() &&
      !this_player(1)->query_lord())) {
    write("You can't do that!\n");
    return ;
  }
  ::dest_me();
} /* dest_me() */

string *parse_command_id_list() {
  if (query_invis() == 2)
    return ({ });
  return ::parse_command_id_list();
} /* parse_command_id_list() */

string *parse_command_adjectiv_id_list() {
  if (query_invis() == 2)
    return ({ });
  return ::parse_command_adjectiv_id_list();
} /* parse_command_id_list() */

string *parse_command_plural_id_list() {
  if (query_invis() == 2)
    return ({ });
  return ::parse_command_plural_id_list();
} /* parse_command_id_list() */

/* this shouldn't be needed. Makes a few extra if's Baldrick jan '94. */

string query_object_type() {
if("/secure/master"->god(geteuid(this_object())))
    return "G";
  if ("/secure/master"->high_programmer(geteuid(this_object())))
return "D";
return "H";
} /* query_object_type() */

string query_gtitle(){
if ("/secure/master"->god(geteuid(this_object())))
{
   if((string)this_object()->query_name()=="ishamael")
    return "the God of Sorcery and Storm";
   if((string)this_object()->query_name()=="aurora")
    return "the Goddess of the Dawn";
   if((string)this_object()->query_name()=="dyraen")
    return "the God of Players";
 if((int)this_object()->query_gender() == 2)
  return "the Goddess";    
 return "the God";
}else{
 if ((string)this_object()->query_name()=="asmodean")
   return "the Demi-God of the Universal Truth";

 if((int)this_object()->query_gender() == 2)
   return "the Demi-Goddess";
  return "the Demi-God";
}
}
void event_enter(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly enters the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly enters your inventory",
                   "enter");
  }
 ::event_enter(me, s1, from);
} /* event_enter() */

void event_exit(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly exits the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly exits your inventory",
                   "enter");
  }
  ::event_exit(me, s1, from);
} /* event_exit() */

static int do_allow(string name) {
  string *names;
  int i;

  if (!name) {
    write("Currently allowed people are: "+implode(allowed, ", ")+"\n");
    write("Syntax: allow <name> [name] ...\n");
    return 1;
  }
  names = explode(name, " ");
  for (i=0;i<sizeof(names);i++)
    if (!"/secure/login"->test_user(names[i])) {
      write("User "+names[i]+" does not exist.\n");
      names = delete(names, i, 1);
      i--;
    }
  if (!sizeof(names)) {
    write("No one is added.\n");
  } else
    write(implode(names, ", ")+" have been added to the allowed array.\n");
  allowed += names;
  return 1;
} /* do_allow() */

static int do_disallow(string name) {
  string *names;
  int i;

  if (!name) {
    notify_fail("Syntax: disallow <name> [name] ...\n");
    return 0;
  }
  names = explode(name, " ");
  for (i=0;i<sizeof(names);i++)
    if (member_array(names[i], allowed) == -1) {
      write("User "+names[i]+" not in the allowed array, how can you "+
            "remove them?\n");
      names = delete(names, i, 1);
      i--;
    }
  if (!sizeof(names))
    write("No one removed from the array.\n");
  else
    write(implode(names, ", ")+" has been removed from the array thingy.\n");
  allowed = allowed - names;
  return 1;
} /* do_disallow() */

string *query_allowed() { return allowed; }

int query_allow(string name) {
  return member_array(name,allowed) == -1?0:1;
} /* query_allow() */
 
void dest_me() {
  if (this_player() && this_player() != this_object()) {
    if (!interactive(this_object()))
      event(users(), "inform", this_player()->query_cap_name()+
            " dests "+(string)file_name(this_object()), "dest");
    else
      event(users(), "inform", this_player()->query_cap_name()+
            " dests "+this_object()->query_cap_name(), "dest");
    tell_object(this_object(), "You were dested by "+
                     this_player()->query_cap_name()+".\n");
  }
  ::dest_me();
} /* dest_me() */
