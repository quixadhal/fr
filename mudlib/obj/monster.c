/* Taniwha 1995, levels for players and monsters for "remember by name" */
#define MIN_PLAYER_LEVEL 5
#define MIN_MONSTER_LEVEL 10

/* Monster.c
 * Will change the AC system, right now it's not in use, using base ac 10.
 * and eventual dex bonus in living/stats..
 * Baldrick.
 * The set base thingie is in it's own file.. the builders can choose to use
 * That instead of coding all by themselves..
 *
 */

inherit "/std/living/handle";
inherit "/std/living/mon_actions";
inherit "/std/living/living.c";
inherit "/global/communicate";
inherit "/global/drunk";
inherit "/global/guild-race";
inherit "/global/spells";
#define MONSTER_HAND "/obj/handlers/monster_handler"
#define MOVE_DEFAULT ({ 300, 300 })

#define SOUL_OBJECT "/obj/handlers/soul"
/* You'll speed things quite a bit by removing ALL mentioning of a soul-object
 * for monsters.  Of course then they can't do soul commands.  You decide.
 */
/* Maybe smart, and use load_a_chat for eventual souls.. */
int hb_counter;

mixed *chat_string,
      *achat_string,
      *attack_spells;

/* if non-0 will record player names, else won't */
int p_memory;
string *p_attack_list; // Taniwha 1995, remember the names

mixed move_after,
      *throw_out;

mixed talk_string;

int chat_chance,
    attack_everyone,
    aggressive,
    follow_speed,
    join_fights,
    protecting,
    // alignment,
    achat_chance,
    level,
    body_ac,
    move_when,
    move_time,heartheal,
    combat_counter;


string race,
       class,
       *move_zones,
       *protect,
       *enter_commands,
       join_fight_mess;
static mixed *doing_story;
static object last_attacked;

int query_concentrate_valid() { return 1; }

// For NPC's remember the man who shot my paw ;) Taniwha 1995
void attack_by(object ob)
{
   if( p_memory && interactive(ob) && (ob->query_level() > MIN_PLAYER_LEVEL) )
   {
      if( member_array(ob->query_name(),p_attack_list) == -1)
      {
         p_attack_list += ({ (string)ob->query_name() });
      }
   }
    ::attack_by(ob);
}
int player_memory(int i)
{
   p_memory = i;
   return p_memory;
}
int query_player_memory() { return p_memory; }

string *query_p_attacker_list()
{
   return p_attack_list;
}
void remove_p_attack_list() { p_attack_list = ({ }); }


int check_props(string prop) /*for spell/ guild attack blocks */
{
   int v;
   v = this_object()->query_property(prop);
   if( v == 0) v = environment(this_object())->query_property(prop);
   return v;
}
int check_anyone_here();
void set_random_stats(int low, int high);
void do_move_after(int bing);
mixed query_attack_spells();

void create()
  {
  reset_get();
  join_fights = 0;
   join_fight_mess = "Hiyaaaa!";
  protecting = 0;
  body_ac = 0;
  set_gender(random(3));  // if no gender set, it's random.
  race_ob = "/std/races/unknown";
  languages = ({ "common" });   //Added by Wonderflug, july 95
  cur_lang = "common";
  follow_speed = 3;
  add_property("determinate", "");
  add_property("npc",1);
  p_attack_list = ({ });
  talk_string = ({ });
  doing_story = ({ ({ }), ({ }) });
  chat_string = ({ 0, ({ }) });
  achat_string = ({ 0, ({ }) });
  move_zones = ({ });
  protect = ({ });
  attack_spells = ({ });
  enter_commands = ({ });
  gr_commands = ([ ]);
  known_commands = ({ });
  enable_commands();
  living_commands();
  handle_commands();
  spell_commands();
  communicate_commands();
  add_action("soul_commqz", "*");
  add_property("npc",1);
  add_action("init_race", "init_race"); /* this is used to get the
                                          * this_player set right */
  // add_action("do_teach", "teach");
  //why this here?...
  set_random_stats(8,17);
  set_max_hp(2);
  set_thac0(22);
  combat_counter=1;
  mon_actions::create();
  living::create();
  spells::create();
  /* it wasn't here, not sure if it should at all...
   * Baldrick, june '94
   */
  ::create();
} /* create() */

