/* The first attempt on a Retire command.
 * It will make the players able to delete their own charachters. 
 * Baldrick march '94 
 * Put it in /secure/master and add it to master.c (#include).
 * Add an add_action and a call in player.c (test on force!)
 */
#define MAX_RETRYS 1
/* The deleting of the player. */
/* have to get root access to be able to do the RM of the file. */
/* Done by putting the whole thingie in the master. */

int do_deathjob(object victim)
  {
  int name;
  // write ("You made it !" + name + "\n");

  if (!previous_object() == "/std/living/death.c")
   return 0;

  victim->add_property("guest",1);
  name = victim->query_name();

  rm ("/players/" + name[0..0] + "/" + name + ".o");
  victim->quit();

  return 0;

} /* do_retire */

int query_prevent_shadow() { return 1; }

