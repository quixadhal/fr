inherit "/std/basic/light";
inherit "/std/basic/property";
inherit "/std/basic/cute_look";
inherit "/std/basic/extra_look";
inherit "/std/basic/desc";
inherit "/std/senses";
#include "room.h"
#include "door.h"
 
string query_dirs_string();
#define ROOM_HAND "/obj/handlers/room_handler"
#define STD_ORDERS ({\
"north", ({ -1, 0, 0 }), "south", ({ 1, 0, 0 }), "east", ({ 0, -1, 0 }),\
"west", ({ 0, 1, 0 }), "up", ({ 0, 0, -1 }), "down", ({ 0, 0, 1 }),\
"northeast", ({ -1, -1, 0 }), "northwest", ({ -1, 1, 0 }),\
"southwest", ({ 1, 1, 0 }), "southeast", ({ 1, -1, 0 }), })
#define SHORTEN ([\
"north":"n", "south":"s", "west":"w", "east":"e", "northeast":"ne",\
"northwest":"nw", "southeast":"se", "southwest":"sw", "up":"u",\
"down":"d" ])

static mapping items,
               door_control;
static string exit_string,
       short_exit_string,
       room_zone,
         *exit_type,*exit_material,
         *dig_exit,*dig_where,
         *lock_str,*lock_dir,
         *all_locks,
       dark_mess,
       *dest_direc,
       *aliases;
static mixed  *dest_other;
static int *co_ord;
static object *destables,
              *hidden_objects;

string query_short_exit_string();
 
int test_add(object ob, int flag) { return 1; }
int test_remove(object ob, int flag) { return 1; }
int add_weight(int n) { return 1; }
 
int *query_co_ord() { return co_ord; }
void set_co_ord(int *new) { co_ord = new; }
void shield_it(string str, string waitpunk) {
   object porter;
 porter = this_player();
if (str == "players") {
if(this_player()->query_creator()) {
     write("You feel a small pulse of magic as you pass through"+
            " a magical shield.\n");
 return;
}
else
{
        waitpunk->force_load();
        this_player()->move(waitpunk);
        write("You are not powerful to breach the magical shield which"+
        " protects your destination.\n"+
        "The magical shield bounces you to another location.\n");
    }
}
if (str == "creators") {
if(this_player()->query_lord()) {
    write("You feel a unnerving pulse of magic as you pass through"+
            " a magical shield.\n");
return;
}
else
{
        waitpunk->force_load();
        this_player()->move(waitpunk);
        write("Devoe appears before you.\n"+
         "Devoe smiles at you.\n"+
         "Devoe says: I am sorry m'lord, only higher immortals may pass the"+
         "magical shield that protects this area.\n"+
         "Devoe opens a rift in time and steps through.\n"+
        "The magical shield bounces you to another location.\n");
    }
}
if (str == "demigods") {
if(this_player()->query_god()) {
    write("You feel a large pulse of magic as you pass through"+
            " a magical shield.\n");
 return;
}
else
{
        waitpunk->force_load();
        this_player()->move(waitpunk);
        write("This is a magically protected area.  This shield should of"+
                " been placed by: "+
                " Bivins, Ducky, or Dank.  Only gods may pass here.\n"+
                "The magical shield bounces you to another location.\n");
    }
}
} 
/* shield_it func doesnt really work fully. but am working on it -biv */
 
 
string query_dark_mess(int lvl)
{ 
 switch(lvl)
 {
    default:
      return "Hmmph, odd, " + dark_mess;
    case 1: /* Total blackout */
      return dark_mess;
    case 2: /* pretty damn dark */
      return "You can't see much.\n"+ query_dirs_string();
    case 3: /* getting dim */
      return "It's hard to see in this gloom.\n"+ ::short(1)+"\n" + query_dirs_string();
    case 4: /* slightly dazzled */
      return "You are dazzled by the light.\n"+ ::short(0)+"\n"+ query_dirs_string();
    case 5: /* very bright */
      return "The light is painfully bright.\n"+ query_dirs_string();
    case 6:
     return "You are too blinded by the light to see properly.";
  }
}

void set_dark_mess(string str) { dark_mess = str; }
 