int query_cols() { return 200; }

/* This can be masked to get more limbs.. */
int query_limbs()
  {
  return 2;
} /* int query_limbs */

int soul_commqz(string str)
  {
  string verb, bit;

  if (sscanf(str, "%s %s", verb, bit) == 2)
    return (int)SOUL_OBJECT->soul_command(verb, bit);
  return (int)SOUL_OBJECT->soul_command(str, "");
} /* soul_commqz() */

int soul_com_force(string str) {
  string str1,str2;

  if (file_name(previous_object()) != SOUL_OBJECT)
    return 0;
  command(str);
  return 1;
  if (sscanf(str, "%s %s", str1, str2) != 2)
    str1 = str;
  SOUL_OBJECT->soul_command(str1, str2);
} /* soul_com_force() */

void set_name(string n)
  {
  if (name && name != "object")
    return;
  name = n;
  add_plural(pluralize(name));
  set_short(capitalize(name));
  set_long("You see nothing special.\n");
  set_living_name(n);
} /* set_name() */

string long(string str, int dark)
  {
  string s;

  s = query_long();
  s += capitalize(query_pronoun())+" "+health_string()+".\n";
  s += calc_extra_look();
  s += query_living_contents(0);
  return s;
} /* long() */

int set_race(string str)
  {
  race = str;
   add_alias(str);
  return 1;
} /* set_race() */

string query_race() { return race; }
string query_class() { return class; }
string query_guild() { return class; }

int set_class(string str) {
  class = str;
} /* set_class() */

int set_guild(string str) {
  class = str;
} /* set_guild() */

void init_command(string str) {
  call_out("do_command", 0, str);
} /* init_command() */

void init_equip() {
  call_out("do_equip", 0);
} /* init_equip() */

void init_race() {
  race_guild_commands();
} /* init_race() */

int do_command(string str) {
  if (stringp(str))
    return command(str);
  else
    printf("Invalid paramater to do_command %O in monster %O, env %O.\n", str,
           this_object(), environment());
} /* do_command() */

void do_aggressive_check(object ob)
{
  if ( ob->query_invis() )  return;
  switch( aggressive )
  {
   case 1:
    if ( !interactive(ob) ) return;
   case 2:
    if ( (int)ob->query_hide_shadow() < ( level>10 ? level : 5 ) )
      attack_ob(ob);
    else return;
    break;
   case 3:
    if ( !interactive(ob) ) return;
   case 4..10000:
    attack_ob(ob);
    break;
   default:
    break;
  }  /* switch( aggressive ) */
}   /* do_aggressive_check */

void init()
{
  if(!query_heart_beat(this_object()))
  {
    if (check_anyone_here() || sizeof(query_attacker_list()))
    {
      set_heart_beat(1);
    }
  }
  else
  heartheal++;
  ::init();
} /* init() */

void event_enter(object ob, string mess, object from)
{
  // Taniwha 1995, I remember you you bastard, you attacked me then logged off
   if(interactive(ob) && member_array(ob->query_name(),p_attack_list) != -1)
   {
      attack_by(ob);
      return;
   }
  if (aggressive)
    do_aggressive_check(ob);
} /* void event_enter */

int check_anyone_here()
{
  object *arr;
  int i;

  if (!environment())
    return 1;
  arr = all_inventory(environment());
  for (i=0;i<sizeof(arr);i++)
    if (interactive(arr[i]) && arr[i] != this_object())
      return 1;
  return 0;
}

void set_attack_everyone(int i) { attack_everyone = i; }
int query_attack_everyone() { return attack_everyone; }

