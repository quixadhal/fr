/* inherited by the common rooms in the domains*/
inherit "/std/room";
string dom_name;

string query_dom() { return dom_name; }
void set_dom(string str) { dom_name = str; }

void init() {
  ::init();
  add_action("do_list", "list");
  add_action("add_creator", "add");
  add_action("delete_creator", "del*ete");
  add_action("add_project", "pro*ject");
}

int do_list(string arg) {
  string *members, *domains, mast, mem_list;
  int i, j;

  if(arg == "all")
    domains = get_dir("/d/");
  else if(!arg)
    domains = ({ dom_name });
  else {
    notify_fail("Usage: list\n       list all\n");
    return 0;
  }

  if(sizeof(domains) > 1) write("All domains:\n");
  else write("This domain:\n");
  
  for(i=0; i<sizeof(domains); i++) {
    mast = "/d/" + domains[i] + "/master";
    members = (string *)mast->query_members(arg);
    printf("%8s has %2d members and is owned by %s.\n", domains[i],
      sizeof((string *)mast->query_members()),
      capitalize((string)mast->query_dom_lord()));
    mem_list = "";
    for(j=0; j<sizeof(members); j++)
      mem_list += capitalize(members[j]) + (j==sizeof(members)-1?".":",");
   write(mem_list + "\n\n");
  }
  return 1;
}

int add_creator(string arg) {
  string mast;
  
  if (!arg) {
    notify_fail("Usage: add <creator>\n");
    return 0;
  }
  arg = (string)this_player()->expand_nickname(arg);
  mast = "/d/" + dom_name + "/master";
  if((string)mast->query_lord() != geteuid(this_player())) {
    notify_fail("You are not the Lord of this Domain.\n");
    return 0;
  }
  if(!mast->add_member(arg)) {
    notify_fail("Failed to add " + capitalize(arg) + " to "+dom_name + ".\n");
    return 0;
  }
  write("Creator " + capitalize(arg) + " now added to " + dom_name + ".\n");
  return 1;
}

int delete_creator(string arg) {
  string mast;

  if (!arg) {
    notify_fail("Usage: delete <creator>\n");
    return 0;
  }
  arg = (string)this_player()->expand_nickname(arg);
  mast = "d/" + dom_name + "/master";
  if((string)mast->query_lord() != geteuid(this_player())) {
    notify_fail("You are not the Lord of this Domain.\n");
    return 0;
  }
  if (!mast->remove_member(arg)) {
    notify_fail("Failed to remove " + capitalize(arg)+" from "+dom_name+".\n");
    return 0;
  }
  write("Member " + capitalize(arg) + " removed from " + dom_name + ".\n");
  return 1;
}
