// /global/guild_race.c
// Modified set_guild_ob() to call the guild_handler, to track
// what guilds the players are in. Dyraen, Sept '95 

#include "commands.h"
#include "guild.h"
//#include "player.h"


int guild_joined;
string race_ob, guild_ob,  *known_commands;
static mapping gr_commands;

void race_guild_commands() {
  int i;
  string *bing;
  mapping tmp;

if ((string)this_player()->query_name() == "asmodean")
{
   write("TO = "+file_name(this_object())+"\n");
    write("PO = "+file_name(previous_object())+"\n");
   write("GO = "+(this_player()->query_guild_ob()?(string)this_player()->query_guild_ob():"NONE")+"\n");
   write("RO = "+(this_player()->query_race_ob()?(string)this_player()->query_race_ob():"NONE")+"\n");
}
if(previous_object())
{
   if (file_name(previous_object())[0..12] == "/secure/login")
      catch(race_ob->start_player(this_object()));
}

  if (!known_commands)
    known_commands = ({ "skills" });
/*
  if (!mappingp(gr_commands))
    gr_commands = (mapping)"/std/commands"->query_commands();
*/
  add_action("list_commands", "co*mmands");
  add_action("add_new_command", "Add_New_Command");
  if (guild_ob)
    catch(guild_ob->start_player(this_object()));
/* this have to get out.. the guild_join calls this function every time a player join a guild.. it gives him new bonus stats each time...
  catch(race_ob->start_player(this_object()));
  Baldrick.. aug '93 */
  gr_commands = ([ ]);
  for (i=0;i<sizeof(known_commands);i++) {
    gr_commands[known_commands[i]] = (string *)
                    COMMAND_SERVER->query_command(known_commands[i]);
    if (!pointerp(gr_commands[known_commands[i]]))
      continue;
    add_action("do_race_command", known_commands[i]);
  }
   /* add_action("do_teach","t*each"); */
} /* race_guild_commands() */

int do_race_command(string str) {
  object ob;
  string s;
  int i;
 
  if (!pointerp(gr_commands[query_verb()]))
    return 0;
 
  s = gr_commands[query_verb()][0];
  if(!(ob = find_object(s))) {
    catch(s->FORCE_LOAD());
    ob = find_object(s);
  }
 
  if(!ob) {
    notify_fail("Error loading command.\n");
    return 0;
  }
        
  if(ob->query_clone_me())
    ob = clone_object(s);
 
  return (int)call_other(ob,gr_commands[query_verb()][1],str);
} /* do_race_command() */

string query_gtitle() {
  string str;

  if (guild_ob)
    if (catch((str = (string)guild_ob->query_title(this_object()))))
      return "Has a broken guild";
    else
      return str;
} /* query_gtitle() */

/*
 * the set functions should not be called indisciminately...
 * becareful when using them that you dont screw up a character ok?
 */
void set_race_ob(string str) {
  string frog;
  if(sscanf(str, "/%s", frog)==1) 
    str = extract(str, 1);
  if (str[0..strlen("std/races")-1]!="std/races") {
    write("Illegal path to set_race_ob.\n");
    return;
  }
  if( (str == "std/races/demigod") &&
      (!"/secure/master"->high_programmer(geteuid())) ) {
    write("The heavens rumble and the earth shakes. You stop.\n");
    return;
  }
  if(str[0..strlen("std/races/god")-1] == "std/races/god" &&
     !"/secure/master"->god(geteuid())) {
    write("The heavens rumble and the earth shakes. You stop.\n");
  }
  else
    /* Have to put the racoal stat modifyer here.. and also do a stat demodifye
        Baldrick. aug'93 */
    /* maybe not... we'll see..
    this_object()->set_bonus_str(0);
    this_object()->set_bonus_con(0);
    this_object()->set_bonus_int(0);
    this_object()->set_bonus_wis(0);
    this_object()->set_bonus_dex(0);
    catch (race_ob->start_player(this_object()));
    */
    race_ob = str;
} /* set_race_ob() */