void set_move_after(int after, int rand)
{
  move_after = ({after, rand });
}

void set_throw_out(int hps, int chance, string their_mess,
                   string everyone_mess) {
  throw_out = ({ hps, chance, their_mess, everyone_mess });
} /* set_throw_out() */

int *query_throw_out() { return throw_out; }

varargs void run_away(int bing) {
  do_move_after(bing+1);
} /* run_away() */

/*  This is the FR way of giving AC instead of add_ac(bla bla bla)
 * If you want different AC for different attacks, tell me, OK.
 * This way is easier and far faster, but of course less flexible.
 */
/* Hmm, body_ac here... */

int query_body_ac() {return body_ac; }

/* I don't like set_ac ..  could break monsies.. let's keep it
 * here for now, it's not used anyway.
 * Wish I knew my own comments after making them.. Baldy..
 */
void set_ac(int i) { body_ac = i; }

string expand_string(string in_str, object on, object attacker)
{
  string *str, ret;
  int q, i, j, add_dollar;

   int k,l;


  object liv, *obs, ob;

//  tell_room(environment(this_object()),"["+in_str+"]\n",({ }));
  str = explode(in_str, "$");
  ret = "";
  for (i=0;i<sizeof(str);i++)
  switch (str[i][0])
  {
  case 'm' :
    ob = this_object();
  case 'l' :
    if (!ob)
    {
      if (!liv)
      {
        obs = all_inventory(environment(this_object()));
        k = sizeof(obs);
        l = random(k);
        for(j = 0; j < k; j++)
        {
           if(living(obs[l]) && obs[l] != this_object())
           {
              liv = obs[l];
              break;
           }
           l++;
           l%= k;
        }
      }
      if (!liv)  /* No one here to see us blow up anyway ;) */
      break;
      ob = liv;
   }
   case 'a' :
   if (!ob)
   {
     if(!sizeof(attacker_list))
     break;
     if (!attacker)
        attacker = attacker_list[random(sizeof(attacker_list))];
     ob = attacker;
   }
   case 'o' :
   if (!ob)
   {
     if(!on)
     {
        obs = all_inventory(environment());
        k = sizeof(obs);
        l = random(k);
        ob = this_object(); /* should all else fail */
        for(j = 0; j < k; j++)
        {
            if ( obs[l] != this_object())
            {
                on = obs[l];
                break;
            }
            l++;
            l%= k;
        }
      }
      ob = on;
   }
   switch (str[i][1..1000])
   {
   case "name" :
      ret += (string)ob->query_name();
      add_dollar = 0;
   break;
   case "cname" :
      ret += (string)ob->query_cap_name();
      add_dollar = 0;
   break;
   case "gender" :
     ret += (string)ob->query_gender_string();
     add_dollar = 0;
   break;
   case "poss" :
     ret += (string)ob->query_possessive();
     add_dollar = 0;
   break;
   case "obj" :
     ret += (string)ob->query_objective();
     add_dollar = 0;
   break;
     case "gtitle" :
     ret += (string)ob->query_gender_title();
     add_dollar = 0;
   break;
   case "pronoun" :
     ret += (string)ob->query_pronoun();
     add_dollar = 0;
   break;
   default :
     if (add_dollar)
        ret += "$";
     ret += str[i];
     add_dollar = 1;
   break;
   }
   ob = 0;
   break;
   default :
      if (add_dollar)
        ret += "$";
      ret += str[i];
      add_dollar = 1;
      ob = 0;
   break;
   }
   if(!strlen(ret)) return "looks confused for a moment, pauses, and continues ";
   if (ret[strlen(ret)-1] == '$')
      return ret[0..strlen(ret)-2];
   return ret;
}

void expand_mon_string(string str) {
  if (!stringp(str)) return;
  switch (str[0]) {
    case ':' :
      say(this_object()->query_cap_name()+" "+
            expand_string(str[1..1000],0,0)+"\n");
      break;
    case '\'' :
    case '"' :
      command(expand_string(str,0,0));
      break;
    case '@' :
      command(expand_string(str[1..10000],0,0));
      break;
    default :
      say(expand_string(str,0,0)+"\n");
      break;
  }
}

