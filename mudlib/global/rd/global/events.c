// /global/events.c

inherit "/global/play_parse_com";
inherit "/global/communicate";

#include "commands.h"
#include "player.h"
#include "property.h"
#include "term.h"

// Begosh was here 10th of may, '94
  int earmuffs, cols, rows; // chat and guild removed.
static mapping colour_map; /* this so that changeing the definitions gets fixed
                            * when they log in again.  Also keeps the save
                            * file smaller. */
string term_name = "dumb";
static string new_line = "";

void create() {
  languages = ({ "common" });
  cur_lang = "common";
  ::create();
  ignored = ({ });
} /* create() */

string query_term_name() { return term_name; }
int query_earmuffs() { return earmuffs; }
// int query_chat() { return chat; }
// int query_guild() { return guild; }

int query_see_magic()
{
  string guild;

  if(!(guild = (string)this_object()->query_guild_ob())) return 0;
  return (int)guild->query_see_magic();
} /* query_see_octarine() */

/*
void new_tell_object(object ob, string mess){
  int htime;
  string name;
  if((htime = (int)ob->query_property("harass")) && htime > 0){
    name = (string)ob->query_name();
    if(htime < time()){
      ob->remove_property("harass");
      efun::tell_object(ob,
	    "===== What you see is no longer being logged =====\n");
      log_file("harass/"+name+".log", "Harass Log stopped: "+
	       ctime(time())+"\n===================================\n");
    }
    else log_file("harass/"+name+".log", mess);
  }
  efun::tell_object(ob, mess);
}
*/

string read_message(string str, string type, string lang) {
  mixed bing;

  if (member_array(lang, languages) == -1)
    if ((bing = (mixed)LANGUAGE_HAND->query_garble_object(lang)))
      if ((bing = (mixed)bing->garble_text(str, previous_object())))
        return "You cannot read the writing "+bing+
           (type?" written in "+type:"")+"\n";
      else
        return "You could have sworn there was writing there...\n"; /* Invisible text... */
    else
      return "You cannot read the writing "+(type?" written in "+type:"")+"\n";
/*
 * Magical writing does silly things with the text string.  Need to test
 * for this...
 */
  if (LANGUAGE_HAND->query_language_magic(lang))
    if ((bing = (mixed)LANGUAGE_HAND->query_garble_object(lang)))
      return (string)bing->magical_text(str, previous_object());
    else {
/* ARggh!  No garble object!  Irk.  What now?  Panic!  Yes Panic! */
      return "The mud panics as it finds some magic writting you can read but "+
             "it cannot find the interpreter for,\n";
    }
  if (!type)
    return str+"\n";
  return "'"+str+"' written in "+type+"\n";
} /* read_message() */

string fix_string(string ret) {
  string *st;
  int i, off, oct;

  if (!colour_map)
    colour_map = (mapping)TERM_HANDLER->set_term_type(term_name);
  if (!stringp(ret) || ret == "")
    return ret;
  st = explode(ret, "%^");
  ret = "";
  for (i=0;i<sizeof(st);i++) {
    if(st[i][0..8] == "OCTARINE:")
      if(query_see_magic()) st[i] = extract(st[i], 9);
      else continue;
    if (colour_map[st[i]])
      ret += colour_map[st[i]];
    else
      ret += st[i];
  }
  return ret+colour_map["RESET"];
} /* fix_string() */

int set_term_type(string str) {
  mapping tmp_col;

  if (!str) {
    notify_fail(sprintf("%-=*s", cols,
                "Syntax: "+query_verb()+" <term_type>\n"+
                "Where term type is one of the following: "+
                implode((string *)TERM_HANDLER->query_term_types(), ", ")+
                ".\n"));
    return 0;
  }
  if(str != term_name) {
    if(member_array(str, (string *)TERM_HANDLER->query_term_types()) != -1) {
      colour_map = (mapping)TERM_HANDLER->set_term_type(str);
      term_name = str;
      write("Ok, terminal type set to "+str+".\n");
      return 1;
    } else {
      notify_fail("No such terminal type as " + str  + ".\n");
      return 0;
    }
  } else {
    notify_fail("Terminal type unchanged as " + str + ".\n");
    return 0;
  }
} /* set_term_type() */

void event_commands(){
  add_action("earmuffs", "earmuffs");
  add_action("inform", "inf*orm");
  add_action("set_our_rows", "rows");
  add_action("set_our_cols", "cols");
  add_action("set_term_type", "term");
  add_action("do_new_line","new_*line");
  if(this_object()->query_property(NO_LINE_PROP))
    new_line = "";
  else
    new_line = "\n";
} /* event_commands() */