void create() {
  dest_other = ({ });
   dig_exit =({ });
   dig_where = ({ });
   exit_material = ({ });
   all_locks = ({ });
  dest_direc = ({ });
   exit_type = ({ });
   lock_str = ({ });
   lock_dir = ({ });
  items = ([ ]);
  aliases = ({ });
  destables = ({ });
  hidden_objects = ({ });
  door_control = ([ ]);
  room_zone = "nowhere";
  seteuid((string)"/secure/master"->creator_file(file_name(this_object())));
  set_dark_mess("It is too dark to see");
  property::create();
  extra_look::create();
  senses::create();
  add_property("location", "inside");
  this_object()->setup();
  this_object()->reset();
} /* create() */
 
string expand_alias(string str);

string short(int dark) {
  if (dark)
    return ::short(1);
  if(query_verb() == "glance")
    return ::short(0) + query_short_exit_string();
  else
    return ::short(0);
} /* short() */
 
int id(string str) {
  int i;

  return 0;
  str = expand_alias(str);
  return items[str];
} /* id() */
 
string expand_alias(string str) {
  int i;
 
  if (!aliases)
    return str;
 
  if ((i=member_array(str,aliases))==-1)
    return str;
 
  if (i%2)
    return aliases[i-1];
  return str;
} /* expand_alias() */
 
/*
 * Yes folks. This creates that really stupid obvious exits message you keep
 * getting. Hope you really hate it.
 * specialy changed to handle stupid things. If you can figure it out I
/** will shake your hand. Look for docs coming soon to a universe near you.
 */
string query_dirs_string() {
  string ret, *dirs;
  int no, i, nostore;
 
  if (!dest_direc || sizeof(dest_direc)==0)
    dest_direc = ({ });
  dirs = ({ });
  for (i=0;i<sizeof(dest_other);i+=2)
    if (dest_other[i+1][ROOM_OBV]) {
      no += 1;
      dirs += ({ dest_other[i] });
    } else if (stringp(dest_other[i+1][ROOM_OBV])) {
      nostore = 1;
      if (call_other(this_object(),dest_other[i+1][ROOM_OBV]))
        dirs += ({ dest_other[i] });
    } else if (pointerp(dest_other[i+1][ROOM_OBV])) {
      nostore = 1;
      if (call_other(dest_other[i+1][ROOM_OBV][0],dest_other[i+1][ROOM_OBV][1]))
        dirs += ({ dest_other[i] });
    }
  if (sizeof(dirs)==0) {
    if (nostore)
      return "%^GREEN%^There are no obvious exits.%^RESET%^";
    exit_string = "%^GREEN%^There are no obvious exits.%^RESET%^";
    return exit_string;
  }
  if (sizeof(dirs)==1) {
    if (nostore)
      return "%^GREEN%^There is one obvious exit: "+dirs[0]+".%^RESET%^";
    exit_string = "%^GREEN%^There is one obvious exit: "+dirs[0]+".%^RESET%^";
    return exit_string;
  }
  ret = " and "+dirs[sizeof(dirs)-1]+".";
  dirs = delete(dirs,sizeof(dirs)-1, 1);
  if (nostore)
    return "%^GREEN%^There are "+query_num(sizeof(dirs)+1, 0)+
           " obvious exits : "+implode(dirs,", ")+ret+"%^RESET%^";
  exit_string = "%^GREEN%^There are "+query_num(sizeof(dirs)+1, 0)+
                " obvious exits : "+implode(dirs,", ")+ret+"%^RESET%^";
  return exit_string;
} /* query_dirs_string() */

/*
 * This creates the exits message you keep getting
 */
