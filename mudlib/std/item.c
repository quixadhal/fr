/* Item.c 
 * Made by Baldrick.
 * to be used instead of /std/object on *EVERY* object that can be carried.
 * 
 * Right now it's only armour.c and weapon.c that inherits it.
 * and for now that's the only one needing it..
 * unless you have any wear / wieldable items.. the should also inherit this
 */
inherit "/std/object";

status wearable;
status holdable;
status in_use;

void set_holdable(int i) 
  { 
  holdable = i; 
  if (wearable && holdable)
    wearable = 0;
}

void set_wearable(int i) 
  { 
  wearable = i; 
  if (wearable && holdable)
    holdable = 0;
}

void set_in_use(int i)
  {
  in_use = i;
  }

int query_holdable() { return holdable; }
int query_wearable() { return wearable; }
int query_in_use() { return in_use; }

void create()
  {
  holdable = wearable = 0;
  object::create();
}

// Move hack so that wearables/holdables will leave the wear/hold
// arrays of living creatures.
int move(mixed dest, mixed messout, mixed messin) 
   {
   object ob;
   int i;

   ob = environment(this_object());
   i = ::move(dest, messout, messin);

   if (!i && in_use && objectp(ob) && living(ob))
      if (holdable)
         ob->unhold_ob(this_object());
      else if (wearable)
         ob->unwear_ob(this_object());

   return i;
}
/* Added april '95 by Baldrick, does the same as the move, just for dest_me
 * Not sure if it will work tho 
 */
void dest_me()
  {
   object ob;
   int i;

   ob = environment(this_object());

   if (in_use && objectp(ob) && living(ob))
      if (holdable)
         ob->unhold_ob(this_object());
      else if (wearable)
         ob->unwear_ob(this_object());
   ::dest_me();
} /* void dest_me */
