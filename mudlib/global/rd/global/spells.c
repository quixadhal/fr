// /global/spells.c

// 19 Jun 95 Laggard    made spells take entire round to cast

#include "commands.h"
#include "spells.h"

/* This is a global variable :=)  */

mixed spells;
int spell_attack(string name, mixed base, mixed hit, mixed dam,
    string type, object me, object him, int percent);

int setup_spell(object me);
int add_spell_attack(string name, mixed base, mixed hit,
   mixed dam, string type, object me);
int remove_spell_attack(string name, object me);
int finish_spell(object me);
/* here is the start on the new spells.c i will try to make
    Baldrick, started july '93
*/
void create() {
  spells = ([ ]);
}

void spell_commands() {
  add_action("show_spells", "spells");
  add_action("cast", "cast");
  /* this is a reset of the spellarray,the players will have tolearn again..
    * Baldrick. sept '93 */
  add_action("reset_spellarray", "reset_spells");
}

/*  If you have a function help() in the spell itself.  It will print the
 *  string you return there. 
 */
string help_spell(string str) 
{
  if (!mappingp(spells))
   spells = ([ ]);
  if (!m_sizeof(spells))
    return 0;
  if (!spells[str])
    return 0;
  /* Since I have removed the /std/spells from the spellaray
  * do I have to put it here..Baldrick sept '93 */
  return ((string)("/std/spells"+spells[str][S_OBJECT])->help(str));
}
 
/*
 * Lists spells you know
 */
int show_spells(string str) {
  string *frog;
  int i;

  if (!mappingp(spells))
   spells = ([ ]);
  if (!m_sizeof(spells)) {
    write("You don't know any spells yet.\n");
    return 1;
  }

  frog = m_indices(spells);
  write("You know the following spells:\n");
  printf("%#-*s\n", this_player()->query_cols(), implode(frog, "\n"));
  return 1;
}

/* Will cast the spell after a round of casting time */
int cast(string str) {
  int i, j;
  string *s,s1;
 
  if (!str) {
    notify_fail("Usage: cast <spell> [<target>]\n");
    return 0;
  }
  s = explode(str, " ");
  
  s1 = s[0];
  j = 1;
  while (!spells[s1] && j < sizeof(s))
    s1 = implode(s[0..j++], " ");
  if (!spells[s1]) {
    notify_fail("You don't know any "+str+" spell.\n");
    return 0;
  }

  // spells take the rest of a round to cast {Laggard}
  // prevents aliased chains of spellcasting from happening too fast
  this_player()->adjust_time_left(DEFAULT_TIME-ROUND_TIME);

/* ok we found our spell...
 * cast it...
 * Or, at least try to ;)
 */
/* This is the original spell call..
 return (int)call_other(spells[s1][S_OBJECT], spells[s1][S_FUNC],
                                    implode(s[j..sizeof(s)], " "));
*/
/* This is the version I will try out. : */
/* the "cast_spell" will be replaced with S_FUNC (defined as "cast_spell" in 
   spell.h. This will hopefully reduce the memory required to the spell list 
   (need only spell object (/std/spells/+++) and the spell name (for the caster
   to use when he casts.
*/
/* out with this one...
  return (int)call_other(spells[s1][S_OBJECT], "cast_spell",
                                     implode(s[j..sizeof(s)], " "));
..*/
/* The one above was the first try to redice the mmory the player ob uses.
 * This one will reduce it even more. I have made a SPELL_ROOT instead of
 * having the whole path to the spellcode. 
 * Still Baldrick. sept '93 */

  return (int)call_other(SPELL_ROOT + spells[s1][S_OBJECT], "cast_spell",
                           implode(s[j..sizeof(s)], " "));
}

mixed query_spells() { return spells; }

/* this will have to get the mixed func removed to get anything out of the change in cast_spell */

int add_spell(string name, mixed ob) {
  int i;
  mapping tmp;

  if (pointerp(spells)) {
    tmp = ([ ]);
    for (i=0;i<sizeof(spells);i+=2)
      tmp[spells[i]] = spells[i+1];
    spells = tmp;
  }
  if (!mappingp(spells))
    spells = ([ ]);
  spells[name] = ({ ob });
  return 1;
}

int remove_spell(string name) {
  int i;

  spells = m_delete(spells, name);
  return 1;
}

int reset_spellarray() 
  {
  spells = ([]);
  write ("Bing.\n");
  return 1;
  }

int query_spell(string type) {
  if (!mappingp(spells)) return 0;
  return spells[type];
}

/*  Dunno if you want a teaching person to teach spells.  Oh well, here's
 * the code
 */
/* I don't want it, Baldrick */
/* But I need to take it out from other places too.. */
/* done
int spell_teach(object *obs, string spell) {
  int i;
  object *succ, *me_low, *him_low;
  string ret;

  if (!mappingp(spells)) spells = ([ ]);
  if (!spells[spell])
    return 0;
  succ = me_low = him_low = ({ });
  for (i=0;i<sizeof(obs);i++) {
    if (!living(obs[i]))
      continue;
    switch (spells[spell][0]->teach(obs[i], spell)) {
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
  if (!succ) {
    ret = "";
    if (sizeof(me_low))
      ret += "You are too low a level to teach "+query_multiple_short(obs)+
             " "+spell+".\n";
    if (sizeof(him_low))
      ret += query_multiple_short(obs)+" is too low a level to learn "+
             spell+".\n";
    write(ret);
    return 1;
  }
  write("You successfuly teach "+query_multiple_short(succ)+" "+spell+".\n");
  if (sizeof(me_low))
    write("You are to low a level to teach "+query_multiple_short(obs-succ)+
           " "+spell+".\n");
  if (sizeof(him_low))
    write(query_multiple_short(obs)+" is too low a level to learn "+
          spell+".\n");
  return 1;
}
*/