int query_hb_counter() { return hb_counter; }
int query_hb_diff(int oldv)
{
   if(hb_counter > oldv) return (hb_counter - oldv);
   else return (oldv - hb_counter);
}

/* More heart_beat stuff, removing pieces from void heart_beat to make the
 * function less complex.
 * First go is the start and stop of heartbeats.
 * Baldrick, march '95
 */

int check_heart_beat()
{
  /* First, ze grose check upon if it will be stopped:
   * It's so big I will part it up.. might make it look as ugly as
   * before.
   */

  if (hp == max_hp && gp == max_gp)
    {
    if (!sizeof(query_attacker_list()))
      if (!check_anyone_here() && !sizeof(query_effects()))
      {
        set_heart_beat(0);
      }
    } /* if hp */
} /* int check heart_beat */
static string *story;
static int which_story;
void chatter(int chance, mixed chat)
{
   int i,j;
// tell_room(environment(this_object()),"chat check !\n");
    if(! sizeof(chat) ) return;
    if (sizeof(story) )
    {
      if(which_story < sizeof(story))
      {
         expand_mon_string(story[which_story++]);
      }
      else
      {
         story = 0;
         which_story = 0;
      }
    }
    else if( random(1000) < chance )
    {
      i = random(chat[0]+1);
    j=0;
      while ((i-= chat[1][j]) >0)
        j += 2;
      if (pointerp(chat[1][j+1]))
      {
        story = chat[1][j+1];
      } /* if(pointerp.. */
      else expand_mon_string(chat[1][j+1]);
   } /* else if(sizeof(doing... */
}
/* This is as ugly as it was when it was in heart_beat.
 * But, should be able to clean it up?
 * Baldrick march '95
 */
void combat_heart_beat()
{
  int i, j, k;
  string spell_target;

    switch(combat_counter)
    {
    case 1:
    do_spell_effects(this_object());
  if (!sizeof(attack_spells))
  break;
    i = random(sizeof(attack_spells)/3);
    i *= 3;
    if (random(100) < attack_spells[i] )
    {
      if (attack_spells[i+2][2] == 1)
      {
        spell_target = "";
        for (k=0;k<(sizeof(attacker_list)-1);k++)
          spell_target += attacker_list[k]->query_name()+",";
          spell_target += attacker_list[sizeof(attacker_list)-1]->query_name();
      }
      else if ( attack_spells[i+2][2] == 2 )
         spell_target = "all";
      else if ( attack_spells[i+2][2] == 3 )
         spell_target = this_object()->query_name();
      else spell_target =
         attacker_list[random(sizeof(attacker_list))]->query_name();
      if ( attack_spells[i+2][2] == 4 && this_object()->check_props("noguild") )
      break;
      else if ( this_object()->check_props("nocast") )
      break;
      call_other(attack_spells[i+2][0], attack_spells[i+2][1],
                spell_target,
                this_object()   );
   }
   break;
   case 2:
    /* end of the attack spell thingie */
   if (throw_out)
     for (i=0;i<sizeof(attacker_list);i++)
        if (attacker_list[i] && attacker_list[i]->query_hp() < throw_out[0] &&
            environment(attacker_list[i]) == environment() &&
            random(100) < throw_out[1])
          {
          if (throw_out[2])
            tell_object(attacker_list[i], expand_string(throw_out[2],
                           0, attacker_list[i]));
          if (throw_out[3])
            say(expand_string(throw_out[3], 0, attacker_list[i]),
                     attacker_list[i]);
          attacker_list[i]->run_away(1);
          } /* if (attacker_list */
    //break;
    default:
      chatter(achat_chance,achat_string);
      combat_counter=0;
    break;
   }

  if ((max_hp*wimpy/100) > hp && hp > 0) run_away();

  //++combat_counter;
  return;
} /* combat heart beat */

