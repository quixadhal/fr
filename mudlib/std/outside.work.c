#include "weather.h"
inherit "/std/room";
 
/* ok this is the out side room standard, It includes weather and
 * all that jazz
 */
 
static string dark_long; /* for those time when night is upon us... but the
                          * should be able to be seen still. */
 
void set_dark_long(string s) { dark_long = s; }
string query_dark_long() { return dark_long; }
 
    
void create() {
  ::create();
  add_property("location", "outside");
}
 
string short(int dark) {
    if (dark) return query_dark_mess();
    else return ::short();
    }
 
string long(string str, int dark) {
int i;
string s, ret;
 
  if (dark)
    return query_dark_mess()+".\n";
  if (!str) {
    if (pointerp(co_ord) && !WEATHER->query_day(this_object())) {
      s = (string)WEATHER->query_moon_string(this_object());
      if (!s)
        ret =  "It is night and the moon is not up.\n";
      else if ((int)WEATHER->cloud_index(this_object()) > 20)
        ret = "It is night and the "+s+" is hidden by the clouds.\n";
      else
        ret = "The land is lit up by the eerie light of the "+s+".\n";
      if (!query_dark_long())
        ret += query_long();
      else
        ret += query_dark_long();
    } else
      ret = query_long();
    s = calc_extra_look();
    if (s && s != "")
      ret += s;
    if (pointerp(co_ord))
      ret += (string)WEATHER->weather_string(this_object())+".\n";
    if (!exit_string)
      s = query_dirs_string();
    else
      s = exit_string;
    ret += s + "\n";
/* Ok since at this point long's dont return a string...
 * we have to write it out ;(
 */
    return ret+query_contents("");
  }
  str = expand_alias(str);
  return items[str];
}
 
/* percentage system */
int query_light() {
  int i;

  i = (int)WEATHER->query_darkness(this_object());
  return ::query_light()*i/100;
}
