/* A temple for raising..
 * Needs money to work...
 * Inherits collect.c that uses the bank-handler to handle accounts.
 * Baldrick.
 */

#define HEALER "/baseobs/monsters/healer.c"
inherit "/std/collect";

string nurs;

void setup()
  {
  set_short("Raiseroom Object.");
}

void init()
  {
  add_action ("do_raise", "raise");
  ::init();
} /* void init */

void set_helper_name(string str)
  {
  nurs = str;
  return;
}

/* Here is the raise thingie. It will start with checking if there is a jill
 * in the room, so he can call upos the high priest for raise.
 * Then the usual check on who.
 * So will the moneystuff happen. It will check if the player has enoug money.
 * and raise him if the player has.
 */

int do_raise(string str)
  {
  int cost; /* The cost in Gold. */
  object priest, poor_guy;
   object *olist;

  if (str=="me")
    poor_guy=this_player();
   else
   {
      notify_fail("Raise who ?\n");
      if(!str) return 0;
      olist = find_match(str,this_object());
      if(!sizeof(olist)) return 0;
      poor_guy = olist[0];
      if(!find_living(str)) return 0;
   }
  if (!poor_guy->query_property("dead"))
    return notify_fail("Why ask for a raise when you don't need it?\n");

  if (!find_match(nurs, environment(this_player())))
    {
    notify_fail("The priestess is not here to help you with the " +
                "raising. You have to wait for her.\n");
    return 1;
    }
 
  if ((int)poor_guy->query_level() > 1) 
    {
    cost = (int)poor_guy->query_level() * 5;
    if(!get_money(cost))
      {
      tell_room(this_object(), "The Nurse says: Due to sad lack of "+
                    "money we will not be able to raise you.\n");
      return 1;
      } /* if */
    } /* if int poorguy.. */

   tell_room(this_object(), "The Nurse"+
             " walks out and comes back with an old man " +
             "with ceremonial clothes. He chants a spell.\n");

  priest = new(HEALER);
   priest->move(this_object());
  priest->do_raising(poor_guy);
  tell_room(this_object(), "The priest says: You are now alive again. " +
             "Be more careful this time.\n");
  tell_room(this_object(), "The priest walks out of the room.\n");
  priest->dest_me();
  return 1;
} /* do  raise */
