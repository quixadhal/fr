#include "mail.h"
inherit "/std/object";

#include "board.h"

string board_name;

mapping being_written;

void string_more(string arg, string prompt);

void setup() {
  set_name("board");
  set_short("bulletin board");
  add_adjective("bulletin");
  set_main_plural("boards");
  reset_get();
  board_name = "fish";
  being_written = ([ ]);
}

string query_plural() {
  return pluralize(::short())+" [ "+sizeof((mixed *)BOARD_HAND->get_subjects(board_name))+
                           " notes ]";
}

string short(int dark) {
  return ::short(dark)+" [ "+
                sizeof((mixed *)BOARD_HAND->get_subjects(board_name))+" notes ]";
}

string the_date(int i) {
  return ctime(i)[4..9];
}

string long(string str, int dark) {
  int i;
  mixed *stuff;
  string ret;
  mapping news_rc;

  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  ret = "A bulletin board ("+board_name+").\n";
  ret += sprintf("%#-*s\n\n", this_player()->query_cols(),
                            "read [note number]\npost <subject>\n"+
                            "store <note number> <file>\neat <note number>\n"+
                            "reply <note number>\nfollowup <note number>\n");
  if (!sizeof(stuff))
    return ret+"The board is completely empty.\n";
  news_rc = (mapping)this_player()->query_property(NEWS_RC);
  if (!news_rc)
    news_rc = ([ ]);
  for (i=0;i<sizeof(stuff);i++)
    if (news_rc[board_name] < stuff[i][B_TIME])
      ret += sprintf("N %2d: %-=*s\n", i+1, (int)this_player()->query_cols()-6,
             stuff[i][B_SUBJECT]+" ("+
             capitalize(stuff[i][B_NAME])+" "+the_date(stuff[i][B_TIME])+")");
    else
      ret += sprintf("  %2d: %-=*s\n", i+1, (int)this_player()->query_cols()-6,
             stuff[i][B_SUBJECT]+" ("+
             capitalize(stuff[i][B_NAME])+" "+the_date(stuff[i][B_TIME])+")");
  string_more(ret, "--- Board");
  return "";
}

void init() {
  add_action("read", "r*ead");
  add_action("post", "p*ost");
  add_action("eat", "eat");
  add_action("followup", "f*ollowup");
  add_action("reply", "rep*ly");
  add_action("save_note", "store");
}

void string_more(string arg, string prompt) {
  object obj;
/* changed to our more_string

  if (!(obj = (object)MAIL_SERVER->mail_reader(this_player()))) {
    log_file(LOG_FILE, "board: got NULL MAIL_READER from MAIL_SERVER.\n");
    write("MAIL_SERVER error ...\n");
    return;
  }
  obj->string_more(arg, prompt);
*/
  this_player()->set_finish_func(0);
  this_player()->more_string(arg, prompt);
}

int read(string str) {
  int num, i;
  mixed stuff;
  mapping news_rc;

  notify_fail("Syntax: read <note number>\n");
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  news_rc = (mapping)this_player()->query_property(NEWS_RC);
  if (!news_rc)
    news_rc = ([ ]);
  if (!str) {
    i = sizeof(stuff)-1;
    while (i >= 0 &&stuff[i][B_TIME] > news_rc[board_name] )
      i--;
    if (i == sizeof(stuff)-1) {
      notify_fail("No unread messages.\n");
      return 0;
    }
    num = i+2;
  } else if (sscanf(str, "%d", num) != 1)
    return 0;
  if (num < 1 || num > sizeof(stuff)) {
    notify_fail("No note of that number.\n");
    return 0;
  }
  num --;
  if (news_rc[board_name] < stuff[num][B_TIME]) {
    news_rc[board_name] = stuff[num][B_TIME];
    this_player()->add_property(NEWS_RC, news_rc);
  }
  string_more(sprintf("%|*s\n\n", this_player()->query_cols(),
              "Note #"+(num+1)+" on "+stuff[num][B_SUBJECT]+" by "+
              stuff[num][B_NAME])+
              BOARD_HAND->get_message(board_name, num),
                 "[Note "+(num+1)+"]");
  return 1;
}

int post(string str) {
  string body;

  notify_fail("Syntax: post <subject>\n");
  if (!str)
    return 0;
/* ok shove the editing stuff in here.  Lets make it function string_edit
 * sound frogy?
 */
/*
  string_edit("");
  body = string_edit_res;
*/
  being_written[this_player()->query_name()] = str;
  this_player()->do_edit(0,"end_of_thing");
  return 1;
}

void end_of_thing(string body) {
  if (body && body != "" && being_written[this_player()->query_name()])
    if (!BOARD_HAND->add_message(board_name, this_player()->query_name(),
                            being_written[this_player()->query_name()], body))
      write("Error writing message.\n");
    else
      write("Message posted.\n");
  else
    write("Erorr.\n");
  being_written = m_delete(being_written, this_player()->query_name());
  return ;
}

int eat(string str) {
  int num;

  notify_fail("Syntax: eat <note number>\n");
  if (!str)
    return 0;
  if (sscanf(str, "%d", num) != 1)
    return 0;
  if (!BOARD_HAND->delete_message(board_name, num-1)) {
    notify_fail("Your mouth isn't big enough to eat messages!\n");
    return 0;
  }
  write("You viciously tear off and eat note "+num+"\n");
  say(this_player()->query_cap_name()+" viciously tears off and eats note "+
         num+".\n");
  return 1;
}

int followup(string str) {
  int num, i;
  mixed stuff;
  string s;

  notify_fail("Syntax: followup <note number>\n");
  if (!str)
    return 0;
  if (sscanf(str, "%d", num) != 1)
    return 0;
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  if (num < 1 || num > sizeof(stuff)) {
    notify_fail("No note of that number.\n");
    return 0;
  }
  if (sscanf(stuff[num-1][B_SUBJECT], "Re:#%d %s", i, s) != 2)
    being_written[this_player()->query_name()] = "Re:#1 "+stuff[num-1][B_SUBJECT];
  else
    being_written[this_player()->query_name()] = "Re:#"+i+" "+s;
  this_player()->do_edit(0,"end_of_thing");
  return 1;
}

int reply(string str) {
  int num;
  mixed stuff;

  notify_fail("Syntax: reply <note number>\n");
  if (!str)
    return 0;
  if (sscanf(str, "%d", num) != 1)
    return 0;
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  if (num < 1 || num > sizeof(stuff)) {
    notify_fail("No note of that number.\n");
    return 0;
  }
  MAIL_TRACK->mail(stuff[num-1][B_NAME], stuff[num-1][B_SUBJECT]);
  return 1;
}

int save_note(string arg) {
  int which, saved;
  string file;
  mixed *stuff;

  if (!arg || (sscanf(arg, "%d %s", which, file) != 2)) {
    notify_fail("Syntax: store <note number> <file name>\n");
    return 0;
  }
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  if (which < 1 || which > sizeof(stuff)) {
    notify_fail("Invalid note number.\n");
    return 0;
  }
  which--; /* 1..n */
  file += ".note";
  seteuid(geteuid(this_player()));
  saved = write_file(file, stuff[which][B_SUBJECT]+"\n\n"+
             BOARD_HAND->get_message(board_name, which));
  if(saved)
    write("Message " + (which+1) + " saved to file " + file + ".\n");
  else
    write("You fail to save to " + file + ".\n");
  seteuid(0);
  return 1;
}

void set_board_name(string str) { board_name = str; }
void set_datafile(string str) { board_name = str; }