string query_race_ob() { return race_ob; }

void set_guild_ob(string str) {
  guild_ob = str;
  guild_joined = time();
  if (interactive(this_object()))
    GUILD_HANDLER->set_guild(this_object()->query_name(),
                             guild_ob?guild_ob->query_name():0);
} /* set_guild_ob() */

string query_guild_ob() { return guild_ob; }

string query_race() { /* should return the name of our race */
  return (string)race_ob->query_name();
} /* query_race() */

mapping query_gr_commands() { return gr_commands+([ ]); }

string help_command(string str) {
  if (!pointerp(gr_commands[str]))
    return 0;
  return (string)gr_commands[str][0]->help(str);
} /* help_command() */

int list_commands() {
  write("Your current commands are:\n"+sprintf("%-#*s\n",
        this_player()->query_cols(), implode(m_indices(gr_commands), "\n")));
  return 1;
} /* list_command() */

string *query_known_commands() { return known_commands+({ }); }

static int allowed_add;

int add_known_command(string str) {
  mixed tmp;

  if (member_array(str, known_commands) != -1)
    return 0;
  tmp = (mixed)COMMAND_SERVER->query_command(str);
  if (!pointerp(tmp))
    return 0;
  known_commands += ({ str });
  gr_commands[str] = tmp;
  allowed_add = 1;
  this_object()->ignore_from_history("Add_New_Command "+str);
  command("Add_New_Command "+str);
  allowed_add = 0;
  return 1;
} /* add_known_command() */

int remove_known_command(string str) {
  int i;

  if ((i = member_array(str, known_commands)) == -1)
    return 0;
  known_commands = delete(known_commands, i, 1);
  gr_commands = m_delete(gr_commands, str);
  return 1;
} /* remove_known_command() */

int add_new_command(string str) {
  if (!allowed_add)
    return 0;
  add_action("do_race_command", str);
  return 1;
} /* add_new_command() */

int command_teach(object *obs, string comm) {
  string person, ret;
  object *succ, *me_low, *him_low;
  int i;

  if (member_array(comm, known_commands) == -1 ||
      !pointerp(gr_commands[comm]))
    return 0;
  succ = ({ });
  me_low = him_low = ({ });
  for (i=0;i<sizeof(obs);i++) {
    if (!living(obs[i]))
      continue;
    switch (gr_commands[comm][0]->teach(obs[i], comm)) {
      case 1 :
        succ += ({ obs[i] });
        break;
      case -1 :
        me_low += ({ obs[i] });
        break;
      case -2 :
        him_low += ({ obs[i] });
        break;
    }
  }
  if (!succ || !sizeof(succ)) {
    ret = "";
    if (sizeof(me_low))
      ret += "You are too low a level to teach "+query_multiple_short(obs)+
             " "+comm+".\n";
    if (sizeof(him_low))
      ret += query_multiple_short(obs)+" is too low a level to learn "+
             comm+".\n";
    write(ret);
    return 1;
  }
  write("You successfuly teach "+query_multiple_short(succ)+" "+comm+".\n");
  say(this_player()->query_cap_name()+" teaches some commands to "+
      query_multiple_short(succ)+".\n", succ);
  if (sizeof(me_low))
    write("You are to low a level to teach "+query_multiple_short(obs-succ)+
           " "+comm+".\n");
  if (sizeof(him_low))
    write(query_multiple_short(obs)+" is too low a level to learn "+
          comm+".\n");
  for (i=0;i<sizeof(succ);i++)
    tell_object(succ[i], this_player()->query_cap_name()+" teaches "+
               query_multiple_short(succ[0..i-1]+succ[i+1..1000]+ ({ "you" }))+
               " the command "+comm+".\n");
  return 1;
} /* command_teach() */