int earmuffs(string str)
{
  string *bits, *types, *on;
  int i;

  types = ({ "shout" });
  if (this_object()->query_creator())
    types += ({ "multiple-soul", "remote-soul", 
                "inter-creator-tell" });

  on = (string *)this_object()->query_property("earmuffs");
  if (!on) on = ({ });

  if (!str || str == "") 
  {
    if (earmuffs)
      write("Your earmuffs are on.\n");
    else
      write("Your earmuffs are off.\n");

/*
    if (!sizeof(on)) 
      write("You have nothing set to be earmuffed.\n");
    else 
*/
    {
      for (i=0;i<sizeof(on);i++)
        write("You have "+on[i]+" earmuffed.\n");

      on = types - on;
      for (i=0;i<sizeof(on);i++)
        write(on[i]+" events are not currently being earmuffed.\n");
    }
    return 1;
  }
  bits = explode(lower_case(str), " ");
  bits = bits - ({ "" });

  if (sizeof(bits) == 1)
  {
    switch (bits[0]) 
    {
    case "on" :
      earmuffs = 1;
      write("Ear muffs turned on.\n");
      if(!sizeof(on))
        write("WARNING: You've not set anything to be earmuffed.\n");
      return 1;

    case "off" :
      earmuffs = 0;
      write("Ear muffs turned off.\n");
      return 1;

    case "all" :
      bits = types;
      break;

    case "none" :
      on = ({ });
      write("Nothing will be ear muffed any more.\n");
      this_player()->add_property("earmuffs", on);
      return 1;
    }
  }
  for (i=0;i<sizeof(bits);i++)
  {
    if (member_array(bits[i], types) == -1) 
      write("I cannot earmuff "+bits[i]+" events.\n");
    else 
    {
      if (sizeof(bits) > i+1) 
      {
        switch (bits[i+1]) 
        {
        case "on" :
          if (member_array(bits[i], on) == -1)
            on += ({ bits[i] });
          write("Your "+bits[i]+" events will now be earmuffed.\n");
          i++;
          break;

        case "off" :
          on = on - ({ bits[i] });
          write("Your "+bits[i]+" events will not be earmuffed.\n");
          i++;
          break;

        default :
          if (member_array(bits[i], on) == -1) 
          {
            write("Your "+bits[i]+" events will be earmuffed.\n");
            on += ({ bits[i] });
          } 
          else 
          {
            write("Your "+bits[i]+" events will not be earmuffed.\n");
            on = on - ({ bits[i] });
          }
          break;
        }
      } 
      else 
      {
        if (member_array(bits[i], on) == -1) 
        {
          write("Your "+bits[i]+" events will be earmuffed.\n");
          on += ({ bits[i] });
        } 
        else 
        {
          write("Your "+bits[i]+" events will not be earmuffed.\n");
          on = on - ({ bits[i] });
        }
      }
    }
  }
  this_player()->add_property("earmuffs", on);
  return 1;
} /* earmuffs() */

int check_earmuffs(string type) 
{
  string *on;

  if(!earmuffs)
    return 0;

  on = (string *)this_object()->query_property("earmuffs");

  if (!on || !sizeof(on)) 
    return 0;

  if (member_array(type, on) == -1)
    return 0;

  return 1;
} /* check_earmuffs() */