string query_short_exit_string() {
  string ret, *dirs;
  int no, i, nostore, add;

  if (short_exit_string) 
    return short_exit_string;
  if (!dest_direc || sizeof(dest_direc)==0)
    dest_direc = ({ });
  dirs = ({ });
  for (i=0;i<sizeof(dest_other);i+=2) {
    add = 0;
    if (dest_other[i+1][ROOM_OBV]) {
      no += 1;
      add = 1;
    } else if (stringp(dest_other[i+1][ROOM_OBV])) {
      nostore = 1;
      add = (int)call_other(this_object(),dest_other[i+1][ROOM_OBV]);
    } else if (pointerp(dest_other[i+1][ROOM_OBV])) {
      nostore = 1;
      add = (int)call_other(dest_other[i+1][ROOM_OBV][0],dest_other[i+1][ROOM_OBV][1]);
    }
    if (!add)
      continue;
    if ((ret=SHORTEN[dest_other[i]]))
      dirs += ({ ret });
    else
      dirs += ({ dest_other[i] });
  }
  if (sizeof(dirs)==0) {
    if (nostore)
      return " %^GREEN%^[none]%^RESET%^";
    return short_exit_string = " %^GREEN%^[none]%^RESET%^";
  }
  if (nostore)
    return " %^GREEN%^["+implode(dirs,",")+"]%^RESET%^";
  return short_exit_string  = " %^GREEN%^["+implode(dirs,",")+"]%^RESET%^";
} /* query_short_exit_string() */
 
string long(string str, int dark) {
  int i;
  string ret,s;
 
  if (dark)
    return query_dark_mess(dark)+"\n";
  if (!str) {
    ret = "";
    ret += query_long();
    s = calc_extra_look();
    if (s && s!="")
      ret += s;
    if (!exit_string)
      s = query_dirs_string();
    else
      s = exit_string;
    ret += s + "\n";
    return ret+query_contents("");
  }
  str = expand_alias(str);
  return items[str];
} /* long() */
 
void calc_co_ord() {
  int *old_co_ord, i, j, k;
 
  for (i=0;i<sizeof(dest_other) && !co_ord;i+=2)
    if (find_object(dest_other[i+1][ROOM_DEST]))
    if (!catch((old_co_ord = (int *)dest_other[i+1][ROOM_DEST]->query_co_ord())))
      if (old_co_ord) {
        co_ord = old_co_ord + ({ });
        if ((j=member_array(dest_other[i], STD_ORDERS)) != -1)
          for (k=0;k<3;k++)
            co_ord[k] += STD_ORDERS[j+1][k];
      }
  /* Set a default later -- Hamlet */
  if(!co_ord)
    call_out("default_calc_co_ord",0);
} /* calc_co_ord() */

void default_calc_co_ord() {
/* Defaults are a good thing. -- Hamlet */
  if(!co_ord)
    co_ord = ({ 0, 0, 0 });
}
 
void init() {
  int i, j;
  mapping done;


add_action("do_dig","dig");
  if (!dest_direc)
    return 0;

  done = ([ ]); 
  for (i=0;i<sizeof(dest_direc);i++) {
    if (!done[dest_direc[i]])
      add_action("do_exit_command", dest_direc[i]);
    done[dest_direc[i]] = 1;
    if ((j=member_array(dest_direc[i], aliases)) != -1) {
      string *al;
      al = aliases;
      
      do {
        if (!(j%2)) {
         if (!done[al[j+1]]) {
          add_action("do_exit_command", al[j+1]);
          done[al[j+1]] = 1;
         }
        } else
          j++;
        al = al[j+2..sizeof(al)];
      } while ((j=member_array(dest_direc[i], al)) != -1);
    }
  }
  add_action("do_search", "search");
  if (!pointerp(co_ord))
    calc_co_ord();
  for (i=0;i<sizeof(hidden_objects);i++)
    if (hidden_objects[i])
      hidden_objects[i]->init();
    else {
      hidden_objects = delete(hidden_objects, i, 1);
      i--;
    }
  senses::init();
} /* init() */
 
/*
 * not particularly useful.
 * But here just the same, great for debugging purposes.
 */
string *query_direc() { return dest_direc; }
 
/*
 * It IS useful to get directions+where they go to
 * BTW this is not a frog.
 */
mixed *query_dest_dir() {
  int i;
  string *retval;
 
  retval = ({ });
  for (i=0;i<sizeof(dest_other);i+=2)
    retval += ({ dest_other[i], dest_other[i+1][ROOM_DEST] });
  return  retval;
} /* query_dest_dir() */
 
mixed *query_dest_other() { return dest_other; }
 
void set_zone(string str) {
  room_zone = str;
} /* set_zone() */
 
string query_zone() {
  return room_zone;
} /* query_zone() */

/*
 * this function puts the directions into the thingy list
 * I am sure you know what I mean 
 */
