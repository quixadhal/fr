/* this is the lord player object */

inherit "/global/wiz_file_comm";

void load_login();     /*  Cupelix.  13 Oct 1992.  */

void create() {
  ::create();
  creator = 1;
  app_creator = 1;
} /* create() */

mixed *olav() { return efun::actions_defined(this_object()); }

void move_player_to_start(string bong, int new_pl) {
  cat("doc/CREATORNEWS");
  cat("doc/LORDNEWS");
  creator = 1;
  app_creator = 1;
  ::move_player_to_start(bong, new_pl);
  if(query_invis())
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  add_action("visible", "vis");
  add_action("invisible", "invis");
  add_action("promote", "promote");
  add_action("do_demote", "demote");
  add_action("new_domain", "new_domain");
  add_action("do_heart_beat", "heart_beat");
  add_action("hide_me", "hide");
  // Test fn by Aragorn
  add_action("do_alsetting","doalign");
  load_login();
 /* Added by Asmodean cause he learned it from Aragorn */
enable_wizard();
} /* move_player_to_start() */

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

int do_heart_beat() {
  heart_beat();
  return 1;
} /* do_heart_beat() */

string short(int dark) {
  if(query_invis() == 2)
  {
    if(this_player()->query_god())
       return "**"+::short(dark)+"**";
    return 0;
  }
  if (query_verb() == "dest")
    return ""+this_object();
  if (query_invis())
    if(!this_player() || this_player()->query_creator())
      return "*"+::short(dark)+"*";
    else
      return 0;
  else
    return ::short(dark);    
  return 0;
} /* short() */

string long(string name, int dark) 
{
  if(query_invis() == 2)
  {
    if(this_player()->query_god())
       return "**"+::long(name, dark)+"**";
    return 0;
  }
  if (query_invis())
    if(!this_player() || this_player()->query_creator())
      return "*"+::long(name, dark)+"*";
    else
      return 0;
  else
    return ::long(name, dark);
  return 0;
} /* long() */

static int visible() {
  if(!query_invis()) {
    notify_fail("You are already visible.\n");
    return 0;
  }
  write("You appear.\n");
  say(query_cap_name()+" suddenly appears out of nowhere.\n", this_player());
  set_invis(0);
  return 1;
} /* visible() */

static int invisible(string str) 
{
  if(query_invis() == 2) 
  {
    notify_fail("You are already true invisible.\n");
    return 0;
  }

  if(query_invis() || str)
  {
    write("You are now truly invisible.\n");
    say(query_cap_name()+" suddenly disappears.\n", this_player());
    set_invis(2);
    return 1;
  }

  write("You disappear.\n");
  say(query_cap_name()+" suddenly disappears.\n", this_player());  
  set_invis(1);
  return 1;
} /* invisible() */

int query_creator() { return 1; }
int query_lord() { return 1; }
int query_god()
{
  if(query_name() == "god")
       return 1;
  return 0;
}

static int promote(string str) {
  if (this_player(1) != this_object())
    return 1;
  if (!str) {
    notify_fail("Usage: promote <person>\n");
    return 0;
  }
  return (int)"/secure/master"->create_creator(str);
} /* promote() */

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

void dest_me() {
  if (!this_player(1) || (this_player(1) != this_object() &&
      !this_player(1)->query_lord())) 
  {
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

string query_object_type() {
  if (this_object()->query_god())
    return "G";
if((string)this_object()->query_name()=="timion") return "D";
if((string)this_object()->query_name()=="grimbrand") return "D";
if((string)this_object()->query_name()=="taniwha") return "D";
  if ("/secure/master"->high_programmer(geteuid(this_object())))
    return "H";
  return "D";
} /* query_object_type() */

string query_gtitle() 
{ 
  if(query_female())
  {
   if(query_god())
     return "the Goddess";
   return "the Demi-Goddess"; 
  }
  else
  {
   if(query_god())
    return "the God";
   return "the Demi-God";
  }
}

