#include "library.h"
#include "tune.h"
#include "login_handler.h"
#include "drinks.h"
#include "weather.h"
#include "log.h"

inherit "/global/line_ed";
inherit "/global/auto_load";
inherit "/global/events";
inherit "/global/log";
inherit "/global/spells";
inherit "/global/help";
inherit "/global/more_string";
inherit "/global/finger";
inherit "/global/pweath";
inherit "/std/living/living";
inherit "/std/living/handle";
inherit "/global/stats-rear";
inherit "/global/psoul";
inherit "/global/guild-race";
inherit "/global/drunk";
inherit "/global/last";
inherit "/global/more_file";
inherit "/global/path";

#include "money.h"
#include "post.h"
#include "mail.h"
#include "player.h"

#define START_POS "/d/ss/daggerford/ladyluck"
#define STD_RACE "/std/races/human"

static int last_command, net_dead;
static int save_counter, hp_counter, combat_counter;
int hb_counter;
string *auto_load, last_on_from, last_pos;
mixed *money_array;
string title, extra_title;
int headache, max_headache, time_on, max_deaths, monitor;
// int ntime_last_saved;
int invis, *saved_co_ords, ed_setup, start_time;
int creator, app_creator, deaths, last_log_on;
static object snoopee;

void set_creator(int i);
void start_player();
void run_away();
void set_title(string str);
void public_commands();
int save_me();
int save();
void set_desc(string str);
string query_title();
int query_creator();
static void set_name(string str);
int check_dark(int light);
void adjust_level(int i);
int query_level();
void quit();

void create() 
  {
  int *i,j,k;

  if (name)
  {
    event (children("/global/lord"), "inform", this_player()->query_name()+
    " called create() on "+name, "person_cheat");
    return ;
  }
  level = 0;
  living::create();
  events::create();
  pweath::create();
  psoul::create();
  line_ed::create();
  add_property("determinate", "");
   //spells::create();
  spells = ({ });
  spheres = ({ });
  money_array = ({ });
  time_on = time();
  start_time = time();
  seteuid("PLAYER");

   Str = 13;
   Dex = 10;
   Int = 11;
   Con = 11;
   Wis = 10;
   Cha = 10; 

  set_thac0(22);
  max_deaths = query_con();
  max_social_points = 10;
  desc = 0;
  add_property("player", 1);
  cols = 79;
  rows = 24;
  verbose = 1;
  last_log_on = time();
  save_counter = 0;
  hp_counter = 0;
  race_ob = RACE_STD;
  sscanf(file_name(this_object()), "%s#", my_file_name);
} /* create() */

int query_x_time_on() { return time_on; }
void set_x_time_on(int i) { time_on = i; }
int set_x_deaths(int i) { deaths = i; }


void move_player_to_start(string bong, int new) {
 int tmp;
 object money;
 mapping mail_stat;
 string s;
 if (file_name(previous_object())[0..13] != "/secure/login#") {
    notify_fail("You dont have the security clearance to do that.\n");
    return ;
 }
/* some stupid test to make sure that the previous object is /secure/login. */
  seteuid("Root");
  set_name(bong);
//  if (query_property("guest"))
    log_file("ENTER", sprintf("Enter : %15-s %s (guest)[%d] [%s]\n",
               name, ctime(time()), time(),
               (query_ip_name()?query_ip_name():query_ip_number())));
/*
  else
    log_file("ENTER", sprintf("Enter : %15-s %s[%d]\n",
               name, ctime(time()), time()));
 */
  restore_object("/players/"+name[0..0]+"/"+name,1);

  // Aragorn fix
  colour_map = 0;
  set_short(capitalize(name));
  if (!cols) cols = 79;
  add_property("determinate", "");
  if (this_player()->query_creator())
    seteuid(name);
  else
    seteuid("PLAYER");
  write("You last logged in from "+last_on_from+".\n");
  last_on_from = query_ip_name(this_object())+" ("+
                 query_ip_number(this_object())+")";
  bonus_cache = ([ ]);
  level_cache = ([ ]);
  if (time_on < -500*24*60*60)
    time_on += time();
  if (time_on > 0)
    time_on = 0;
  time_on += time();
  guild_joined += time();
  start_player();
  if(!msgin || msgin[0] != '@')
    msgin = msgout = mmsgin = mmsgout = 0;
  if(!msgin)
    msgin = "@$N arrives from $F.";
  if(!msgout)
    msgout = "@$N leaves $T.";
  if(!mmsgin)
    mmsgin = "@$N appears out of the ground.";
  if(!mmsgout)
    mmsgout = "@$N vanishes in a puff of smoke.";
  cat("doc/NEWS"); 

  if (!last_pos || (my_file_name == "/global/player" && last_pos[0..1] == "/w")
        || catch(call_other(last_pos, "??")))
    {
    /* Hmm, think I have to change this. should make a neater version.
     * Let they be put in their home cottage.
     */
    /*
    if (last_pos[0..1] == "/w")
      last_pos = "/d/ss/daggerford/ladyluck";
     else
      */
      last_pos = "/room/raceroom";
    move(last_pos);
  }
  else
  {
    move(last_pos);
   /*
    * Set the old co ord if one does not already exist.  Otherwise don't
    * destroy the already existing nameing scheme.
    */
    if (!last_pos->query_co_ord() && saved_co_ords)
       last_pos->set_co_ord(saved_co_ords);
  }
  event(users(), "inform", query_cap_name() +
    " enters " + (query_property("guest")?"as a guest of ":"") + "FR-MUD"+
    (new?" (New player)":""), 
    "logon");
  say(query_cap_name()+" enters the game.\n", 0);
  if (verbose)
    command("look");
  else
    command("glance");
  last_pos->enter(this_object());
  money = clone_object(MONEY_OBJECT);
  money->set_money_array(money_array);
  money->move(this_object());
  if (query_property(PASSED_OUT_PROP))
    call_out("remove_property", 10+random(30), PASSED_OUT_PROP);
  curses_start();
    mail_stat = (mapping)POSTAL_D->mail_status(query_name());
      if(mail_stat["unread"]) {
     if(mail_stat["total"] == 1)
       write("\n        >>> Your only mail is unread! <<<\n");
     else write("\n        >>> "+mail_stat["unread"]+" of your "+
       mail_stat["total"]+" letters are unread. <<<\n");
    }
  if (query_property("dead")) {
    money = clone_object(DEATH_SHADOW);
    money->setup_shadow(this_object());
  }
  if(query_property("noregen"))
    DEATH_CHAR->person_died(query_name());
  exec_alias("login","");
  last_log_on = time();
  LOGIN_HANDLER->player_logon(bong);
  if (my_file_name != "/global/player")
    if (file_size("/w/"+name+"/"+PLAYER_ERROR_LOG) > 0)
      write("You have ERRORS in /w/"+name+"/"+PLAYER_ERROR_LOG+"\n");
} /* move_player_to_start() */

