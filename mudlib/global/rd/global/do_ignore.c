// Coded by Dyraen.
// Communications master Begosh looked it over did his this and that and
// gladly approved to have it installed.

string *ignored;
 
static int do_ignore(string name) {
  string *names;
  int i;
  if (!name) {
    write("Currently ignored people are: "+implode(ignored, ", ")+"\n");
    write("Syntax: ignore <name> [name] ...\n");
    return 1;
  }
  names = explode(name, " ");
  for (i=0;i<sizeof(names);i++)
    if (!"/secure/login"->test_user(names[i])) {
      write("User "+names[i]+" does not exist.\n");
      names = delete(names, i, 1);
      i--;
    }
  if (!sizeof(names)) {
    write("No one is added.\n");
  } else
    write(implode(names, ", ")+" have been added to the ignored array.\n");
  ignored += names;
  return 1;
} /* do_ignore() */
 
static int do_unignore(string name) {
  string *names;
  int i;
  if (!name) {
    notify_fail("Syntax: unignore <name> [name] ...\n");
    return 0;
  }
  names = explode(name, " ");
  for (i=0;i<sizeof(names);i++)
    if (member_array(names[i], ignored) == -1) {
      write("User "+names[i]+" not in the ignored array, how can you "+
            "remove them?\n");
      names = delete(names, i, 1);
      i--;
    }
  if (!sizeof(names))
    write("No one removed from the array.\n");
  else
    write(implode(names, ", ")+" has been removed from the ignore array.\n");
  ignored = ignored - names;
  return 1;
} /* do_unignore() */
 
string *query_ignored() { return ignored; }
 
int query_ignore(string name) {
  return member_array(name,ignored) == -1?0:1;
} /* query_ignore() */
