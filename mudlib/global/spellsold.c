#include "spells.h"

mixed spells;
mixed spheres; // Also used by schools.
//object guild;
//string spell_dir;

/* here is the start on the new spells.c i will try to make
    Baldrick, started july '93
*/
void create() 
  {
  spells = ([ ]);
  spheres = ({ });
  //guild = this_player()->query_guild_ob();
  }
  
  /*
void init_spells()
  {
  spell_dir = guild->query_spell_directory();
}
*/

void spell_commands() 
  {
  add_action("show_spells", "spells");
  add_action("show_spheres", "spheres");
  add_action("show_schools", "schools");
  add_action("cast", "cast");
  /* this is a reset of the spellarray,the players will have tolearn again..
    * Baldrick. sept '93 */
  //add_action("reset_spellarray", "reset_spells");
}

/*  If you have a function help() in the spell itself.  It will print the
 *  string you return there. 
 */
string help_spell(string str) 
{
  object guild;
  string spell_dir;

  if (!mappingp(spells))
   spells = ([ ]);
  if(!m_sizeof(spells))
    return 0;
  if (!spells[str])
    return 0;
  guild = this_player()->query_guild_ob();
  spell_dir = guild->query_spell_directory();

  /* Since I have removed the /std/spells from the spellaray
  * do I have to put it here..Baldrick sept '93 */
  return ((string)(spell_dir+spells[str][S_OBJECT])->help(str));
}
 
/*
 * Lists spells you know
 */
int show_spells(string str) 
  {
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
int cast(string str) 
  {
  int i, j;
  string *s,s1;
  object guild;
  string spell_dir;
 
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
/* ok we found our spell...
 * cast it...
 * Or, at least try to ;)
 */
/* the Spell_dir is used to reduce space in the spellarray */
  guild = this_player()->query_guild_ob();
  spell_dir = guild->query_spell_directory();
  return (int)call_other(spell_dir + spells[s1][S_OBJECT], "cast_spell",
                           implode(s[j..sizeof(s)], " "));
}

mixed query_spells() { return spells; }

int add_spell(string name, mixed ob) 
  {
  int i;
  mapping tmp;

  if (pointerp(spells)) 
    {
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

int remove_spell(string name) 
  {
  spells = m_delete(spells, name);
  return 1;
}

int reset_spellarray() 
  {
  spells = ([ ]);
  // write ("Bing.\n");
  return 1;
  }

int query_spell(string type) 
  {
  if (!mappingp(spells)) return 0;
  return spells[type];
  }

/* the sphere code.. added by Baldrick october '93 to use by 
 * add_spell code in the guilds..*
 */

int add_sphere(string name)
  {
  if (!pointerp(spheres))
    spheres = ({ });
  spheres += ({name,});
  return 1;
  }

int add_spheres(mixed list)
  {
  if (!pointerp(spheres))
    spheres = ({ });
  spheres += list;
  return 1;
  }

/*
int remove_sphere(string name)
  {
  spheres = m_delete(spheres, name);
  return 1;
  }
*/

int reset_spheres()
  {
  spheres = ({ });
  return 1;
  }

mixed query_spheres() {return spheres;} 

mixed query_sphere(string name)
  {
  int tin;

  if (tin = member_array(name, spheres) != -1)
    return 1;
  return 0;
  }

int show_spheres()
  {
  object guild;
  guild = this_player()->query_guild_ob();

  if ((!guild) || ((string)guild->query_spell_directory()!=CLERIC_ROOT))
    {
    notify_fail("You don't need spheres.\n");
    return 0;
    }
  if (!sizeof(spheres))
    {
    write("You are sphereless.\n");
    return 0;
    }
  write("You have these spheres:\n");
  printf ("%-#*s\n", this_player()->query_cols(),
    implode(spheres, "\n"));
  return 1;
  } /* int show spheres..*/
 
int show_schools()
  { 
  object guild;
  guild = this_player()->query_guild_ob();

  if ((string)guild->query_spell_directory()!=MAGE_ROOT)
    {
    notify_fail("You dont need schools.\n");
    return 0;
    }
  if (!sizeof(spheres))
    {
    notify_fail("You don't belong to any schools.");
    return 0;
    }
    write("You have these schools:\n");
    printf ("%-#*s\n", this_player()->query_cols(),
     implode(spheres, "\n"));
    return 1;
} /* int show schools..*/


/*** damage and resistance routine for different damage types ***/
/*** added by Eerevann 2-11-94 ***/

int spell_damage(string target, int damage, string type)
{
  int resistance;
  int damage_taken;
  int damage_resisted;
  int resist_value;

  resistance = target->query_property(type);
           
  write("Resistance Value % : "+resistance+"\n");

   /** queries a property that returns a value between 0-100
       this value is the percentage that the damage will be 
       reduced ***/

  resist_value = 100-resistance;

  damage_taken = ((damage * resist_value)/100);
  damage_resisted = (damage - damage_taken);

  write("Damage Taken: "+damage_taken+"  Damage Resisted:  "+damage_resisted+"\n");
  
  target->adjust_hp(-damage_taken);
  return 1;
}