void start_player() {
  if (app_creator && my_file_name != "/global/player") {
    this_player()->all_commands();
    this_player()->app_commands();
  }
  if (creator && my_file_name != "/global/player") 
    this_player()->wiz_commands();
  reset_get();
  enable_commands();
  public_commands();
  parser_commands();
  handle_commands();
  force_commands();
  race_guild_commands();
  soul_commands();
  event_commands();
  finger_commands();
  communicate_commands();
  living_commands();
  spell_commands();
  logging_commands();
  weather_commands();
  editor_commands();
  set_living_name(name);
  set_no_check(1);
  set_con(Con);
  set_str(Str);
  set_int(Int);
  set_dex(Dex);
  set_wis(Wis);
  set_cha(Cha);
  reset_all();
  current_path = home_dir;
  //spells::init_spells();
  call_out("do_load_auto", 0);
  add_property("loading",1);
  birthday_gifts(); /* check if birthday today and give gifts */
  set_heart_beat(1);
  if (wimpy > 100)
    wimpy = 25;
} /* start_player() */

/* Ok.. the big question is: will the  reset() be called ?
 * Baldrick Feb '94
 * it does, but not in lord.c and those..
 */

void reset ()
  {
  /* to make the object not save each reset */
  /* well, with tose scarse resets we have now we do save every reset.
  if (save_counter == 2)
    {
    save();
    update_tmps();
    save_counter = 0;
    }
  else
    ++save_counter;
   */
  save();
  update_tmps();

}  /* reset()  */


// Aragorn testing
void do_auto_equip() {
   if((string)this_object()->query_property("autoequip") == "yes")
      this_object()->do_equip();
}

int do_load_auto() { 
  load_auto_load(auto_load, this_object());
  remove_property("loading");
  call_out("do_auto_equip",3);
} /* do_load_auto() */

int is_player() {
   if (my_file_name == "/global/player") return 1;
   else return 0;
}

void public_commands() {
  add_action("do_whoami", "whoami");
  add_action("rearrange", "rearrange");
  /* taken out to see if the players wont die that much...
   * baldrick, nov '94.
  add_action("do_su", "su");
   */
  add_action("help_func","help");
  /* why here ? maybe it should be a creatorcommand..*/
  /* it shoud. */
  add_action("last", "last");
  add_action("restart_heart_beat", "restart");
  add_action("look_me","l*ook");
  add_action("glance", "glance");
  add_action("do_kill","kill");
  /* I like this one better.. */
  add_action("do_kill","att*ack");
  add_action("do_stop","stop");
  add_action("invent","inventory");
  add_action("invent","i");
  add_action("sheet","she*et");
  add_action("score","sc*ore");
  add_action("brief_verbose","brief");
  add_action("brief_verbose", "verbose");
  add_action("save","save");
  add_action("do_quit","quit");
  add_action("review", "review");
  add_action("examine","ex*amine");
  add_action("toggle_wimpy", "wimpy");
  add_action("monitor", "mon*itor");
  add_action("do_refresh", "refresh");
  add_action("do_retire", "retire");
  /* Nope, no more teach.. Baldrick..*/
  /*
  add_action("do_teach", "teach");
  */
} /* public_commands() */

int invent() 
  {
  write(query_living_contents(1));
  return 1;
}