string expand_direc(string str) {
  string s1,s2;
 
  if (sscanf(str,"%s %s",s1,s2)==2)
    return s1;
  return str;
} /* expand_direc() */
 
/* ok.... I am going to rewrite the add_exit, modify_exit and
 * remove_exit code.... I hope you dont mind.
 */

 
//  New add_exit more strings!!!!   Piper 3/6/95

varargs int add_exit(string direc,mixed dest,string type,
                          string material)
{
   mixed *stuff;
   int i;

   if(!exit_type||sizeof(exit_type) == 0)
     exit_type = ({ });
   exit_type += ({ type });

   if(!material)
      material = "normal";

   if(!exit_material||sizeof(exit_material) == 0)
      exit_material = ({ });
   exit_material += ({ material });

   if(!dest_other)
      dest_other = ({ });

   if(member_array(direc, dest_other) != -1)
     return(0);

   stuff = ({dest}) +ROOM_HAND->query_exit_type(type,direc);
   dest_other += ({ direc, stuff});
   dest_direc += ({expand_direc(direc) });
   exit_string = 0;
   short_exit_string = 0;
   if((stuff = (mixed)ROOM_HAND->query_door_type(type,direc,dest)))
   {
      door_control[direc] = ({ clone_object(DOOR_OBJECT) });
      door_control[direc][0]->setup_door(direc,this_object(),dest,stuff);
      hidden_objects += ({door_control[direc][0] });
      door_control[dest] = direc;
   }
   return(1);
}
 
//  Query for the exit_type.. only the type...  **Piper**
string *query_ex_type(string direc)
{
   return exit_type;
}

// Query for the exit material **Piper**

string *query_exit_material(string direc)
{
   return exit_material;
}

//  This is the best thing I can think of doing that would be simple
// enough to code for locked doors... adding in a random strength of the
// lock.                 **Piper**

varargs int door_lock(string direc, int strength)
{
   if(!strength)
      strength = random(101);
   if(strength != 0)
   {
      if(!lock_dir||sizeof(lock_dir) ==0)
         lock_dir = ({ });
      lock_dir += ({ direc });

      if(!lock_str||sizeof(lock_str) ==0)
         lock_str = ({ });
      lock_str += ({ strength });

      if(!all_locks||sizeof(all_locks) == 0)
         all_locks = ({ });
      all_locks += ({ direc,strength });

      return(1);
   }
   return(1);
}

// First stab a an unlock feature... to enable the lock to be opened...
//      ***Piper***

int door_unlock(string direc)
{
   int i;
  string strong;
   if((i = member_array(direc,lock_dir)) == -1)
     return(0);
   strong = lock_str[i];
            write("\n   You unlock the "+direc+" exit.\n\n");
              say("\n   "+this_player()->query_cap_name()+
                  " unlocks the "+direc+" exit.\n\n");
            lock_dir -= ({ direc });
            lock_str -= ({ strong });
            all_locks -= ({ direc,strong });
         return(1);
}

// Attempt at a query for the strength of the locked doors
//               ***Piper***

string *query_lock_str(string direc)
{
   return lock_str;
}

// Query for the lock direction.... ***Piper**

string *query_lock_dir(string direc)
{
   return lock_dir;
}

// Query that **shows** you the locked exits and there respective
//      strengths   **Piper**

mixed *query_locks() { return all_locks; }

//    This is a function to set up exits that can be dug to...
//   ie <dig direction>  lets you if allowed to dig an exit in this
//     room...    **Piper**

int dig(string direc, mixed dest)
{
   string *nodig = this_object()->query_direc();

   if(!dig_exit||sizeof(dig_exit) == 0)
      dig_exit = ({ });
      dig_exit += ({ direc });

   if(!dig_where||sizeof(dig_where) == 0)
      dig_where = ({ });
      dig_where += ({ dest });

}

// This is a query for the array of diggable exits.... :)
//   returns the exits in array form....  **Piper**

string *query_pos_dig() { return dig_exit; }

// This is a query for the array of diggable exit destinations
//    returns array of file pathnames...  **Piper**

string *query_dig_dest() { return dig_where; }