int inform(string str) {
  string *types, *on, *frog;
  int i;

  if (this_object()->query_creator())
    types = ({ "logon", "link-death", "message", "call", "death", "guild" });
  else
    types = ({ "logon" });
  if (this_object()->query_lord())
    types += ({ "force", "enter", "dest","clone" });
  on = (string *)this_object()->query_property("inform");
  if (!on)
    on = ({ });
  if (!str) str = "";
  frog = explode(str, " ");
  if (!frog)
    frog = ({ });
  else
    frog = frog - ({ "", 0 });
  if (!sizeof(frog)) {
/* show status */
    if (this_object()->query_property("inform repressed"))
      write("Your informs are currently being repressed.\n");
    for (i=0;i<sizeof(on);i++)
      write("You will be informed of "+on[i]+" events.\n");
    types = types - on;
    for (i=0;i<sizeof(types);i++)
      write("You are not being informed of "+types[i]+" events.\n");
    return 1;
  }
  if (sizeof(frog) == 1) {
    switch (frog[0]) {
      case "on" :
        this_object()->remove_property("inform repressed");
        write("You are now being informed.  This is true!\n");
        for (i=0;i<sizeof(on);i++)
          write("You will be informed of "+on[i]+" events.\n");
        return 1;
      case "off":
        this_object()->add_property("inform repressed", 1);
        write("Inform is now repressed.\n");
        return 1;
      case "all":
        on = types;
        frog = frog[1..100];
        for (i=0;i<sizeof(on);i++)
          write("You will be informed of "+on[i]+" events.\n");
        break;
      case "none" :
        on = ({ });
        write("You will not be informed of anything.\n");
        frog = frog[1..100];
        break;
    }
  }
  for (i=0;i<sizeof(frog);i++)
    if (member_array(frog[i], types) == -1) {
      write("I don't know about "+frog[i]+" events.\n");
    } else {
      if (sizeof(frog) > i+1) {
        switch (frog[i+1]) {
          case "on" :
            if (member_array(frog[i], on) == -1)
              on += ({ frog[i] });
            write("You will now be informed of "+frog[i]+" events.\n");
            i++;
            break;
          case "off" :
            on = on - ({ frog[i] });
            write("You will now not be informed of "+frog[i]+" events.\n");
            i++;
            break;
          default :
            if (member_array(frog[i], on) == -1) {
              write("You will now not be informed of "+frog[i]+" events.\n");
              on += ({ frog[i] });
            } else {
              write("You will now not be informed of "+frog[i]+" events.\n");
              on = on - ({ frog[i] });
            }
            break;
        }
      } else {
        if (member_array(frog[i], on) == -1) {
          write("You will now be informed of "+frog[i]+" events.\n");
          on += ({ frog[i] });
        } else {
          write("You will now not be informed of "+frog[i]+" events.\n");
          on = on - ({ frog[i] });
        }
      }
    }
  this_object()->add_property("inform", on);
  return 1;
} /* inform() */

/* removed this function since it is now in communicate
int chat(string str)
{
     if(!chat && str == "off") {
       write("Ok.  Chat turned off.\n");
       chat = 1;
       return 1;
     }
     if(chat && str == "on") {
       write("Ok.  Chat turned on.\n");
       chat = 0;
       return 1;
      }
     if(!chat && str == "on") {
       notify_fail("Chat is already on.\n");
       return 0;
     }
     if(chat && str == "off") {
       notify_fail("You haven't turned chat on.\n");
       return 0;
     }
     else {
       notify_fail("Syntax: chat <on/off>\n");
       return 0;
     }
}   /* chat */

/*
int guild(string str)
{
     if(!guild && str == "off") {
       write("Ok. The guild-channel is now turned off.\n");
       guild = 1;
       return 1;
     }
     if(guild && str == "on") {
       write("Ok. The guild-channel is now turned on.\n");
       guild = 0;
       return 1;
      }
     if(!guild && str == "on") {
       notify_fail("The guild-channel is already on.\n");
       return 0;
     }
     if(guild && str == "off") {
       notify_fail("You haven't turned the guild-channel on.\n");
       return 0;
     }
     if(guild && str == "off") {
       notify_fail("You haven't turned the guild-channel on.\n");
       return 0;
     }
     else {
       notify_fail("Syntax: guild <on/off>\n");
       return 0;
     }
}  /* guild */

void event_inter_creator_tell(object ob, string mname, string pname,
    string mess, object ig, int emote)
{
 if(!this_object()->query_creator() || check_earmuffs("inter-creator-tell") ||
    this_object() == ig)
 return;

 efun::tell_object(this_object(), new_line + 
    fix_string(sprintf("%s@%s%s%-=*s\n", pname, mname,
    (emote? " " : ": "), 
    cols-strlen(mname)-strlen(pname)-3,mess)));
}

/* Away away with the old stuff - Begosh
void event_lord_tell(object ob, string start, string mess)
{
  if (ob == this_object() ||
     (check_earmuffs("lord-tell") && query_verb() !="lord!") ||
     !this_object()->query_lord())
    return;

  efun::tell_object(this_object(), new_line + 
    fix_string(sprintf("%s%-=*s\n",
    start, cols - strlen(start), mess)));
}

void event_god_tell(object ob, string start, string mess)  
{
  if (ob == this_object() ||
     (check_earmuffs("god-tell") && query_verb() != "god!") || 
     !("/secure/master"->god((string)this_object()->query_name())))
    return;

  efun::tell_object(this_object(), new_line + 
    fix_string(sprintf("%s%-=*s\n",
    start, cols - strlen(start), mess)));
}

*/
void set_rows(int i) { rows = i; }
int query_rows() { return rows; }