/* Does the move after thingie called in heart_beat
 */
void move_after_heart_beat()
{
  /* first, a way to randomize the moveing.. */
  if (!move_when)
  {
    move_when = (move_after[0] + random(move_after[1]));
    move_time = 0;
  } /* if (!move_when */

  /* if it's time to move, do it.. */
  if (move_time == move_when)
  {
    do_move_after(0); //probably change that number.. random ?
  } /* if move_time==  */
  else
  {
    move_time++;
  } /* else if move_timre... */
  return;
} /* void move_after */

/* This code is *ugly* and it has to be possible to make it cleaner and faster!
 * Hrmf..
 * Well, actually done that now, moved a lot of the stuff in it to their
 * own funtions (right above), they are as ugly as before, but it looks a bit
 * cleaner.
 * Baldrick. march '95
 */
void heart_beat()
  {
  object ob;
  int i, j;

  adjust_hp(heartheal, this_object());
  adjust_gp(2);
  heartheal = 0;
  ++combat_counter;
  hb_counter++;

  /* This is the attack part.
   * it runs when the monsie is in fight.
   */
  if (sizeof(attacker_list))
  {
    combat_heart_beat();
  } /* if(sizeof.. */
  else
  {
     chatter(chat_chance,chat_string);
  } /* else if.. */

  remove_property("done follow");

  if (drunk_heart_beat(query_volume(0)) && combat_counter>=1)
    attack();

  if (move_after && !sizeof(attacker_list))
  {
    move_after_heart_beat();
  }  /* if (move_after) */

  /* Wonder what this one is?
   * Baldrick.
   */
  catch(race_ob->monster_heart_beat(race, class, race_ob, guild_ob));

  /* This will start and stop the heartbeats dependant on a lot of
   * variables. this is to lessen the cpu.
   */
  check_heart_beat();

} /* void heart_beat */

int rand_num(int low, int max)
{
  return random(max-low)+low+1;
}

void set_random_stats(int low, int max) {
  set_str(rand_num(low, max));
  set_dex(rand_num(low, max));
  set_int(rand_num(low, max));
  set_con(rand_num(low, max));
  set_wis(rand_num(low, max));
  set_cha(rand_num(low, max));
}

/* How many levels do we have? this is a mess.
 * Gonna get rid of these...
 * June '94; not many left, this one is needed.
 * Baldrick..
 */
void set_level(int i)
{
  object guildobject;
  int e, step;

   if(i > MIN_MONSTER_LEVEL) p_memory = 1;
  if (i < 1) i = 1;
  level = i;
  recalc_stats(i);
  set_hp(query_max_hp(),  this_object());
  /* This set's the THAC0 routine.
   * maybe I should put it somewhere else?
   * Baldrick, june '94
   */
  if (guildobject = query_guild_ob())
    step = guildobject->query_thac0_step();
   else
    step = 3;
  // wonder if it works...
  this_object()->adjust_thac0(  -(i / step) );

  /* why this now? not sure.. */
  init_command("init_race");
}

int give_money(int base, int rand, string type) {
  if (!type)
    type = "copper";
  return adjust_money(base+random(rand), type);
}

void load_chat(int chance, string *c_s)
  {
  int i;
  for (i=0;i<sizeof(c_s);i+=2)
  {
      chat_string[1] += ({ c_s[i], c_s[i+1] });
      chat_string[0] += c_s[i];
  } /* for.. */
  chat_chance = chance;
}

void set_chat_chance(int i) { chat_chance = i; }
int query_chat_chance() { return chat_chance; }
void set_chat_string(string *chat) { chat_string = chat; }
string *query_chat_string() { return chat_string; }

void add_chat_string(mixed weight, mixed chat)
{
  int i;

  if (pointerp(weight))
    for (i=0;i<sizeof(weight);i+=2)
      add_chat_string(weight[i], weight[i+1]);
  else
    if (member_array(chat, chat_string[1]) == -1) {
      chat_string[1] += ({ weight, chat });
      chat_string[0] += weight;
    }
}

