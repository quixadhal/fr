#define TICS_HB 5 /* cludge to get timed properties on things without heart_beats */
/* /std/basic/property */
/* Adding static properties. making it easer to use for spelleffetcs
 * and such wombles..
 * Baldrick, Jan '95
 * Hrmf.. now a hard one, a timed propertysystem. saveable
 */
 
mapping map_prop;
mapping timed_prop;
static mapping static_map_prop;
 
void create() {
  map_prop = ([ ]);
  static_map_prop = ([ ]);
  timed_prop = ([ ]);
}
 
 
int query_hb_counter()
{

   return time()/TICS_HB;
}

int query_hb_diff(int oldc)
{
   int hb_counter;
   hb_counter = query_hb_counter();
   if(hb_counter > oldc) return hb_counter - oldc;
   else return oldc - hb_counter;
}
 
int add_property(string var, mixed val) {
  int i;
 
  if (!stringp(var))
    return 0;
  if (!map_prop)
    map_prop = ([ ]);
  map_prop[var] = val;
  return 1;
}

int add_static_property(string var, mixed val) {
  int i;

  if (!stringp(var))
    return 0;
  if (!static_map_prop)
 /* this_object() because we have a crude thingy in here which is over-ridden in anything with it's own HB */
    static_map_prop = ([ ]);
  static_map_prop[var] = val;
  return 1;
}

int add_timed_property(string var, mixed val, int time)
  {
  int i;

  if (!stringp(var))
    return 0;
  if (time < 1)
    return 0;
  if (!timed_prop)
    timed_prop = ([ ]);
  i = this_object()->query_hb_counter();
  timed_prop[var] = ({val, time, i});
  return 1;
}

int remove_property(string var) {
  int i;
 
  if (!var)
    return 0;
  if (!map_prop)
    map_prop = ([ ]);
  map_prop = m_delete(map_prop, var);
  return 1;
}

int remove_static_property(string var) {
  int i;

  if (!var)
    return 0;
  if (!static_map_prop)
    static_map_prop = ([ ]);
  static_map_prop = m_delete(static_map_prop, var);
  return 1;
}

int remove_timed_property(string var) {
  int i;

  if (!var)
    return 0;

  if (!timed_prop)
    timed_prop = ([ ]);
  timed_prop = m_delete(timed_prop, var);
  return 1;
}
 
int query_old_property(string str) {
  int i;

  if (!str)
    return 0;
 
  if (!map_prop)
    map_prop = ([ ]);
  return map_prop[str];
}


int query_static_property(string str) {
  int i;
  
  if (!str)
    return 0;

  if (!static_map_prop)
    static_map_prop = ([ ]);
  return static_map_prop[str];
}

/* This is the hard part of the timing system.
 * It will check if the property is timed out before returning the value.
 * this will make the timingsystem sleeping while not in use.
 * Smart, idea from Taniwha, coded by Baldrick.
 * ehh tried to be coded.. wonder if it will work..
 */
int query_timed_property(string str) {
  int i;
  int val;

  if (!str)
    return 0;

  if (!timed_prop)
    timed_prop = ([ ]);
  //if (!sizeof(timed_prop[str][0]));
   // return 0;
   if(!timed_prop[str]) return 0;
  i = timed_prop[str][1];
  if (this_object()->query_hb_diff(timed_prop[str][2]) > i)
    {
    remove_timed_property(str);
    return 0;
    }
  val = timed_prop[str][0];
  return val;
}
/* Added Taniwha 1995, by popular demand, time remaining */
/* Could do clever stuff like check for static & normals if it falls through */
static int timeleft;
int query_time_remaining(string str) {
  int i;
  int val;
  if (!str)
    return 0;
  if (!timed_prop)
    timed_prop = ([ ]);
   if(!timed_prop[str]) return 0;
  i = timed_prop[str][1];
   val = i - (int)this_object()->query_hb_diff(timed_prop[str][2]) ;
   if( val <= 0)
   {
      val = 0;
      remove_timed_property(str);
   }
   timeleft = val;
   return timeleft;
}

/* Added by Baldrick April '95.
 * This is called upon every login or logout (not decided yet)
 * Will remove "old" timed properties to redice memoryusage.
 * The clue is to get through a bunch of stringpointers when you don't
 * know the string...
 */
void traverse_timed_properties()
  {
  int i, koo;
  string *koofs;

  koofs = m_indices (timed_prop);
  for (i=0;i<sizeof(koofs);i++)
    {
    koo = koofs[i][1];
    if (this_object()->query_hb_diff(timed_prop[koofs[i]][2]) > koo)
      {
      remove_timed_property(koofs[i]);
      } /* if */
    } /* for */

} /* void traverse.. */
 
int query_property_exists(string str) {
  int i;
  if (!map_prop)
    map_prop = ([ ]);
  return (member_array(str, m_indices(map_prop))) != -1;
}

int query_static_property_exists(string str) {
  int i;
  if (!static_map_prop)
    static_map_prop = ([ ]);
  return (member_array(str, m_indices(static_map_prop))) != -1;
}

int query_timed_property_exists(string str) {

  if (!timed_prop)
    timed_prop = ([ ]);
  return (member_array(str, m_indices(timed_prop))) != -1;
}
 
mapping query_properties() { return map_prop ; }

mapping query_static_properties() { return static_map_prop ; }

mapping query_timed_properties() { return timed_prop; }

int add_properties(mapping map) {
  map_prop += map;
}

int add_static_properties(mapping map) {
  static_map_prop += map;
}

int add_timed_properties(mapping map) {
  timed_prop += map;
}

/* std/basic/property: */
mixed *query_init_data() {
   return ({ "properties", map_prop, "add_properties/p/" });
} /* query_init_data() */
int query_property(string str) {

  if (!str)
    return 0;
   if(query_timed_property_exists(str)) return query_timed_property(str);
   if(query_static_property_exists(str)) return query_static_property(str);
   return query_old_property(str);
 
}