int set_our_rows(string str) {
  int val;

  if(!str) {
    notify_fail("Rows currently set to " + rows + ".\nrows <number> to set.\n");
    return 0;
  }
  if(!sscanf(str, "%d", val) || val <= 10) {
    notify_fail("Invalid number of rows.\n");
    return 0;
  }
  write("Rows set to " + val + ".\n");
  rows = val;
  return 1;
} /* set_our_rows() */

int query_cols() { return cols; }
void set_cols(int i) { cols = i; }

int set_our_cols(string str) {
  int val;

  if(!str) {
    notify_fail("Columns currently set to " + cols + ".\ncols <number> to set.\n");
    return 0;
  }
  if(!sscanf(str, "%d", val) || val <= 35) {
    notify_fail("Invalid column size.\n");
    return 0;
  }
  write("Columns set to " + val + ".\n");
  cols = val;
  return 1;
} /* set_our_cols() */

int do_new_line(string str) {
  switch(str) {
    case 0:
     if (new_line == "")
       new_line = "\n";
     else
       new_line = "";
     break;
    case "off":
      new_line = "";
      break;
    case "on":
      new_line = "\n";
      break;
    default:
      notify_fail("Syntax: new_line <on|off>\n");
      return 0;
  }
  if (new_line == "") {
    this_object()->add_property(NO_LINE_PROP, 1);
    write("New lines after everything switched off.\n");
  } else {
    this_object()->remove_property(NO_LINE_PROP);
    write("New lines after everything switched on.\n");
  }
  return 1;
} /* do_new_line() */

void event_inform(object ob, string mess, string type) {
  string *on;

  on = (string *)this_object()->query_property("inform");
  if (!on) on = ({ });
  if (this_object()->query_property("no_inform")
      || (ob->query_invis() && !this_object()->query_creator())
        || ((int)ob->query_invis() == 2 && !this_object()->query_lord())
      || !sizeof(on))
    return ;
  if (member_array(type, on) == -1) return ;
  efun::tell_object(this_object(), new_line + "[" +
    fix_string(sprintf("%-=*s", cols-2, mess)) + "]\n");
} /* event_inform() */

void event_enter(object ob, string mess, object *ignore) {
  if (pointerp(ignore) && member_array(this_object(), ignore) != -1)
    return ;
  if (mess)
    new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s",
                      cols, process_string(mess))));
} /* event_enter() */

void event_exit(object ob, string mess, object to) {
  int i;

  ::event_exit(ob, mess, to);
  if (mess)
    new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s",
                     cols, process_string(mess))));
} /* event_exit() */

void event_say(object caller, string str, mixed avoid)
{
  if (pointerp(avoid)) 
    if (member_array(this_object(), avoid) != -1)
      return ;
  else 
    if (avoid == this_object())
      return ;

  new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s",
                    cols, process_string(str))));
} /* event_say() */

void event_write(object caller, string str) {
  new_tell_object(this_object(), fix_string(process_string(str)));
} /* event_write() */

void do_efun_write(string str) {
  new_tell_object(this_object(), fix_string(sprintf("%-=*s",
                    cols, process_string(str))));
} /* do_efun_write() */

void event_soul(object ob, string str, mixed avoid) {
  if (ob != this_object())
    event_say(ob, str, avoid);
  else
    do_efun_write(str);
} /* event_soul() */

void event_person_say(object ob, string start, string mess, string lang) 
{
  if (member_array(lang, languages) == -1) {
    mixed str;

    if ((str = (mixed)LANGUAGE_HAND->query_garble_object(lang)))
      if ((str = (mixed)str->garble_say(start, mess))) {
        start = str[0];
        mess = str[1];
      } else
        return ;
    else
      return ;
  } else if (lang != "common")
    start = start[0..strlen(start)-3]+" in "+lang+": ";
  if (ob == this_object()) return;
  new_tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
       start, cols-strlen(start), mess)));
} /* event_person_say() */

void event_person_tell(object ob, string start, string mess, string lang) 
{
  string s;
  int id;

  if(check_block(USE_NO_TELL))
  {
    write(ob, "You can't tell "+(string)this_object()->query_cap_name()+".\n");
    return;
  }

  if (member_array(lang, languages) == -1) {
    mixed str;

    if (str = (mixed)LANGUAGE_HAND->query_garble_object(lang))
      if (str = (mixed)str->garble_say(start, mess)) {
        start = str[0];
        mess = str[1];
      } else
        return ;
    else
      return ;
  } else if (lang != "common")
      start = start[0..strlen(start)-3]+" in "+lang+": ";

  /* The following block of code was added because I got sick
     of people telling me stuff and getting mad when I don't respond.
     I added a little code to report the target's idle time, if any,
     to the teller.
     Firestorm  */

  if ((id = query_idle(this_object())) > TELL_WARN_TIME)  
  {
    mixed str;

      str = ({  });
    if (id/(60*60))
      str += ({  (id/(60*60))+" hours"  });
    if((id/60)%60)
      str += ({  ((id/60)%60)+" minutes"  });
    if(id%60)
      str += ({  (id%60)+" seconds"  });
    write(this_object()->query_cap_name()+" has been idle for "+
        query_multiple_short(str)+".\n");
  }

  /* This will tell players that you are busy :)   -- Firestorm -- */

  if(this_object()->query_in_editor()) 
  {
    write(this_object()->query_cap_name() + " is editing a file "+
        "and may take awhile to respond.\n");
  }

  new_tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
       start, cols-strlen(start), mess)));
} /* event_person_tell() */