//  Had to add the dig code to this file.. no longer inheriting it
//  needed add_exit (besides thought it might streamline better.)
//    ***Piper***   (4-1-95)
//   Inheritable digging routine...  dig (direction) with digging tool
//       Original idea by Lor
//       Major rework by Piper

#define TP this_player()
#define TPP this_player()->query_possessive()
#define TPN this_player()->query_cap_name()

string tool;

int query_wielded_pick()
{
   int i;
   object *olist;
   olist = this_player()->query_held_ob();
   for(i=0;i<sizeof(olist);i++)
   {
      if(olist[i])
      {
         if((string)olist[i]->query_name() == "shovel")
         {
            tool = olist[i];
            return(1);
         }
         if((string)olist[i]->query_name() == "mining pick")
         {
            tool = olist[i];
            return(1);
         }
         if((string)olist[i]->query_name() == "pick")
         {
            tool = olist[i];
            return(1);
         }
      }
   }
   return(0);
}

void do_dig(string direc)
{
   mixed path = file_name(this_object());
   string adirec = "hole";

   int i,j;
   mixed *dlist,*dwhere;
   dwhere = this_object()->query_dig_dest();
   dlist = this_object()->query_pos_dig();
   for(i=0;i<sizeof(dlist) && i<sizeof(dwhere);i++)
   {
     mixed *ndlist;
     ndlist = this_object()->query_direc();
     for(j=0;j<sizeof(ndlist);j++)
     {
         if((string)ndlist[j] && direc == (string)ndlist[j])
         {
            if(query_wielded_pick())
            {
            write("\n   Why would you dig somewhere that a way"+
                  " of passage already exists.  Try digging else"+
                  "where.\n\n");
               say("\n   "+TPN+" prepares to dig"+
                  ", takes a step forward then stops, slaps "+TPP+
                  " forehead and looks digruntled.\n\n");
             return(1);
            }
         write("\n   Dig with what?\n\n");
          return(1);
         }
      }
      if((string)dlist[i] && direc == (string)dlist[i])
      {
         string where = dwhere[i];
         if(query_wielded_pick())
         {
            write("\n   You begin to dig slowly into the earth, but"+
                  " meet difficulty immediately.  The rock and dirt"+
                  " here has been settled for so long, it seems that"+
                  " it will be immpossible to make any progress.  With"+
                  " determination and a little time however, you are"+
                  " finally able to dig a hole.\n\n");
             tell_room(environment(this_player()),"\n   "+
                  this_player()->query_cap_name()+" begins to dig"+
                  " into the earth with fierce determination"+
                  ".  After a considerable amount of digging a"+
                  " nice size hole develops.\n\n",({this_player()}));
            add_exit(direc,where,"hole");
            this_object()->init();
               if(direc == "east")
                 adirec = "west";
               if(direc == "west")
                 adirec = "east";
               if(direc == "north")
                 adirec = "south";
               if(direc == "south")
                 adirec = "north";
               if(direc == "up")
                 adirec = "down";
               if(direc == "down")
                 adirec = "up";
               if(direc == "northeast")
                 adirec = "southwest";
               if(direc == "southeast")
                 adirec = "northwest";
               if(direc == "northwest")
                 adirec = "southeast";
               if(direc == "southwest")
                  adirec = "northeast";
            where->add_exit(adirec,path,"hole");
         return(1);
         }
      write("\n   Dig with what?\n\n");
      return(1);
      }
   }
   write("\n   You start to dig into the earth with such vigor that"+
         " the air is growing dusty and thick with dirt.  It is only"+
         " after you take a rest that you realize that the hole is"+
         " growing very slowly...  Looks like your gonna be digging for a"+
         " while.\n\n");
     say("\n   "+
         this_player()->query_cap_name()+" starts to dig with a"+
         " determination that you can only admire."+
         "\n\n"+
         " ");
   return(1);
}

