/*** Resurrect ***/
inherit "/std/spells/patch.c";

/* find_unique_match() does a find match that ensures the returned 
   object list contains no duplicates
   find_one_match() returns only the first matched object
*/
mixed find_unique_match(string find,mixed in);
mixed find_one_match(string find,mixed in);
/*** modified by Eerevann ***/

/*** Sphere Necromantic ***/
/*** Level 7th ***/

#define SP_NAME "Resurrect"
#define GP_COST 14

/*** Help file here ***/
string help() {
   return
   "\n\n"+
   "Spell Name: "+SP_NAME+"\n"+
   "Sphere:  Necromantic\n"+
   "Level:  7th\n"+
   "Gp Cost: "+GP_COST+"\n"+
   "Description: \n"+
   "  This spell ressurects someone after they have died.  It does not remove "+
   "one of your lives, unlike "+
   "raise, and turns you back from being a ghost.\n\n";
}

mixed spell(string str, int cast);
 
int cast_spell(string str) {
  mixed ret;
 
  str = (string)this_player()->expand_nickname(str);
  ret = spell(str, 1);
  if (stringp(ret)) {
    notify_fail(ret);
    return 0;
  }
  return 1;
}
 
mixed spell(string str, int cast) {     
  mixed ob;

  if (!str || str == "")
    return "You try to ressurect nothing and fail miserably.\n";
  ob = find_one_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    return "Who is " + capitalize(str) + "?\n";
  if (!living(ob))
    return (string)ob->query_cap_name() + " refuses to be brought to life.\n";
  if (!ob->query_property("dead"))
    return (string)ob->query_cap_name() + " is not dead ... yet.\n";
  if (ob->query_property("noregen"))
    return "Death tells you: HOLD ON, I'M NOT FINISHED WITH THEM YET.\n";
  if (cast && (int)this_player()->adjust_gp(-GP_COST) < 0)
    return "Too low on power.\n";
  write("You call upon the gods to ressurect "+(string)ob->query_cap_name()+
    " from " + (string)ob->query_possessive() + " immaterial state by "+
    "hitting "+ob->query_pronoun()+" with a lightning bolt..\n");
  tell_object(ob, (string)this_player()->query_cap_name() +
    " summons the gods for you, and incidently hits you with a lightning "+
    "bolt.  It doesn't seem to hurt.\n");
  say((string)this_player()->query_cap_name() + " stares intently into space, "+
    "you hear a vage rumbling in the distance, suddenly a lightning bolt "+
    "sears through the sky and hits "+ob->query_cap_name()+" ressurecting "+
    " them from the dead.\n", ob);

  ob->adjust_con(-1);
  ob->remove_ghost();
  ob->adjust_max_deaths(1);

  return (random(2000));
}