int glance(string arg) 
  {
  object *ob;
  int i, dark;
  string ret;
  
  if (!environment()) {
    notify_fail("You are in limbo... sorry you can't look at anything.\n");
    return 0;
  }
  dark = check_dark((int)environment()->query_light());
  if (!arg) {
    if (this_object()->query_creator())
      write(file_name(environment())+"\n");
    if(!dark)
      ret = (string)environment()->query_contents();
    else
      ret = "";
    write((string)environment()->short(dark, 1)+ ".\n" + ret);
    return 1;
  }

  if (!sscanf(arg, "at %s", arg)) {
    notify_fail("Glance at something!\n");
    return 0;
  }

  ob = find_match(arg, ({ this_object(), environment() }) );

  if (sizeof(ob)) {
    for (i=0;i<sizeof(ob);i++)
      write(ob[i]->short(dark)+".\n");
    return 1;
  }

  notify_fail("You do not think that the "+arg+" is here.\n");
  return 0;
}

int look_me(string arg) 
  {
  object *ob;
  int i, dark;
  string ret;

  dark = check_dark((int)environment()->query_light());
  if (!arg || !stringp(arg)) {
    if (this_object()->query_creator())
      write(file_name(environment())+"\n");
    write(environment()->long(0, dark));
    this_player()->adjust_time_left(-5);
    return 1; /* blame evan */
  }

  sscanf(arg, "at %s", arg);

  ob = find_match(arg, ({ this_object(), environment() }) );
  ret = "";
  this_player()->adjust_time_left(-DEFAULT_TIME);
  if (sizeof(ob)) {
    if (pointerp(ob)) {
      for (i=0;i<sizeof(ob);i++) {
        ret += ob[i]->long(arg, dark);
        this_player()->adjust_time_left(2);
      }
    } else {
      ret += ob->long(arg, dark);
      this_player()->adjust_time_left(2);
    }
    more_string(ret, "Look");
    return 1;
  }

  notify_fail("You do not think that the "+arg+" is here.\n");
  return 0;
}

int setmin(string str) 
  {
  msgin = str;
  return 1;
  }

int setmout(string str)
  {
  msgout = str;
  return 1;
  }

int setmmin(string str)
  {
  mmsgin = str;
  return 1;
  }

int setmmout(string str)
  {
  mmsgout = str;
  return 1;
  }

int review() {
  write("Entry  : " + extract(msgin, 1) + "\n");
  write("Exit   : " + extract(msgout, 1) + "\n");
  write("MEntry : " + extract(mmsgin, 1) + "\n");
  write("MExit  : " + extract(mmsgout, 1) + "\n");
  write("Editor : " + editor + "\n");
  return 1;
}

int examine(string arg) {
  return look_me("at "+arg);
}

string short(int dark) {
  string str;

  if (!interactive(this_object()))
    str = "The net dead statue of ";
  else
    str = "";
  return str+::short(dark);
}

/*
void set_level(int i)
  {
  if(i<0) 
    i = i +(i*-2);
  if (!guild_ob)
    {
    level = i;
    }
   else
    {
    level = i;
    guild_ob->set_level(i,this_object());
    }
}
*/

/* This is my way to get rid of the stupid set_level thingie.. 
 * Baldrick. */
void adjust_level(int i)
  {
   if(i > 1)
   {
      if(interactive(this_object()))
      {
         log_file("BUSTED",(string)this_object()->query_cap_name()+" level adjusted by "+
         i+" by "+previous_object()->query_name()+" file "+
         file_name(previous_object())+"\n");
      }
   }
  if (guild_ob)
    guild_ob->new_levels(i, this_object());
  // Not sure if I need to call anything at all in the race object..
  //race_ob->new_levels;
  // This calls a recalc function in stats.c 
  level += i;
  this_object()->recalc_stats(i);
}
  
int toggle_wimpy(string str) 
  {
  if (!str) {
    notify_fail("Usage: "+query_verb()+" <num> (caution read help wimpy)\n");
    return 0;
  } else {
    if (sscanf(str, "%d", wimpy) != 1) {
      notify_fail("You must set wimpy to a number.\n");
      return 0;
    }
    if (wimpy < 0 || wimpy > 100) {
      notify_fail("Wimpy must be in the range 0-100, 0 turning wimpy off.\n");
      wimpy = 0;
      return 0;
    }
  }
  if (wimpy)
    write ("You are in wimpy mode, you will run away at "+wimpy+
           "% of your max hps.\n");
  else
    write("You are in brave mode.\n");
  return 1;
}

int brief_verbose(string str) {
  if (str == "on")
    verbose = (query_verb() == "verbose");
  else if (str == "off")
    verbose = (query_verb() == "brief");
  else if (str) {
    notify_fail("Usage: "+query_verb()+" <on/off>\n");
    return 0;
  } else
    verbose = !verbose;

  if (verbose)
    write ("You are in verbose mode.\n");
  else
    write("You are in brief mode.\n");
  return 1;
}