void remove_chat_string(mixed chat)
  {
  int i;

  if (pointerp(chat))
    for (i=0;i<sizeof(chat);i++)
      remove_chat_string(chat[i]);
  else
    if ((i = member_array(chat, chat_string[1])) != -1) {
      chat_string[0] -= chat_string[1][i-1];
      chat_string[1] = delete(chat_string[1], i-1, 2);
    }
}

void load_a_chat(int chance, string *c_s) {
  int i;
  for (i=0;i<sizeof(c_s);i+=2) {
    achat_string[1] += ({ c_s[i], c_s[i+1] });
    achat_string[0] += c_s[i];
  }
  achat_chance = chance;
}

void set_achat_chance(int i) { achat_chance = i; }
int query_achat_chance() { return achat_chance; }
void set_achat_string(string *chat) { achat_string = chat; }
string *query_achat_string() { return achat_string; }

void add_achat_string(mixed weight, mixed chat)
  {
  int i;

  if (pointerp(weight))
    for (i=0;i<sizeof(weight);i+=2)
      add_achat_string(weight[i], weight[i+1]);
  else
    if (member_array(chat, achat_string[1]) == -1) {
      achat_string[1] += ({ chat });
      achat_string[0] += weight;
    }
}


void remove_achat_string(mixed chat) 
  {
  int i;
 
  if (pointerp(chat))
    for (i=0;i<sizeof(chat);i++)
      remove_achat_string(chat[i]);
  else
    if ((i = member_array(chat, achat_string[1])) != -1) {
      achat_string[0] -= achat_string[1][i-1];
      achat_string[1] = delete(achat_string[1], i-1, 1);
    }
}

void add_move_zone(mixed zone) 
  {
  int i;

  if (pointerp(zone))
    for (i=0;i<sizeof(zone);i++)
      add_move_zone(zone[i]);
  else if (member_array(zone, move_zones) != -1)
    return;
  else
    move_zones += ({ zone });
  if (!move_after)
    set_move_after(MOVE_DEFAULT[0], MOVE_DEFAULT[1]);
}

void set_move_zones(string *zones) 
  {
  int i;

  for (i=0;i<sizeof(zones);i++)
    add_move_zone(zones[i]);
}

void remove_move_zone(mixed zone) 
  {
  int i;

  if (pointerp(zone))
    for (i=0;i<sizeof(zone);i++)
      remove_move_zone(zone[i]);
  else {
    if ((i=member_array(zone, move_zones)) == -1)
      return ;
    move_zones = delete(move_zones, i, 1);
  }
}

string *query_move_zones() { return move_zones; } 

void add_protect(mixed shield) {
  int i;

  if (pointerp(shield))
    for (i=0;i<sizeof(shield);i++)
      add_protect(shield[i]);
  else if (member_array(shield, protect) != -1)
    return;
  else
    protect += ({ shield });
}

void set_protect(string *shields) {
  int i;

  for (i=0;i<sizeof(shields);i++)
    add_protect(shields[i]);
}

void remove_protect(mixed shield) 
{
  int i;
  
  if(pointerp(shield))
    for(i=0;i<sizeof(shield);i++)
      remove_protect(shield[i]);
  else 
  {
   if((i=member_array(shield, protect)) == -1)
     return;
   protect = delete(protect, i, 1);
  }
}

string *query_protect() { return protect; }

mixed query_move_after() { return move_after; }

int add_enter_commands(mixed str) {
  if (stringp(str))
    enter_commands += ({ str });
  else if (pointerp(str))
    enter_commands += str;
  return 1;
}

string *query_enter_commands() { return enter_commands; }

int reset_enter_commands() {
  enter_commands = ({ });
}