// Modify_exit... does this thing ever work? **Piper**
int modify_exit(string direc, mixed *data) {
  int i, j;
  if ((i=member_array(direc, dest_other)) == -1)
    return 0;
 
  for (j=0;j<sizeof(data);j+=2)
    switch (lower_case(data[j])) {
      case "message" :
        dest_other[i+1][ROOM_MESS] = data[j+1];
        break;
      case "obvious" :
        dest_other[i+1][ROOM_OBV] = data[j+1];
        break;
      case "function" :
        dest_other[i+1][ROOM_FUNC] = data[j+1];
        break;
      case "size" :
        dest_other[i+1][ROOM_SIZE] = data[j+1];
        break;
      case "enter" :
        dest_other[i+1][ROOM_ENTER] = data[j+1];
        break;
      case "dest" :
        dest_other[i+1][ROOM_DEST] = data[j+1];
        break;
      case "open" :
        if (door_control[direc])
          door_control[direc][0]->set_open(data[j+1]);
        break;
      case "locked" :
        if (door_control[direc])
          door_control[direc][0]->set_locked(data[j+1]);
        break;
      case "key" :
        if (door_control[direc])
          door_control[direc][0]->set_key_prop(data[j+1]);
        break;
      case "other" :
        if (door_control[direc])
          door_control[direc][0]->set_other_id(data[j+1]);
        break;
      case "difficulty" :
        if (door_control[direc])
          door_control[direc][0]->set_difficulty(data[j+1]);
        break;
      case "open desc" :
        if (door_control[direc])
          door_control[direc][0]->set_open_desc(data[j+1]);
        break;
      case "close desc" :
        if (door_control[direc])
          door_control[direc][0]->set_close_desc(data[j+1]);
        break;
      case "undoor" :
        if (door_control[direc]) {
          door_control[direc][0]->go_away();
          hidden_objects = hidden_objects - ({ door_control[direc][0] });
        }
        door_control = m_delete(door_control, direc);
        break;
    }
  return 1;
} /* modify_exit() */
 
int remove_exit(string direc) {
  int i;
  if (!dest_other)
    dest_other = ({ });
  if ((i=member_array(direc, dest_other)) == -1)
    return 0;
  dest_other = delete(dest_other, i, 2);
  dest_direc = delete(dest_direc, i/2, 1);
  if (door_control[direc]) {
    door_control[direc][0]->go_away();
    hidden_objects = hidden_objects - ({ door_control[direc][0] });
  }
  door_control = m_delete(door_control, direc);
  short_exit_string = 0;
  exit_string = 0;
  return 1;
} /* remove_exit() */

int query_exit(string direc) {
  return (member_array(direc, dest_other) != -1);
} /* query_exit() */

int query_size(string direc) {
   int i;
 
  if ((i=member_array(direc, dest_other))==-1)
    return 0;
  if (stringp(dest_other[i+1][ROOM_SIZE]))
    return (int)call_other(this_object(), dest_other[i+1][ROOM_SIZE]);
  if (pointerp(dest_other[i+1][ROOM_SIZE]))
    return (int)call_other(dest_other[i+1][ROOM_SIZE][0],
                      dest_other[i+1][ROOM_SIZE][1]);
  return dest_other[i+1][ROOM_SIZE];
} /* query_size() */
 
