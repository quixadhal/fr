int create_domain(string name, string lord) {
  string file;

  if (!high_programmer(geteuid(previous_object())) ||
      !interactive(previous_object()))
    return 0;
  if (high_programmer(capitalize(name))) {
    write("Invalid name....\n");
    return 0;
  }
  if (file_size("/d/"+name) != -1) {
    write("Domain already exists (or invalid).\n");
    return 0;
  }
  if (sizeof(explode(name, "/")) > 1) {
    write("Invalid to have a / in the domain name.\n");
    return 0;
  }
  if (!"/secure/login"->test_creator(lord)) {
    write("The lord must exist.... and be a creator already.\n");
    return 0;
  }
  mkdir("/d/"+name);
  add_lord(lord);
  file = read_file("/std/dom/master.c");
  write_file("/d/"+name+"/master.c", "#define LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/master.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/master.c", file);
  file = read_file("/std/dom/common.c");
  write_file("/d/"+name+"/common.c",
             "#define DOM_TITLE \"the domain of "+name+"\"\n");
  write_file("/d/"+name+"/common.c", "#define LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/common.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/common.c", file);
  file = read_file("/std/dom/loader.c");
  write_file("/d/"+name+"/loader.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/loader.c", file);
  save_object("/secure/master");
  write("Created domain "+name+".\n");
  log_file("PROMOTIONS", "Domain "+name+" created with a lord of "+lord+
              " by "+geteuid(previous_object())+"\n");
  return 1;
} /* create_domain() */

int create_creator(string name) {
  string file;

  seteuid("Root");
  if (!query_lord(geteuid(previous_object()))
      || !interactive(previous_object()))
    return 0;
  if (!"/secure/login"->test_user(name))
    return 0;
  if (file_size("/w/"+name) != -1) {
    write("Directory already exists or something.\n");
    return 0;
  }
  mkdir("/w/"+name);
  file = read_file("/std/creator/workroom.c");
  write_file("/w/"+name+"/workroom.c", "#define CREATOR \""+name+"\"\n");
  write_file("/w/"+name+"/workroom.c", file);
  log_file("PROMOTIONS", name+" promoted to creator by "+
           geteuid(previous_object())+"\n");
  write("Creator "+name+" promoted.\n");
  if (find_player(name)) {
    find_player(name)->set_creator(1);
    find_player(name)->save();
    tell_object(find_player(name), "You have been promoted to creator by "+
      geteuid(previous_object())+".\n");
    tell_object(find_player(name), "Be sure to look over the directories, "+
      "especially /doc.  'help create' will give you a brief list of commands."+
      "  Bother someone about getting into a domain.  Womble on, mighty frog.\n");
  } else {
    write_file("/players/"+name[0..0]+"/"+name+".o", "creator 1\napp_creator 1\n");
  }
  return 1;
} /* create_creator() */

int demote_creator(string str) {
  string name, reason;

  if (!query_lord(geteuid(previous_object())) ||
      !interactive(previous_object()))
    return 0;
  if (!sscanf(str, "%s %s", name, reason) != 2)
    return 0;
  if (!"/secure/login"->test_creator(name))
    return 0;
  if (query_lord(name)) {
    write("Cannot demote lords.\n");
  }
  write_file("/log/DEMOTE", name+" demoted by "+
              previous_object()->query_cap_name()+" at "+ctime(time())+
              "\nReason: "+reason+"\n");
  if (find_player(name)) {
    find_player(name)->set_creator(0);
    find_player(name)->save();
    tell_object(find_player(name),
                "You have just been demoted by "+
                previous_object()->query_cap_name()+", whos been a naught "+
                "person then?\n");
  } else
    write_file("/players/"+name[0..0]+"/"+name+".o", 
                "creator 0\napp_creator 0\n");
  write("Creator "+name+" demoted.\n");
} /* demote_creator() */