move_player(string dir, string dest, mixed message, object followee,
                mixed enter) {
  int i, j;

  i = ::move_player(dir, dest, message, followee, enter);
  if (i) {
    for (j=0;j<sizeof(enter_commands);j++)
      init_command(enter_commands[j]);
    return i;
  }
  return 0;
}

void do_move_after(int bing) 
  {
  mixed *direcs;
  int i, bong;
  string zone;

  direcs = (string *)environment()->query_dest_dir();
  while (!bong && sizeof(direcs)) 
    {
    i = random(sizeof(direcs)/2)*2;
    bong = 0;
    if (bing > 1)
      catch(bong = (int)direcs[i+1]->query_property("no throw out"));
    catch(zone = (string)direcs[i+1]->query_zone());
    if (sizeof(move_zones) || bong)
      if (bong || member_array(zone, move_zones) == -1) 
	{
        direcs = delete(direcs, i, 2);
        continue;
        } /* if (bong */
    bong = command(direcs[i]);
    if (!bong)
      direcs = delete(direcs, i, 2);
    } /* while */
} /* do_move_after() */
 
void set_talk_string(mixed arr) { talk_string = arr; }
mixed query_talk_string() { return talk_string; }

void add_talk_string(string cat, mixed do_this) {
  talk_string += ({ cat, do_this });
}

void remove_talk_string(string cat) {
  int i;
 
  if ((i=member_array(cat, talk_string)) == -1)
    return ;
  talk_string = delete(talk_string, i, 2);
}

int in_talk;
 
void catch_talk(string str) {
  string s1, s2;
  int i;

  if (in_talk)
    return ;

  in_talk = 1;
  for (i=0;i<sizeof(talk_string);i+=2)
    if (sscanf(str, "%s"+talk_string[i]+"%s", s1, s2))
      if (stringp(talk_string[i+1]))
        call_other(this_object(), talk_string[i+1], str, s1, s2);
      else if (pointerp(talk_string[i+1]))
        call_other(talk_string[i+1][0], talk_string[i+1][1], str, s1, s2);
  in_talk = 0;
}

void event_fight_in_progress(object me, object him) 
  {
  if (!me || !him)
    return ;
  if (him == this_object() || me == this_object())
    return ;
  if (join_fights) {
    if (member_array(me, attacker_list) == -1 &&
        member_array(him, attacker_list) == -1)
      say(join_fight_mess);
    attack_by(me);
    attack_by(him);
  }

  if(sizeof(protect) &! protecting)
  {
   if(member_array(him->query_name(), protect) != -1)
   {
    say(capitalize(query_short())+" protects "+
        him->query_short()+".\n");
    attack_ob(me);
    protecting = 1;
   }
   if(member_array(me->query_name(), protect) != -1)
   {
    say(capitalize(query_short())+" jumps into the fray to protect "+
        me->query_short()+".\n");
    attack_ob(him);
    protecting = 1;
   }
  }
}

void set_join_fight_mess(string str) { join_fight_mess = str; }
void set_join_fights() { join_fights = 1; }

query_join_fight_mess() { return join_fight_mess; }
query_join_fights() { return join_fights; }

void set_al(int i) { alignment = i; }
int query_al() { return alignment; }
int query_align() { return alignment; }
void set_align(int i) { alignment = i; }
void set_alignment(int i) { alignment = i; }
int query_alignment() { return alignment; }

void event_exit(object me, string mess, mixed ob) 
  {
  mixed *bing;
  int i;
  string zone;

  if (!move_after) /* we dont move :( */
    return ;
/* follow the suckers. */
  if (member_array(me, attacker_list) != -1) {
    bing = (mixed *)environment()->query_dest_dir();
    if ((i = member_array(ob, bing)) == -1) {
      if (!objectp(ob))
        ob = find_object(ob); /* arhghh must have teleported... scums. */
      else
        ob = file_name(ob);
      if ((i = member_array(ob, bing)) == -1)
        return ; /* lost cause */
    }
    zone = (string)ob->query_move_zone();
    if (move_zones && sizeof(move_zones))
      if (member_array(zone, move_zones) == -1) {
        return ; /* If we are suppose to wander in move_zones.. dont go
                  * where we are not supposed to... get stuck */
    }
    remove_call_out("do_follow_move");
    call_out("do_follow_move", 2+random(follow_speed), bing[i-1]);
  }
}

