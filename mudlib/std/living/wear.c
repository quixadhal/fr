/* Taniwha was here 09/94
 * extended the code to allow more types
 * so clothing like shirts can be worn with armour
 *
 */

#define MAXTYPES 20
/* Wear.c used for wearable objects.. or rather for players to be able
 * to wear armour and other stuff. 
 * Will makeit possible for items to be worn even if they're not armour.
 * And also make armour heldable, not only wearable.
 * It is completely rewritten by Baldrick, april '94
 */

/* we will have different types of worn objects.
 * Body armour, Body clothing, boots/shoes and head will be one only.
 * Rings will be multipple.  Maybe add an amount_heads ? :=)
 * It won't be any problem to add new types later.
 */

static private mixed *worn_ob;
static private int worn_ac;
static private int *armour_types;

/* Won't need this then.. Just ask the item for type.. */

// string w_object;

// prototypes:

object query_worn_ob() { return worn_ob; }

void reset_types();

create() 
  {
  worn_ob = ({ });
  worn_ac = 0;
  reset_types();
}

void reset_types()
  {
  int e;
  armour_types = allocate (MAXTYPES);
  for (e=0;e<MAXTYPES;e++)
    {
    armour_types[e] = 0;
    }
}

/* The total AC for all worn objects.. */
/* Shall I add the hold AC (shields) here or caculate everything 
 * in an equip.c ? */

int query_worn_ac() { return worn_ac; }

/*  Need a total rewrite..:=) as everything else..
void dest_armour(object armour) 
  {

}
*/

int unwear_ob(object ob) 
  {
  int slot;
  int a_type;
  if ((slot = member_array(ob, worn_ob)) == -1) 
    return notify_fail("You don't hold this item.\n");

  worn_ob -= ({ ob });
  a_type = ob->query_armour_type();
  armour_types[a_type] = 0;

  tell_object(this_object(),"You take off your " + (string)ob->query_short() + ".\n");
  worn_ac -= ob->query_ac();
  ob->set_in_use(0);
  return 1;
}

status wear_ob(object ob) 
  {
  int a_type, occupied;
  /* Maybe this check is/can be another place ? */
  /* Made a query_holdable in living.c.. */
 
//  if (!ob->query_wearable()) return 0;

  /* Test if the type is worn already.. */
  /* This check is a mess, since I want to use the return as a string.
   * query_wear_type is a string.. */
  /* I'll add the whole thingie later.. */
  a_type = (int)ob->query_armour_type();
  /* Rings and amulets can be multipple worn.
   * that's type 5 & 7 
   */
  if ( (a_type != 5) && (a_type != 7) )
    {
    if (armour_types[a_type]) 
      occupied = 1;
     else
      armour_types[a_type] = 1;
    }
  if (occupied)
    {
    /* Ok, rewrite the notify later.. */
    notify_fail("You are already wearing this kinda object.\n");
    return 0;
    } /* if (occupied) */

  worn_ob += ({ ob });
  ob->set_in_use(1);
  worn_ac += (int)ob->query_ac();
  tell_object(this_object(),"You wear " + (string)ob->short() + ".\n");
  return 1;
       
} /* status hold_ob */

/* Another one I don't know what to do with.. */
