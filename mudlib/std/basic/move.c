#include "move_failures.h"
#define DROP 1
#define GET 2
int move_flag;
private object prev; /* added Mar 3 '93 by Dank to support goback command */

object query_prev() { return prev; }

/* default to being gettable and dropable...
 * modify as you will...
 */
void reset_get() { move_flag |= GET; }   /* can't be gotten */
void set_get() { move_flag &= ~GET; }    /* can be gotten */
void reset_drop() { move_flag |= DROP; }   /* can't be dropped */
void set_drop() { move_flag &= ~DROP; }    /* can be dropped */  

/* these should have been called "query...", but they're not */
int drop() { return move_flag & DROP; }
int get() { return move_flag & GET; }

void set_move_flag(int i) { move_flag = i; }

varargs int move(mixed dest, mixed messin, mixed messout) {

  prev = environment();
  if (!dest)
    return MOVE_EMPTY_DEST;
  if (environment() && !environment()->test_remove(this_object(),
                                                  move_flag & DROP))
    return MOVE_NO_DROP;
  if (!dest->test_add(this_object(), move_flag & GET))
    return MOVE_NO_GET;
  if (environment())
    event(environment(), "exit", messout, dest);
  move_object(this_object(), dest);
  if (objectp(dest))
    event(dest, "enter", messin, prev);
  else if (find_object(dest))
    event(find_object(dest), "enter", messin, prev);
  return MOVE_OK;
}

void dest_me() {
  if (environment())
    event(environment(), "dest_me");
  efun::destruct(this_object());
}

/* Do not I repeat do not mask this function.
 * is used when all else fails to dest the object...
 * If we find you masking this function... We will cut you up
 * into little bits... slowly
 */
nomask mixed dwep() {
  efun::destruct(this_object());
  return "Destruct With Extreme Prejuce";
}

/* std/basic/move: */
mixed *query_init_data() {
   return ({ "move", move_flag, "set_move_flag/p/" });
} /* query_init_data() */
