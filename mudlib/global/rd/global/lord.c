inherit "/global/wiz_file_comm";
#define MAX_HRANK 2
#define FORGER (["maui":1,"morgoth":1,"laggard":1,"belal":1,"moredhel":1])
string *allowed, *members, *domains, mast, dtitle;

void load_login();

void create() {
  ::create();
  creator = 1;
  app_creator = 1;
  allowed = ({ });
} /* create() */

mixed *my_commands() { return "NA"; /* efun::actions_defined(this_object()); */ }

void move_player_to_start(string bong, int bing, string c_name) {
  cat("doc/CREATORNEWS");
  creator = 1;
  app_creator = 1;
  ::move_player_to_start(bong, bing, c_name);
  if(query_invis())
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  if (channels["cre"] == "off" || !channels["cre"])
    message("==| Cre Channel is OFF |==\n","",this_object());
  if (channels["lord"] == "off" || !channels["lord"])
    message("==| Lord Channel is OFF |==\n","",this_object());
  if ("/secure/master"->high_programmer(geteuid(this_object())))
    if (channels["demi"] == "off" || !channels["demi"])
      message("==| Demi Channel if OFF |==\n","",this_object());
  add_action("visible", "vis");
  add_action("invisible", "invis");
  add_action("promote", "promote");
  add_action("do_demote", "demote");
  add_action("new_domain", "new_domain");
  add_action("do_heart_beat", "heart_beat");
  add_action("do_allow", "allow");
  add_action("do_disallow", "disallow");
  add_action("codechange","codechange");
  /* rpromote and rdemote added for ranks by Kelaronus 7/24/94 */
  add_action("rpromote","rpromote");
  add_action("rdemote","rdemote");
//  block commands added by Dyraen  17may95.
  add_action("b_chat","block_chat");
  add_action("b_shout","block_shout");
  add_action("r_chat","remove_chat");
  /* Added by Aragorn, just testin' */
  enable_wizard();
load_login();
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
int codechange(string str) {
   if (!str || str=="") return notify_fail("Usage : codechange <text>\n");
   log_file("Codechange",ctime(time())+" : "+
                  (string)this_player()->query_name()+"\n"+str+"\n");
   write("Ok.\n");
   return 1;
}

// Coded the 5th of may 1994 by Begosh@RotD
// Receiver for the chat

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

int query_creator() { return 1; }
int query_lord() { return 1; }

static int promote(string str) {
  if("/secure/master"->high_programmer(geteuid(this_player()))){
  if (!str) {
    notify_fail("Usage: promote <person>\n");
    return 0;
  }
  return (int)"/secure/master"->create_creator(str);
  }
}

static int do_demote(string str) {
  if("/secure/master"->high_programmer(geteuid(this_player()))){
  if (!str) {
    notify_fail("Syntax: demote <person> <reason>\n");
    return 0;
  }
  return (int)"/secure/master"->demote_creator(str);
  }
}

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

string query_object_type() {
  if ("/secure/master"->high_programmer(geteuid(this_object())))
  return "D";
  if ( FORGER[ geteuid( this_object() ) ] ) return "F";
  if (rank) return "L"+rank;
  return "L";
} /* query_object_type() */


int ok_set_rank(int i) {
   if ( "/secure/master"->high_programmer( geteuid( previous_object() ) ) )
   return ( rank = i );
   return -1;
}

int query_rank(){
   /* just a fix to make sure abnormal ranks dont show up -Akira */
   if (rank > MAX_HRANK) rank = 0;
   return rank;
}

/* do_reduce added for ranks by Kelaronus 7/26/94 */
do_reduce(){
   /* only gods may do this */
   if((int)this_player()->god() == 1){

     /* cant rdemote pass rank 0 */
     if((int)this_object()->query_rank() == 0){
        notify_fail("This immortal is the lowest rank already.\n");
        return 0;
     } 

     rank = rank - 1;
     message("You have been demoted to rank "+this_object()->query_rank()+
               " by "+this_player()->query_cap_name()+".\n",
               "", this_object());
     message(this_object()->query_cap_name()+" demoted to rank "+
               this_object()->query_rank()+".\n", "", this_player());
     log_file("RANKS", sprintf("Demoted "+this_object()->query_cap_name()+
        " to the rank of Lord "+this_object()->query_rank()+
        ": %15-s %s\n", this_player()->query_cap_name(), ctime(time())));
     return rank;
   }
}

/* do_advance added for ranks by Kelaronus 7/25/94 */
int do_advance(){
   /* only gods may do this */
   if((int)this_player()->god() == 1){

     if((int)this_object()->query_rank() >= MAX_HRANK){
             notify_fail("This lord is already an elder.\n");
             return 0;
     }

     rank = rank + 1;
     message("You have been promoted to rank "+this_object()->query_rank()+
              " by "+this_player()->query_cap_name()+".\n",
               "", this_object());
     message(this_object()->query_cap_name()+" promoted to rank "+
              this_object()->query_rank()+".\n", "", this_player());
     log_file("RANKS", sprintf("Promoted "+this_object()->query_cap_name()+
          " to the rank of Lord "+this_object()->query_rank()+
          ": %15-s %s\n", this_player()->query_cap_name(), ctime(time())));
     tell_object(this_player(), this_object()->query_cap_name()+" is now "+
              "rank "+this_object()->query_rank()+".\n");
     tell_object(this_object(), "You have been promoted to rank "+
          this_object()->query_rank()+" by "+this_player()->query_cap_name()+
          ".\n");
   }
}
string query_gtitle(){
int i;

if ("/secure/master"->high_programmer(geteuid(this_object()))) {
  if((string)this_object()->query_name()=="aragorn")
   return "the Demi-God of Bits";
  if((string)this_object()->query_name()=="baldrick")
   return "the Demi-God of Sage Advice, God of Final Realms";
  if((string)this_object()->query_name()=="gar")
   return "the Demi-God of Darkness"; 
  if((string)this_object()->query_name()=="aeryn")
   return "the Demi-Goddess of Fire and Ice";
  if((string)this_object()->query_name()=="rahvin")
  return "the Demi-God of War and Law";
  if((string)this_object()->query_name()=="skaflock")
   return "the Demi-God of Justice and Honour";
  if((string)this_object()->query_name()=="akira")
   return "the Demi-God of the Outer Planes";
  if((string)this_object()->query_name()=="dyraen")
   return "the Demi-God of Thunder and Lightning";
  if((string)this_object()->query_name()=="kelaronus")
   return "the Demi-God of Shadows and the Night";
  if((string)this_object()->query_name()=="begosh")
   return "the Demi-God of Mischief and Trickery";
if((string)this_object()->query_name()=="lancer")
return "the Demi-God of Life and Wisdom\; Liberty, Fraternity, Equality"; 
  else {

   /* no special title Demi-gods */
   if((int)this_object()->query_gender() == 2){
    return "the Demi-Goddess of Balance";
   }
   else{
    return "the Demi-God of Balance";
   }

  } /* end-else */
 } /* end highprogrammer */

 /* special High Lords */
 if( FORGER[ geteuid( this_object() ) ] )
    return "the Eternal Forger of the Realms";
 

/* new gtitle code for domain lords - Kelaronus 6/23/94 */
/* changed top switches so it is more robust to fix
   rpromotion comflicts - Akira */
domains = get_dir("/d/");
for(i=0; i<sizeof(domains); i++) {
  mast = "/d/" + domains[i] + "/master";
  if(mast->query_lord() == this_object()->query_name()){
    dtitle = capitalize(domains[i]);
     if(domains[i] == "omiq")
      dtitle = "High Adventure";
     if((domains[i] == "Thelbane") || (domains[i] == "lirath"))
	dtitle = "Lirath and Thelbane";
    if((int)this_object()->query_gender() == 2){
       switch((int)this_object()->query_rank()) {
       default:
        return "the High Immortal, Lady of "+dtitle;
	break;  
       case 1:
        return "the High Immortal, Senior Lady of "+dtitle;
	break;
       case MAX_HRANK:
        return "the High Immortal, Elder Lady of "+dtitle;
        break;
       }
    }
    else {
       switch((int)this_object()->query_rank()) {
       default:
        return "the High Immortal, Lord of "+dtitle;
        break;
       case 1:
        return "the High Immortal, Senior Lord of "+dtitle;
        break;
       case MAX_HRANK:
        return "the High Immortal, Elder Lord of "+dtitle;
        break;
       }
    } /* end gender */
  } /* end lord */
}

/* High Lords without domains */
if((int)this_object()->query_gender() == 2){
       switch((int)this_object()->query_rank()) {
       default:
        return "the High Immortal, Renegade Lady";
        break;
       case 1:
        return "the High Immortal, Renegade Senior Lady";
        break;
       case MAX_HRANK:
        return "the High Immortal, Renegade Elder Lady";
        break;
       }
 }
else {
       switch((int)this_object()->query_rank()) {
       default:
        return "the High Immortal, Renegade Lord";
        break;
       case 1:
        return "the High Immortal, Renegade Senior Lord";
        break;
       case MAX_HRANK:
        return "the High Immortal, Renegade Elder Lord";
        break;
       }
}

}/*Query_gtitle()*/

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

int b_chat(string str) {
object pob;
string plr, rea;
 
  notify_fail("Syntax: block_chat <player> <reason>\n");
  if (!str)
    return 0;
  if (sscanf(str,"%s %s",plr,rea) != 2)
    return 0;
  pob = find_player(plr);
  if (!pob) {
    notify_fail("Cannot find "+plr+".\n");
    return 0;
  }
  write("Ok.\n");
  return "/global/set_channel"->block_chat(pob,rea);
} /* b_chat() */
 
int b_shout(string str) {
object pob;
string plr, rea;
 
  notify_fail("Syntax: block_shout <player> <reason>\n");
  if (!str)
    return 0;
  if (sscanf(str,"%s %s",plr,rea) != 2)
    return 0;
  pob = find_player(plr);
  if (!pob) {
    notify_fail("Cannot find "+plr+".\n");
    return 0;
  }
  log_file("SHOUT",ctime(time())+" "+this_player()->query_cap_name()+
           " blocked "+pob->query_cap_name()+"'s shout.\nReason: "+
           rea+".\n");
  write("Ok.\n");
  pob->set_social_points(-2000);
  pob->do_efun_write("You have abused the shout channel and your "+
                     "shouting privileges have been taken away for "+
                     "a set period of time. Continue to abuse this, "+
                     "and you will lose all shouting privileges "+
                     "permanently.\n");
  return 1;
} /* b_shout() */

int r_chat(string str) {
object pob;
string plr, rea;
 
  notify_fail("Syntax: remove_chat <player> <reason>\n");
  if (!str)
    return 0;
  if (sscanf(str,"%s %s",plr,rea) != 2)
    return 0;
  pob = find_player(plr);
  if (!pob) {
    notify_fail("Cannot find "+plr+".\n");
    return 0;
  }
  write("Ok.\n");
  return "/global/set_channel"->remove_chat(pob,rea);
} /* r_chat() */