void do_follow_move(string dir) {
  command(dir);
}

/* Here we have what the players and immorts are whining about..
 * can understand it tho, it won't work yet..:=)
 * Maybe fix it?
 * Baldrick, oct '94
 */
int add_attack_spell(int chance, string name, mixed obj) 
  {
  int i;

  if ((i=member_array(name, attack_spells)) == -1)
    attack_spells += ({ chance, name, obj  });
   else 
    {
    attack_spells[i-1] = chance;
    attack_spells[i+1] = obj;
    }
  return 1;
}

int remove_attack_spell(string name) 
  {
  int i;

  if ((i=member_array(name, attack_spells)) == -1)
    return 0;
  attack_spells = delete(attack_spells, i-1, 3);
  return 1;
}

mixed query_attack_spells() { return attack_spells; }

mixed query_race_ob() { return race_ob; }
void set_race_ob(mixed r) { race_ob = r; }

mixed query_guild_ob() { return guild_ob; }
void set_guild_ob(mixed g) { guild_ob = g; }
int query_follow_speed() { return follow_speed; }
void set_follow_speed(int f) { follow_speed = f; }

int query_aggressive() { return aggressive; }
void set_aggressive(int a) { aggressive = a; }

int query_level() {
  return level;
}

/* Teach here ? not now.
 * Baldrick.
int do_teach(string str) {
  string bing;
  object *obs;

  notify_fail("Syntax: teach <spell/command> to <person>\n");
  if (!str || str == "")
    return 0;
  if (sscanf(str, "%s to %s", str, bing) != 2)
    return 0;
  obs = find_match(bing, environment());
  if (!sizeof(obs)) {
    notify_fail("You must teach someone.\n");
    return 0;
  }
  if (!command_teach(obs, str) && !spell_teach(obs, str) &&
      !teach_skill(obs, str)) {
    notify_fail("You do not know the spell or command "+str+".\n");
    return 0;
  }
  return 1;
}
*/

mixed *stats() 
  {
  mixed *zone,
        *shield;
  int i;

  zone = ({ });
  shield = ({ });
  for (i=0;i<sizeof(move_zones);i++)
    zone += ({ ({ "Move zone "+i, move_zones[i] }) });
  for (i=0;i<sizeof(protect);i++)
    shield += ({ ({ "Protect "+i, protect[i] }) });
  if (!query_move_after())
     return ::stats() + ({
        ({ "guild", query_guild() }),
        ({ "guild ob", query_guild_ob() }),
        ({ "race", query_race() }),
        ({ "race ob", query_race_ob() }),
        ({ "join_fights", query_join_fight_mess() }),
        ({ "follow speed", query_follow_speed() }),
        ({ "level", level }),
        ({ "chat chance", query_chat_chance() }),
        ({ "achat chance", query_achat_chance() }),
        ({ "alignment", query_al() }),
         ({ "aggressive", query_aggressive() }),
    }) + zone + shield;
   return ::stats() + ({
      ({ "race", query_race() }),
      ({ "race ob", query_race_ob() }),
      ({ "guild", query_guild() }),
      ({ "guild ob", query_guild_ob() }),
      ({ "ac", body_ac }),
      ({ "follow_speed", query_follow_speed() }),
      ({ "level", level }),
      ({ "chat chance", query_chat_chance() }),
      ({ "achat chance", query_achat_chance() }),
      ({ "alignment", query_al() }),
      ({ "aggressive", query_aggressive() }),
      ({ "move after-fix", query_move_after()[0] }),
      ({ "move after-rand", query_move_after()[1] }),
   }) + zone + shield;
}

string expand_nickname(string str) { return str; }