int sheet() 
  {
 int i;
 string info;
 info = "";

 info += "Name : "+query_cap_name()+"\n";
 info += "Race : "+query_race()+"\n";
 info += "Sex  : "+query_gender_string()+"\n";
 if(query_guild_ob())
   info += "Guild: "+query_guild_ob()->query_short()+"\n";
 else
   info += "Guild: No guild.\n";
 info += "Level: "+level+"\n";
 info += "Wimpy: "+query_wimpy()+" %\n";
 info += "Set Alignment    : "+query_playerset_alname()+"\n";
 info += "Gameset Alignment: "+query_align_name()+"\n";
 info += "Body AC modifier : "+query_body_ac()+"\n";
  /*  They dont need to know what AC equip is giving.
 info += "Equip AC modifier: "+query_equip_ac()+"\n";
 info += "Total AC    : "+query_total_ac()+"\n";
  */
 info += "To Hit AC0  : "+query_thac0()+"\n";
 info += "Strength    : "+stat_string(query_str())+"\n";
 info += "Damage bonus: "+query_damage_bonus() + "\n";
 info += "To hit bonus: "+query_tohit_bonus() + "\n";
 info += "Dexterity   : "+query_dex()+"\n";
 info += "Constitution : "+query_con()+"\n";
 info += "Con Bonus   : "+query_hp_bonus()+"\n";
 info += "Intelligence: "+query_int()+"\n";
 info += "Wisdom      : "+query_wis()+"\n";
 info += "Charisma    : "+query_cha()+"\n";
 info += "Hit Points  : "+query_hp()+" ("+query_max_hp()+")\n";
 info += "Guild Points: "+query_gp()+" ("+query_max_gp()+")\n";
 info += "Social      : "+query_social_points()+" ("+ 
                          query_max_social_points()+")\n";
 info += "Total money : "+query_value()/100+" GP\n";
 info += "Experience  : "+query_xp()+"\n";
 info += "Encumbrance : "+query_loc_weight()+" ("+query_max_weight()+")\n";

 printf("%-#*s\n", query_cols(), info);
 write("\n");
 command("spells");
 command("commands");
 return 1;
} /* int sheet */

int score(string str) 
  {
  int age, i;
  string *st;

  if (str)
    st = explode(str, " ");
  else
    st = ({ });
  if ((verbose && (member_array("brief", st) == -1)) ||
      (member_array("verbose", st) != -1)) {
    if (member_array("stats", st) != -1) {
      write("Here are some arbitrary numbers for you to look at:\n");
      printf("%-#*s\n", query_cols(), 
             "Strength     : "+stat_string(query_str())+
           "\nIntelligence : "+query_int()+
           "\nDexterity    : "+query_dex()+
           "\nConsitution  : "+query_con()+
           "\nWisdom       : "+query_wis()+"\n");
      return 1;
    }
    write("You are level "+query_level()+", "+
          "you have "+hp+"("+max_hp+") hit points, "+
          gp+"("+max_gp+") guild points and\n"+social_points+"("+
          max_social_points+") social points.\n");
    write("Your current experience is "+xp+", and you have died "+deaths+
          " times.\nYou can die "+(max_deaths-deaths)+" more times before "+
          "you are completely dead.\n");
    write("You are ");
    age = time_on - time();
    age = -age;
    if (age > 86400)
      printf("%d days, ", age/86400);
    if (age > 3600)
      printf("%d hours, ", (age/3600)%24);
    if (age > 60)
      printf("%d minutes and ", (age/60)%60);
    printf("%d seconds old.\n", age % 60);
    if (wimpy)
      write("Wimpy set to "+wimpy+"%\n");
    else
      write("You are in brave mode.\n");
    return 1;
  } else if (member_array("stats", st) != -1) {
    write("Here are some arbitrary numbers for you to look at:\n");
    printf("%-#*s\n", query_cols(), 
           "Str : "+stat_string(query_str())+
           "\nInt : "+stat_string(query_int())+
           "\nDex : "+stat_string(query_dex())+
           "\nCon : "+stat_string(query_con())+
           "\nWis : "+stat_string(query_wis())+
           "\nCha : "+stat_string(query_cha())+"\n");
    return 1;
  }
  write("Hp: "+hp+"("+max_hp+")"+"  Gp: "+gp+"("+max_gp+")"+"  Xp: "+
         xp+"\n");
  return 1;
}

nomask int save() {
  if (my_file_name == "/global/player" || query_verb() == "save")
    tell_object(this_object(), "Saving...\n");
  save_me();
  return 1; 
}

void save_me() {
  object ob;
  mixed old;

  if (query_property("guest")) {
    write("But not saving for guests... sorry.\n");
    return ;
  }
  if ((ob = present("Some Money For Me", this_object())))
    money_array = (mixed *)ob->query_money_array();
  else
    money_array = ({ });
  if (guild_ob)
    guild_ob->player_save();
  if (race_ob)
    race_ob->player_save();
  old = geteuid();
  if (environment())
    last_pos = file_name(environment());
  else
    //last_pos = "/room/start/"+query_race();
    last_pos = "/room/raceroom";
  auto_load = create_auto_load(all_inventory());
  saved_co_ords = (int *)last_pos->query_co_ord();
  time_on -= time();
  guild_joined -= time();
  // ntime_last_saved -= time();
  seteuid("Root");
  catch(save_object("/players/"+name[0..0]+"/"+name,1));
  seteuid(old);
  time_on += time();
  guild_joined += time();
  // ntime_last_saved += time();
} /* save_me() */

int do_quit() {
  object *ob, money;
  object frog, frog2;
  int i;

  if (query_loading() || query_property("loading"))
    {
    notify_fail("Still loading equipment, wait until it's finished.\n");
    return 0;
    } 
  write("Quitting.\n");
  if (sizeof(attacker_list))
    {
    write("You are in a fight, quitting will take some time.\n");
    call_out("quit", 20);
    }
   else
    quit();
  return 1;
} /* quit */