void event_whisper(object ob, string start, string mess, object *obs,
                   string lang) {
  string blue;
  mixed str;

  blue = "";
  if (member_array(lang, languages) == -1) {
    if (str = (mixed)LANGUAGE_HAND->query_garble_object(lang))
      if (str = (mixed)str->garble_whisper(start, mess)) {
        start = str[0];
        mess = str[1];
        blue = ": ";
      } else
        return ;
    else
      return ;
  } else if (lang != "common")
      blue = " in "+lang+": ";
  else
    if (!stringp(blue)) blue = "";
  if (member_array(this_object(), obs) == -1)
    new_tell_object(this_object(), new_line + fix_string(sprintf("%s.\n",
                      start + "to " + query_multiple_short(obs) +
                      blue[0..strlen(blue)-3])));
  else if (sizeof(obs) == 1)
    new_tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
                      start + "to you: " + blue, rows - strlen(start) - 10,
                      mess)));
  else
    new_tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
                      start + "to you and ", rows - strlen(start) - 10,
                      query_multiple_short(obs) + blue + ": " + mess)));
} /* event_whisper() */

void event_person_shout(object ob, string start, string mess, string lang) 
{
  if (ob == this_object()) 
    return;
  if((check_block(USE_NO_CHANNELS) || check_earmuffs("shout")) &&
       (string)ob->query_verb() != "shout!")
    return;

  if (member_array(lang, languages) == -1) {
    mixed str;

    if (str = (mixed)LANGUAGE_HAND->query_garble_object(lang))
      if (str = (mixed)str->garble_say(start, mess)) {
        start = str[0];
        mess = str[1];
      } else
        return ;
    else
      return ;
  } else if (lang != "common")
    start = start[0..strlen(start)-3]+" in "+lang+": ";

  new_tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
       start, cols-strlen(start), mess)));
} /* event_person_shout() */

void event_creator_tell(object ob, string start, string mess) 
{
  if (ob == this_object() || 
      (check_earmuffs("creator-tell") && query_verb() != "cre!") ||
      !this_object()->query_creator())
    return;

  efun::tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
        start, cols - strlen(start), mess)));
} /* event_creator_tell() */

/* removed by Begosh
void event_person_chat(object ob, string start, string mess) 
{
  if (ob == this_object() || ((check_block(USE_NO_CHANNELS) || 
      chat == 1) && query_verb() != "chat!"))
    return;

  efun::tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
        start, cols - strlen(start), mess)));
} /* event_person_chat() */

/*
void event_person_guild(object ob, string start, string mess) 
{
  if (ob == this_object() || ((check_block(USE_NO_CHANNELS) ||
      guild == 1) && query_verb() != "guild!") ||
      ((string)this_object()->query_guild_ob() != 
      (string)ob->query_guild_ob()))
    return;

  efun::tell_object(this_object(), new_line + fix_string(sprintf("%s%-=*s\n",
        start, cols - strlen(start), mess)));
} /* event_person_guild() */

void event_player_echo_to(object ob, string mess) 
{
  if (this_object()->query_lord())
    new_tell_object(this_object(), ob->query_cap_name()+" echo to's:\n");
  new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s\n",
        cols, mess)));
} /* event_player_echo_to() */

void event_player_emote_all(object ob, string mess) 
{
  if (ob == this_object())
    return;
  if (this_object()->query_lord())
    efun::tell_object(this_object(), ob->query_cap_name()+" emote all's:\n");
  new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s\n",
        cols, mess)));
} /* event_player_echoall() */

void event_player_echo(object ob, string mess) {
  if (ob == this_object())
    return;
  if (this_object()->query_lord())
    new_tell_object(this_object(), ob->query_cap_name()+" echo's:\n");
  new_tell_object(this_object(), new_line + fix_string(sprintf("%-=*s\n",
        cols, mess)));
} /* event_player_echo() */