int do_exit_command(string str, mixed verb, object ob, object foll) {
  string special_mess, closed;
   int i,lk;
  mixed zip;

   object *locklist,*lockstr;
   locklist = this_object()->query_lock_dir();
   lockstr = this_object()->query_lock_str();

  if (!verb)
    verb = query_verb();
  else {
    if (pointerp(verb)) {
      special_mess = verb[1];
      verb = verb[0];
    }
    if (!sscanf(verb, "%s %s", verb, str) !=2)
      str = "";
  }
  if (!ob)
    ob = this_player();
  if ((i=member_array(verb,dest_direc))==-1)
    if ((i=member_array(verb, aliases)) == -1)
      return 0;
    else
      if ((i=member_array(aliases[i-1], dest_direc)) == -1)
        return 0;
 
/* ok must be two command exit */
  if (dest_direc[i] != dest_other[i*2]) {
    string s1,s2;
    int j;
 
    sscanf(dest_other[i*2],"%s %s",s1,s2);
    str = expand_alias(str);
    if (s2 != str) {
      zip = dest_direc[i+1..sizeof(dest_direc)];
      while (1)
        if ((j = member_array(verb, zip)) != -1) {
          i += j+1;
          sscanf(dest_other[i*2],"%s %s", s1, s2);
          if (str == s2)
            break;
          zip = zip[j+1..sizeof(zip)];
        } else
          return 0;
    }
  }
//  Gonna add my own little locked door thingy here.
//         **Piper**
   for(lk=0;lk<sizeof(locklist)&&lk<sizeof(lockstr);lk++)
   {
      if(locklist[lk] == dest_direc[i])
      {
         string capname = ob->query_cap_name();
         object here = this_object();
         string direc = dest_direc[i];
         string etype = exit_type[i];
         int locked = lockstr[lk];

         if((locked != 0)&&
           ((etype == "gate")||
            (etype == "door")))
         {
         write("\n   The "+etype+" is locked."+
               "\n\n");
            say ("\n   "+capname+" tries to open the "+direc+" "+etype+
                  ", but it is locked.\n\n");
            return(1);
         }
      }
   }
/* First check for lockedness of doors etc */
  if (zip = door_control[dest_other[i*2]]) {
    if (zip[0]->query_locked()) /* Locked...  We auto-unlock, if they have the key */
      if (!zip[0]->moveing_unlock(ob))
        return 0;
    if (!zip[0]->query_open()) { /* Closed open it and close it after us. */
      if (!zip[0]->moveing_open(ob))
        return 0;
      closed = zip[0];
    }
  }
  if (dest_other[i*2+1][ROOM_FUNC])
    if (stringp(dest_other[i*2+1][ROOM_FUNC])) {
      if (!call_other(this_object(), dest_other[i*2+1][ROOM_FUNC], str, ob, special_mess))
        return 0;
    } else {
      if (pointerp(dest_other[i*2+1][ROOM_FUNC]))
        if (!call_other(dest_other[i*2+1][ROOM_FUNC][0],
                        dest_other[i*2+1][ROOM_FUNC][1], ob, special_mess))
          return 0;
    }
  if (!special_mess)
    zip = (int)ob->move_player(dest_other[i*2], dest_other[i*2+1][ROOM_DEST],
                                   dest_other[i*2+1][ROOM_MESS], foll,
                                   dest_other[i*2+1][ROOM_ENTER]);
  else
    zip = (int)ob->move_player(dest_other[i*2], dest_other[i*2+1][ROOM_DEST],
                                   special_mess, foll,
                                   dest_other[i*2+1][ROOM_ENTER]);
  if (closed)
    closed->moveing_close(ob);
  return zip;
} /* do_exit_command() */
 
/* 
 * Ok we have done all the exit junk, now for the item bits and pieces
 * share and enjoy your plastic pal who is fun to be with
 */
int add_item(string str,string desc) {
  object ob;
  int i;

  if (!items)
    items = ([ ]);

  ob = items["The object"];
  if (!ob) {
    ob = clone_object(ITEM_OBJECT);
    items["The object"] = ob;
  }
  ob->setup_item(str, desc);
  return 1;
} /* add_item() */

/*
 * Ok.  Remove item is nasty :(  But....  We will add it.
 * It will remove all things that reference the given desc.
 */
int remove_item(string str) {
  object ob;
 
  if (!items)
    items = ([ ]);

  ob = items["The object"];
  if (!ob)
    return 0;
  return (int)ob->remove_item(str);
} /* remove_item() */

/*
 * Change all descs...  It does a match and goes wimble.
 */
int modify_item(string str, string new_desc) {
  object ob;
 
  if (!items)
    items = ([ ]);

  ob = items["The object"];
  if (!ob)
    return 0;
  return (int)ob->modify_item(str, new_desc);
} /* modify_item() */

mapping query_items() { return items; }

/*
 * The alias junk
 */
int add_alias(mixed name,string str) {
  int i;
 
  if (!aliases)
    aliases = ({ });
 
  if (pointerp(name)) {
    for (i=0;i<sizeof(name);i++)
      add_alias(name[i], str);
    return 1;
  }
 
  aliases += ({ str, name });
  return 1;
} /* add_alias() */
 
int modify_alias(string str,string name) {
  int i;
 
  if (!aliases)
    return 0;
 
  if ((i=member_array(str, aliases))==-1 || !(i%2))
    return 0;
 
  aliases[i+1] = name;
  return 1;
} /* modify_alias() */
 