int quit()
  {
  object *ob, money;
  object frog, frog2;
  int i;
 
  if (this_object()->query_alive())
    this_object()->remove_property("dead");
  save_me();
  traverse_timed_properties();
  last_log_on = time();
  log_file("ENTER", sprintf("Exit  : %15-s %s[%d]\n", name, 
           ctime(time())+ (query_property("guest")?"(guest)":""), time()));
  catch(editor_check_do_quit());
  write("Thanks for playing see you next time.\n");
  say(query_cap_name()+" left the game.\n");
  event(users(), "inform", query_cap_name() + " left the MUD", "logon");
  LOGIN_HANDLER->player_logout(query_name());
  if (race_ob)
    catch(race_ob->player_quit(this_object()));
  if (guild_ob)
    catch(guild_ob->player_quit(this_object()));
  curses_quit();
/* get rid of the money....
 * we dont want them taking it twice now do we?
 */
  if ((money = present("Some Money For Me", this_object())))
    money->dest_me();
  frog = first_inventory(this_object());
  while (frog) {
    frog2 = next_inventory(frog);
    if (frog->query_auto_load() ||
        frog->query_static_auto_load())
      frog->dest_me();
    frog = frog2;
  }
  transfer_all_to(environment());
  ob = all_inventory(this_object());
  for (i=0;i<sizeof(ob);i++)
    ob[i]->dest_me();
  dest_me();
  return 1;
} /* quit() */
 
int query_drunk()
  {
  if (query_volume(D_ALCOHOL)>200)
    return 1;
  return 0;
  }

string query_title() { return title; }
void set_title(string str) { title = str; }

string query_extitle() { return extra_title; }
void set_extitle(string str) { extra_title = str; }

int query_deaths() { return deaths; }

/* Think we can get rid of this one..
  * Baldrick..
string query_stime() {
  if (ntime_last_saved>0)
    return ctime(ntime_last_saved);
  return ctime(-ntime_last_saved);
}*/ /* query_stime() */
 

static void set_name(string str) {
  if (name && name != "object")
    return ;
  name = str;
  set_living_name(name);
  set_main_plural(name);
} /* set_name() */

string long(string str, int dark) {
  string s;

  if (str == "soul") {
    return (string)"/obj/handlers/soul"->query_long();
  }
  if (str == "sun" || str == "moon" || str == "weather") {
    return weather_long(str);
  }
  if (this_player() != this_object())
    tell_object(this_object(), this_player()->query_cap_name()+" looks at you.\n");
  s = "You see "+query_cap_name();

  /* Nope, no guilds will be shown..
   * Baldrick. */
   /*
  if (guild_ob)
    s += " "+(string)guild_ob->query_title(this_object());
    */

  /* probably make this it's own function later.. */

if (this_object()->query_female())
    s += " the female ";
   else 
    s += " the male ";
  s += this_object()->query_race_name();

  if (extra_title)
    s += " ("+extra_title+"), \n";
  else
    s += ",\n";
  if (race_ob)
    s += (string)race_ob->query_desc(this_object());
  if (desc && desc != "")
    s += query_cap_name() + " " + desc+"\n";
  s += capitalize(query_pronoun())+" "+health_string()+".\n";
  s += calc_extra_look();
  s += weather_extra_look();
  s += query_living_contents(0);
  return s;
} /* long() */

/* second life routine... handles the player dieing. */

int second_life() 
  {
  string str;
  int i, no_dec;
  object tmp;

  make_corpse()->move(environment());
  str = query_cap_name() + " killed by ";
  if (!sizeof(attacker_list))
    str += this_player()->query_cap_name()+" (with a call)";
  else
    for (i=0;i<sizeof(attacker_list);i++)
      if (attacker_list[i]) 
       {
       str += attacker_list[i]->query_name()+"<"+geteuid(attacker_list[i])+"> ";
        attacker_list[i]->stop_fight(this_object());
        no_dec += interactive(attacker_list[i]);
       }
  log_file("DEATH", ctime(time())+": "+str + "\n");
  event(users(), "inform", str, "death");
  attacker_list = ({ });
  for (i=0;i<sizeof(call_outed);i++)
    call_outed[i]->stop_fight(this_object());
  call_outed = ({ });
  // weapon = 0;
  if (!no_dec)
    deaths++;
  if (deaths > max_deaths) {
    write("You have died too many times.  I am sorry, your name will be "+
          "inscribed in the hall of legends.\n");
    shout(this_object()->query_cap_name()+" has just completely died.  "+
          "All mourn "+(string)this_object()->query_possessive()+
          " passing.\n");
    LIBRARY->complete_death(query_name());
  }
/* oh dear complete death ;( */

  say(query_cap_name()+" dies(sigh).\n");
  save_me();
  DEATH_CHAR->person_died(query_name());
  hp = 0;
  gp = 0;
  xp = 0;
  if (!no_dec) 
    {
    contmp = -2;
    strtmp = -2;
    dextmp  = -2;
    inttmp = -2;
    wistmp = -2;
  }
  tmp = clone_object(DEATH_SHADOW);
  tmp->setup_shadow(this_object());
  return 1;
} 

