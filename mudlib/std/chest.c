inherit "std/item";
inherit "std/basic/cute_look";
#include "move_failures.h"

#define MAX_INVENT 40
#define C_CLOSED 1
#define C_TRANS 2
#define C_OPAQUE 1

static int max_weight, loc_weight;
int strength;
string locktype;
static int prevent_insert;
int open;    // if open == 1 you can SEE contents
string close_mess, open_mess;

void create() {
  item::create();
} /* create() */

string query_close_mess() { return close_mess; }
string query_open_mess() { return open_mess; }
void set_open_mess(string arg) { open_mess = arg; }
void set_close_mess(string arg) { close_mess = arg; }
void set_close_message(string arg) { close_mess = arg; }
void set_open_message(string arg) { open_mess = arg; }
void set_max_weight(int arg) { max_weight = arg; }
int query_max_weight() { return max_weight; }
int query_loc_weight() { return loc_weight; }
int query_open() { return(open); }

int add_weight(int n) {
  int old, new;

  if (::add_weight(n)) return 1;
  if (!max_weight) return 1;
  if (n + loc_weight > max_weight) return 0;
  loc_weight += n;
  return 1;
} /* add_weight() */

int transfer_all_to(object dest) {
  object *ob;
  int i;
 
  ob = all_inventory(this_object());
  ob -= ({ dest });
  for (i=0;i<sizeof(ob);i++)
    ob[i]->move(dest);
  if (first_inventory(this_object())) return 0;
  return 1;
} /* transfer_all_to() */

/* ok modifyed back to using writes... */
string long(string str, int dark) {
  string ret;

  ret = ::long(str);
  ret += calc_extra_look();
  if(!query_open()) return ret;
  if(this_object()->query_corpse())
    ret += (string)this_object()->query_living_contents(0);
  else
    ret += query_contents(short(dark)+" contains:\n", all_inventory() - 
                          query_labels());
  return ret;
} /* long() */
int open_chest() 
{
   if(!open)
   {
      int diff = this_object()->query_lock_str();
      if(diff == 0)
      {
         write(query_open_mess()+"\n");
         open = 1;
         return(1);
      }
      write("\n   The "+this_object()->query_name()+" is"+
            " locked tightly.\n\n");
      return(1);
   }
   write("Chest is already open.\n");
   return(1);
}
int close_chest()
{
   if(open)
   {
      write(query_close_mess()+"\n");
      open = 0;
      return(1);
   }
   write("The chest is presently closed.\n");
   return(1);
}

int test_remove(object ob, int flag) {
   if(open == 1){return 1;}
   else{return 0;}
}
int test_add(object ob, int flag) {
   if(open == 1){return 1;}
   else{return 0;}
}
int set_prevent_insert() { prevent_insert = 1; }
int reset_prevent_insert() { prevent_insert = 0; }
int query_prevent_insert() { return prevent_insert; }

varargs int move(mixed dest, mixed messin, mixed messout) {
  if (prevent_insert && loc_weight && !living(dest) && environment(dest))
    return MOVE_INVALID_DEST;
   return item::move(dest,messin,messout);
} /* move() */

object *find_inv_match(string str) {
  return all_inventory(this_object());
} /* find_inv_match() */

mixed stats() {
  return ::stats() + ({
    ({ "loc_weight", query_loc_weight(), }),
    ({ "max_weight", query_max_weight(), }),
  });
} /* stats() */

mixed *query_init_data() {
  return item::query_init_data() + ({
         "max weight", max_weight, "set_max_weight",
         "prevent insert", prevent_insert, "set_prevent_insert",
         });
} /* query_init_data() */

mapping int_query_static_auto_load() {
  mapping tmp;

  tmp = ::int_query_static_auto_load();
  return ([ "::" : tmp, "max weight" : max_weight,
            "prevent insert" : prevent_insert,
    ]);
} /* int_query_static_auto_load() */

mapping query_dynamic_auto_load() {
  return ([ "::" : ::query_dynamic_auto_load(),
            "inv" : 
         "/global/player"->create_auto_load(all_inventory(this_object())-labels),
         ]);
} /* query_dynamic_auto_load() */

void init_dynamic_arg(mapping bing) {
  if (bing["::"])
    ::init_dynamic_arg(bing["::"]);
  if (bing["inv"])
    "/global/player"->load_auto_load(bing["inv"], this_object());
} /* init_dynamic_arg() */

void init_static_arg(mapping bing) {
  if (bing["::"])
     ::init_static_arg(bing["::"]);
  if (!undefinedp(bing["max weight"]))
    max_weight = bing["max weight"];
  if (!undefinedp(bing["prevent insert"]))
    prevent_insert = bing["prevent insert"];
} /* init_static_arg() */

mixed query_static_auto_load() {
  if (file_name(this_object())[0..13] == "/std/container")
    return int_query_static_auto_load();
  return ([ ]);
} /* query_static_auto_load() */

//Locks.. always me and the locks...  **Piper** (5/23/95)

varargs int box_lock(string type,int stren)
{
   if(!stren)
      stren = random(101);
   if(!type)
      type = "simple";
   strength = stren;
   locktype = type;
}

string query_lock_str() { return strength; }

int query_ltype() { return locktype; }

int box_unlock(string box)
{
   strength = 0;
   write("\n   You unlock the "+this_object()->query_name()+".\n\n");
     say("\n   "+this_player()->query_cap_name()+" smiles"+
         " as "+this_player()->query_pronoun()+" unlocks the"+
         " "+this_object()->query_name()+".\n\n");
   return(1);
}

void contain(mixed content)
{
   open = 1;
   new(content)->move(this_object());
   open = 0;
   return(1);
}