int remove_alias(string str) {
  int i;
 
  if (!aliases)
    return 0;
 
  if ((i=member_array(str, aliases))==-1 || !(i%2))
    return 0;
 
  aliases = delete(aliases, i, 2);
  return 1;
} /* remove_alias() */
 
int query_no_writing() { return 1; }
 
void dest_me() {
  int i;

  if (!destables)
    destables = ({ });
  if (mappingp(items))
    destables += m_values(items);
  for (i=0;i<sizeof(destables);i++)
    if (destables[i])
      destables[i]->dest_me();
  destruct(this_object());
} /* dest_me() */
int clean_up( int flag )
{
  mixed *arr;
  int i;
 
  if( flag > 1 ) return 0; // If inherited don't call clean_up() for TO again
  arr = all_inventory(this_object());
  for (i=0;i<sizeof(arr);i++)
    if (interactive(arr[i]))
     return 1;
  arr->dest_me();
  dest_me();
  return 0;
} // clean_up()
object *find_inv_match(string str) {
  return all_inventory(this_object()) + hidden_objects + m_values(items);
} /* find_inv_match() */

int do_search(string str) {
  write( ({
"You search around for a while but dont find anything.\n",
"You scrounge around, the ground does look interesting you decide.\n",
"You look carefully at everything, but you find nothing.\n",
"After a while of intensive searching you find nothing.\n" })[random(3)]);
  say(this_player()->query_cap_name()+" searches around the room a bit.\n");
  event(this_object(), "player_search");
  return 1;
} /* do_search() */

/* Cute, useful add_sign. */
/*
 * add_sign(string long, string read_mess, string short, string name)
 * [short and name are optional]
 * This file can be inherited and will return a sign that can be used
 * by a room or object in any way it sees fit.  This function was the
 * brainchild of Wyrm - 7 Feb '92
 * If the short is left out.. The sign isnt moved into the room,
 * but it can still be looked at and read.
   * This facility was removed by Taniwha 1995, as recent driver and
   * lib changes means thats these objects are scavenged as "dead" now
   *
 */

varargs object add_sign(string long, string mess, string short, string sname) {
  object sign;

  sign = clone_object("/std/object");

  if(!sname) sname = "sign";
  sign->set_name(sname);
  sign->set_main_plural(pluralize(sname));
  if (short)
    sign->set_short(short);
   else sign->set_short("Sign");
  sign->set_long(long);
  sign->set_read_mess(mess);
  sign->reset_get();
//if (short && short != "")
    sign->move(this_object());
//else
//  hidden_objects += ({ sign });
  destables += ({ sign });
  return sign;
} /* add_sign() */

mapping query_door_control() { return door_control; }

void tell_door(string dir, string mess) {
  if (!door_control[dir])
    return;
  door_control[dir][0]->tell_door(mess);
} /* tell_door() */

mixed call_door(string dir, string func, mixed arg1, mixed arg2, mixed arg3) {
  if (!door_control[dir])
    return;
  return (mixed)call_other(door_control[dir][0], func, arg1, arg2, arg3);
} /* call_door() */


mixed query_door(mixed dest) {
  mixed bing;

  if ((bing = door_control[dest]))
    if (!pointerp(bing))
      return bing;
  if (objectp(dest))
    if ((bing = door_control[file_name(dest)]))
      if (!pointerp(bing))
        return bing;
  return 0;
} /* query_door() */

mixed stats() {
  mixed *exits, *tmp;
  int i;

  exits = ({ });
  for (i=0;i<sizeof(dest_other);i+=2)
    exits += ({ ({ "Direction", dest_other[i], }),
                ({ "Destination", dest_other[i+1][ROOM_DEST] }) });
  if (co_ord)
    tmp = ({ ({ "co-ord x", co_ord[0] }),
             ({ "co-ord y", co_ord[1] }),
             ({ "co-ord z", co_ord[2] }), });
  else
    tmp = ({ });
  return ({ ({ "short", short(0), }),
            ({ "location", query_property("location"), }),
            ({ "move zone", room_zone }),
         }) + tmp + exits + ::stats();
} /* stats() */

int query_decay() { return 10; }

/* Number of move points used by an attack... */
int attack_speed() { return 15; }