void remove_ghost() 
  {
  if ((deaths > max_deaths) || ((int)this_object()->query_con() < 1)) 
    {
    if (this_player() != this_object()) 
      {
      tell_object(this_object(), this_player()->query_cap_name()+
                  " tried to raise you, but you are completely dead.\n");
      tell_object(this_player(), query_cap_name()+
                  " is completely dead, you cannot raise him.\n");
      } 
     else
      tell_object(this_object(), "You are completely dead.  You cannot "+
                  "be raised.\n");
    say(query_cap_name()+" struggles to appear in a solid form, but fails.\n");
    return ;
  }
  this_object()->remove_property("dead");
   this_object()->adjust_max_lives(1);
   if((int)this_object()->query_level() > 5)
      this_object()->adjust_con(-1);
   this_object()->set_hp(3); /* to make SURE it aint negative */
  this_object()->set_alive(1);
  tell_object(this_object(), "You reappear in a more solid form.\n");
  say(query_cap_name() + " appears in more solid form.\n");
  this_object()->dest_death_shadow();
  this_object()->save_me();
  save();
}

int query_hb_counter()
{
   return hb_counter;
}

int query_hb_diff(int oldc)
{
   if(hb_counter > oldc) return hb_counter - oldc;
   else return oldc - hb_counter;
}


static int hb_num;

/*
 * the heart beat. bounce what does this do? we arent going to tell you
 */
void heart_beat() 
  {
  int i, intox;

  flush_queue();
  intox = query_volume(D_ALCOHOL);
  hb_counter++;

  /* Added a combat_counter, so the combat aren't that quick. */
  if (drunk_heart_beat(intox) && time_left > 0 && combat_counter >= 2) 
    {
    do_spell_effects(this_object());
      attack();
      if (sizeof(attacker_list))
        time_left -= (int)environment()->attack_speed();
    combat_counter = 0;
    } /* If drunk_heart... */
   combat_counter++;

  if (!interactive(this_object()) ) 
    {
    if (name == "guest" || name == "root") 
      {
      say(query_cap_name()+" just vanished in a puff of logic.\n");
      do_quit();
      } 
     else 
      if (!net_dead) 
	{
        /* Why? this was because of equipment not saving.
         * Alas: not needed.
         * Baldrick.
         */
        say(query_cap_name()+" goes white, looks very chalky and turns into a "+
          "statue.\n");
        event(users(), "inform", query_cap_name() + " has lost " +
          query_possessive() + " link", "link-death");
        this_object()->do_quit();
        /* 
        save_me();
        for (i=0;i<sizeof(attacker_list);i++)
          attacker_list[i]->stop_fight(this_object());
        */
        net_dead = 1;
        }
    if (time() - last_command > MAX_IDLE) 
      {
      say(query_cap_name()+" has been idle for too long, "+query_pronoun()+
          " vanishes in a puff of boredom.\n");
      do_quit();
      return ;
      }
  } else {
    net_dead = 0;
    if (query_idle(this_object()) > MAX_IDLE)
      if(my_file_name != "/global/lord" && !this_object()->query_property("I don't want to idle out please")) {
        say(query_cap_name()+" has been idle for too long, "+query_pronoun()+
            " vanishes in a puff of boredom.\n");
        write("You idled out sorry.\n");
        do_quit();
        return ;
      }
    last_command = time() - query_idle(this_object());
  }

/* Hit point receival, or more accurately increase of fatigue */
/* Naaaah, can't use this, too fast. made it so that it doesent give you
 * a new HP for every heartbeat
 * Baldrick..
 */
  if ( hp_counter >= 15 )
    {
    if (hp < max_hp)
      hp++;
    if (intox<200 && gp < max_gp)
      gp++;
    hp_counter = 0;
    }
  hp_counter++; 

/* handle intoxication dispersion by our selves...
 * they just handle hp recival and sp recival...
 */
  if(headache)
    if (!--headache)
    {
      tell_object(this_object(), "Your headache disapears.\n");
      headache = 0;
    }

  if (intox) 
    {
    if (!(intox-1)) 
      {
      headache = 15;
      tell_object(this_object(),"You get a splitting headache, be happy.\n");
      hp -= 2;
      if (hp<1)
        hp = 1;
      }
    }
  if (++hb_num%4) 
    {
    social_points++;
    if(social_points > max_social_points)
      social_points = max_social_points;
    if (monitor && sizeof(attacker_list)) 
      {
      /* Hmm, the monitor costs GP, good idea..:=) */
      /* But the rest out there don't want it..
      gp--;
      if (gp>0)
      */

        write(sprintf("Hp: %d Gp: %d\n", hp, gp));
      /*
      else
        gp = 0;
      */
      }
    if (hb_num > 500)
      {
      if(max_social_points < 1000)
       max_social_points++;
      hb_num = 0;
      }
  }
  if (sizeof(attacker_list) && wimpy && hp < max_hp*wimpy/100)
    run_away();
  update_volumes();
}  /* Void heart_beat */

int monitor(string str) 
  {
  if (!str)
    monitor = !monitor;
  else if (str == "on")
    monitor = 1;
  else if (str == "off")
    monitor = 0;
  else {
    notify_fail("Syntax: monitor <on/off>\n");
    return 0;
  }
  if (monitor)
    write("Your hit point monitor is on.\n");
  else
    write("Your hit point monitor is off.\n");
  return 1;
}

void run_away() 
  {
  mixed *direcs;
  int i, bong;

  direcs = (mixed *)environment()->query_dest_dir();
  while (!bong && sizeof(direcs)) 
    {
    i = random(sizeof(direcs)/2)*2;
    bong = command(direcs[i]);
    if (!bong)
      direcs = delete(direcs, i, 2);
    else
      write("Your feet run away with you.\n");
    }
  if (!bong)
    write("You tried to run away, but no matter how much you scrabbled you "+
          "couldn't find any exits.\n");
}

