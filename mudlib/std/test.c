inherit "/std/object";
inherit "/std/basic/cute_look";
#include "skills.h"
#include "commands.h"
#include "tune.h"

string *commands;
mixed spells;
int heal_loop;

void create() {
  commands = ({ });
  spells = ({ });
  ::create();
}

int add_command(string name, int add_if_player) {
  if (member_array(name, commands) != -1)
    return 0;
  commands += ({ name, ({ add_if_player }) });
  return 1;
}

int remove_command(string name) {
  int i;

  if ((i = member_array(name, commands)) == -1)
    return 0;
  commands = delete(commands, i, 1);
  return 1;
}

int do_command(string name, mixed param) {
  mixed *tmp;

  if (member_array(name, commands))
    return 0;
  tmp = (mixed *)COMMAND_SERVER->query_command(name);
  return (int)call_other(tmp[0], tmp[1], param);
}

int add_spell(string name, object ob, string func_name, int add_if_player) {
  int i;

  if ((i = member_array(name, spells)) != -1)
    return 0;
  spells += ({ name, ({ ob, func_name, add_if_player }), });
  return 1;
}

int remove_spell(string name) {
  int i;

  if ((i= member_array(name, spells)) == -1)
    return 0;
  spells = delete(spells, i, 2);
  return 1;
}

int cast_spell(string name, mixed bing) {
  int i;

  if ((i=member_array(name, spells)) == -1)
    return 0;
  return (int)call_other(spells[i+1][0], spells[i+1][1], bing);
}

mixed query_spells() { return spells; }

string *query_commands() { return commands; }

int query_skill_cost(string skill) { return 0; }

/*  Simply how much money the guild will charge to train you  */
int query_advance_cost() { return DEFAULT_COST; }

/* Seems we won't use this one, but check *bits of skills instead */
int query_xp_cost() { return DEFAULT_XP_COST; }
int query_max_level() { return 300; }

/*  Instead of the titles we've been using so far we might want to just
 * let the guild titles consist of <level> <guild>.  At least this will be
 * the standard.  If that's not acceptable, just mask this function.
 */
string query_title(object player) 
{
  int lvl;
  lvl = player->query_level();
  return "the "+number_as_place(lvl)+" level "+query_short();
}

/*
 * cant think of anything I want to do here at the moment...
 * This is where you would set up any shadows you want on the player
 * object (for instance kits/specializations).  The only thing we'll
 * do here in the inheritable guild is to add known commands and spells
 * for monsters (who'll more often have commands and spells than a guild
 * who'll give it to them.
 */
void start_player(object pl) {
  int i;
  if (!spells)
    spells = ({ });

  for (i=0;i<sizeof(spells);i+=2)
    if (spells[i+1][2] || !interactive(pl))
      pl->add_spell(spells[i], spells[i+1][0], spells[i+1][1]);
  if (!pointerp(commands))
    commands = ({ });
  for (i=0;i<sizeof(commands);i+=2)
    if (commands[i+1][0] || !interactive(pl))
      pl->add_known_command(commands[i]);
}

/* Just some jumbo bumbo I'm playing with  Ducky.
void set_level(int lvl)
{
   string name;
   name = this_player()->query_name();
   write_file("/players/"+name[0..0]+"/"+name+".o",
              "level "+lvl+"\n");
   level = lvl;
}
*/

/* Not something players should be able to do until we add dual class humans.
 * Up until then we leave the function open so that lords can call it
 * instead of set_guild_ob() which they often seem to bungle.
 * We will stop removing spells when dual class is implemented
 */
void leave_guild() {
  int i;

  for (i=0;i<sizeof(spells);i+=2)
    this_player()->remove_spell(spells[i]);
}

/* Class is not actually needed, but is put in so that one easier can add
 * specializations-objects and send their path as a description in case they
 * affect level advancement.
 */
void set_level(object ob, int lvl, string class) {
  call_out("set_new_level", 0, ({ ob, lvl, class }) );
}

/*  Just what's supposed to happen when you advance in level */
void set_new_level(mixed *arr) 
{
  object ob;
  int lvl;

  ob = arr[0];
  lvl = arr[1];

/*I've set it up for letting the player have all the skills on the skill-list*/
/* Figured we'd be better of not showing skills on the skill-list itself if  */
/* He's not allowed to train in a certain skill.                             */
  ob->add_skill_level("level", lvl);
  ob->add_skill_level("str", lvl);
  ob->add_skill_level("dex", lvl);
  ob->add_skill_level("con", lvl);
  ob->add_skill_level("wis", lvl);
  ob->add_skill_level("int", lvl);
  ob->add_skill_level("cha", lvl);
/* In the separate guilds you might want to put some code here to let the 
 * guild-members raise in some stats at higher levels.  Such as in strength
 * for fighters and wisdon for clerics.  This may or may not be covered by
 * the skills system however.
 */
  
/* If we want to reset hp, gp or sp when we increase in level, we might do it
 * here like most muds.  However I haven't done this since I see no good reason
 * why you should be fully heaed because you raise in level
 */
  ob->reset_all();
}

int query_level(object ob) {
  return (int)ob->query_skill("level");
}