/* why have invis here ? have to find out  that Baldrick. */

int set_invis(int i) 
  {
 if(!previous_object()->query_lord())
  {
  if(i)
    invis = 1;
  else 
    invis = 0;
  }
 else
  invis = i;
}

int query_invis() { return invis; }

int help_func(string str) 
  {
  string rest;
  mixed i;

  if (!str) return do_help(0);
  if (sscanf(str, "spell %s", rest) == 1) 
    {
    i = help_spell(rest);
    if (i) 
      {
      write(i);
      return 1;
      }
    notify_fail("No such spell as '"+rest+"'\n");
    return 0;
    }
  if (sscanf(str, "command %s", rest) == 1) 
    {
    i = help_command(rest);
    if (i) 
      {
      write(i);
      return 1;
      }
    notify_fail("No such command as '"+rest+"'\n");
    return 0;
    }
  i = do_help(str); /* calling /global/help.c */
  if (!i)
    if ((i = help_spell(str)))
      write(i);
  if (!i)
    if ((i = help_command(str)))
      write(i);
  if(str == "guild")
    write(query_guild_ob()->help());
  return i;
}

int query_wizard() { return creator; } /* need this for the gamed driver */
int query_app_creator() { return app_creator; }

int do_kill(string str) 
  {
  int i;
  object *obs;
 
  if (!str || str == "") 
    {
    notify_fail("Usage: kill <object>\n");
    return 0;
    }

  str = lower_case(str);

  if (str=="all" || str[0..0] == "0")
    {
    notify_fail("Sorry, not allowed.\n");
    return 0;
    }
 
  obs = find_match(str, environment());
  //obs = find_living(str, environment());
  if (!sizeof(obs)) 
    {
    notify_fail("Cannot find "+str+"\n");
    return 0;
    }

/* Notice that there is no check for living().  One can attack anything. 
 * Should have.. 
 */

  if (obs[0]==this_player())
    {
    notify_fail("Why commit suicide?\n");
    return 0;
    }

  for (i=0;i<sizeof(obs);i++)
  {
    this_object()->attack_ob(obs[i]);
    if(obs[i]->query_statue())
      log_file("LINK", ctime(time())+" "+query_cap_name()+" attacked "+
                obs[i]->query_cap_name()+".\n");
    if (interactive(obs[i]))
      log_attack(query_name(), query_level(), obs[i]->query_name(),
               obs[i]->query_level());
  }

  write("Ok.  Fight with "+str+" starts.\n");
  return 1;
}

int do_stop(string str)
  {
  write("Stopping fights, takes some time.\n");
  call_out("really_stop", 10, str);
} /* stop */
 
int really_stop(string str) 
  {
  int i;
  object *obs;

  if (!str) 
    {
    obs = attacker_list + call_outed;
    if (!sizeof(obs)) 
      {
      notify_fail("Not fighting anyone.\n");
      return 0;
      }
    for (i=0;i<sizeof(obs);i++)
      stop_fight(obs[i]);
    write("Stopped fighting "+query_multiple_short(obs)+".\n");
    return 1;
    }

  obs = find_match(str, environment());
  if (find_living(str))
   obs += ({ find_living(str) });

  if (!sizeof(obs)) 
    {
    notify_fail("Cannot find "+str+"\n");
    return 0;
    }
  for (i=0;i<sizeof(obs);i++)
    stop_fight(obs[i]);
  write("Ok, stopped hunting "+str+"\n");
  return 1;
}

/* Removed, Baldrick
int adjust_align(int i) 
  {
  if (alignment != 0)
    alignment += (i*10)/(alignment<0?-alignment:alignment);
  else
     alignment += i;
  return alignment;
  } */ /* adjust_align() */

int query_time_on() { return time_on - time(); }
/* why have a guild joined time ? Baldrick */
int query_last_joined_guild() { return guild_joined - time(); }

int check_dark(int light) 
  {
  if (race_ob)
      return (int)race_ob->query_dark(light);
   return 0;
}

int query_level() { return level; }

int restart_heart_beat() 
  {
  if(!query_heart_beat(this_object()))
    {
    set_heart_beat(1);
    write("Ok, heart_beat restarted.\n");
    return 1;
    }
  notify_fail("Didn't need to start it.\n");
  return 0;
}

void set_snoopee(object ob) { snoopee = ob; }
object query_snoopee() { return snoopee; }

int do_su(string str) {
  if (!str || str == "") {
    notify_fail("Usage: su <name>\n");
    return 0;
  }

  notify_fail("");
  clone_object("/secure/login")->do_su(str);
  return 1;
}


void set_creator(int i) {
/* who the hell is putting coment on this ???
   Next time I'll dest the sucker for good when I find out.. 
   Baldrick..*/
  if (file_name(previous_object()) != "/secure/master") {
    write("Illegal attempt to set creator!\n");
    log_file("ILLEGAL", this_player(1)+" Illegal attempt to set_creator "+
             "at "+ctime(time())+" from "+file_name(previous_object())+"\n");
  }
  write("You are now a creator.\n");
  creator = i;
  app_creator = i;
  home_dir = "/w/"+name;
  save_me();
}

int query_prevent_shadow(object ob) {
  if (function_exists("query_prevent_shadow", ob) ||
      function_exists("query_name", ob) ||
      function_exists("query_creator", ob) ||
      function_exists("query_app_creator", ob) ||
      function_exists("query_hidden", ob) ||
      function_exists("dest_me", ob) ||
      function_exists("save_me",ob))
    return 1;
  return 0;
}

int query_max_deaths() { return max_deaths; }
void set_max_deaths(int i) { max_deaths = i; }
int adjust_max_deaths(int i) { return (max_deaths += i); }

/* Including new hack for parse_command ;) */
move(object dest, string msgin, string msgout) {
  int i;
  object env;

  if ((env = environment()))
    WEATHER->unnotify_me(environment());
  i = ::move(dest, msgin, msgout);
  if (environment())
    WEATHER->notify_me(environment());
  if (!i)
    me_moveing(env);
  return i;
}

static int do_refresh(string str) 
  {
  if (!str || str != "me") {
    notify_fail("Please read the docs before using this command.\n");
    return 0;
  }
  write("WARNING!  Make sure you have read the docs before doing this!\n\n"+
        "Are you sure you wish to refresh yourself? ");
  input_to("refresh2");
  return 1;
}

static int refresh2(string str) {
  str = lower_case(str);
  if (str[0] != 'n' && str[0] != 'y') {
    write("Pardon?  I do not understand.  Do you want to refresh yourself? ");
    input_to("refresh2");
    return 1;
  }
  if (str[0] == 'n') {
    write("Ok, not refreshing.\n");
    return 1;
  }
  write("Doing refresh.\n");
  if (query_property("dead"))
    {
    remove_property("dead");
    this_object()->dest_death_shadow();
    }
  /* Removing the guildchannel */
  remove_property("chan_" + guild_ob->query_name());
  level = 0;
  Str = 10;
  Con = 10;
  Int = 10;
  Wis = 10;
  Dex = 10;
  Cha = 10;
  set_max_hp(random(3));
  set_max_gp(1);
  inttmp = dextmp = wistmp = strtmp = contmp = 0;
  guild_ob = 0;
  skills = ({ });
  spells = ({ });
  known_commands = ({"skills", "consider", "bury", }); 
  languages = ({});        /* this too */
  spheres = ({ });
  guild_ob = 0;
  xp = 0;
  deaths = 0;
  max_deaths = 10;
  level_cache = ([ ]);
  bonus_cache = ([ ]);
  gr_commands = ([ ]);
  race_guild_commands();
  remove_property("stats_rearranged");
  // Hmmm, maybe not use a catch.. 
  //"/obj/handlers/bank_handler"->refresh_account(this_object()->query_name());
  move("/room/raceroom");
  command("look");
  write("Done.\n");
  reset_all();
  reset_bon_stats();
  say(query_cap_name()+" refreshes "+query_objective()+"self.\n");
  return 1;
}

/* for creators who are playing as players */
int query_creator_playing() { return creator; }

int query_max_languages() 
{
  return (query_int()/3);
}

int teach_language(object *obs, string str)
{
  int nb, i;
  object *taught;

  taught = ({ });
  if(member_array(str, query_languages()) == -1)
    return 0;
  nb = sizeof(obs);
  if(!nb)
    return 1;
  for(i=0;i<nb;++i)
  {
    if(!living(obs[i]))
      continue;
    if(member_array(str, (string *)obs[i]->query_languages()) != -1)
    {
      write(obs[i]->query_cap_name()+" knows "+str+" already.\n");
      continue;
    }
    if(obs[i]->query_max_languages()<=
       sizeof((string *)obs[i]->query_languages()))
    {
      write(obs[i]->query_cap_name()+" can't learn more languages.\n");
      tell_object(obs[i], query_short()+" tries to teach you '"+str+"', "+
        "but you aren't intelligent enough to learn another language.\n");
      continue;
    }
    taught += ({ obs[i] });
  }
  nb = sizeof(taught);
  if(!nb) 
    return 1;
  for(i=0;i<nb;i++) 
  { 
    taught[i]->add_language(str);
    write("You teach "+taught[i]->query_short()+" '"+str+"'.\n");
  }
  return 1;
} /* teach_language */

string query_object_type()
  {
  if (creator)
    return "A"; 
  return " ";
} /* query_object_type() */

int do_whoami() {
  write(query_name()+"\n");
  return 1;
} /* do_whoami() */

int query_statue() { return !interactive(this_object()); }


/* Add of Retire.
 * Baldrick, march '94
 */
int do_retire() 
  {
  // should probably do a more secure check, but the retire has a password.
 "/secure/master"->try_retire();
  return 1;
  } /* void do_retire */

// Coded the 5th of may 1994 by Begosh@RotD
// Receiver for the chat


void receive_message( string str, string class)
{
    strlen( class ) ? receive( sprintf("%s%*=-s\n", class,
            cols-strlen(class), str) ) : receive( str );
} /* recieve_message */


/* This is an attempt to make it illegal to set_short on playerobjects.
 * Baldrick, aug '94
 */

void set_short(string moo)
  {
  if (living(previous_object()))
    {
    tell_object(previous_object(), "Boo! Not legal anymore.\n");
    return;
    }
  ::set_short(moo);
}
