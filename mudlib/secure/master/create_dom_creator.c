/*
    Prototype functions.
*/
int	create_creator( string name );
int	create_domain( string name , string lord );
int	demote_creator( string str );

/* Do we want this to stay ? Baldy.. */
status	eligible_creator( object player );

/*
    Functions.
*/
int create_domain(string name, string lord) {
  string file;
  
  if (!high_programmer(geteuid(this_player()))) {
    tell_object(this_player(), "Not enough power.\n");
    return 0;
  }
  if (high_programmer(capitalize(name))) {
    tell_object(this_player(), "Invalid name....\n");
    return 0;
  }
  if (file_size("/d/"+name) != -1) {
    tell_object(this_player(),"Domain already exists (or invalid).\n");
    return 0;
  }
  if (sizeof(explode(name, "/")) > 1) {
    tell_object(this_player(),"Invalid to have a / in the domain name.\n");
    return 0;
  }
  if (!"/secure/login"->test_creator(lord)) {
    tell_object(this_player(),"The lord must exist and be a creator.\n");
    return 0;
  }
  mkdir("/d/"+name);
  add_lord(lord);
  file = read_file("/std/dom/master.c");
  write_file("/d/"+name+"/master.c", "#define DOM_LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/master.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/master.c", file);
  file = read_file("/std/dom/common.c");
  write_file("/d/"+name+"/common.c",
             "#define DOM_TITLE \"the domain of "+name+"\"\n");
  write_file("/d/"+name+"/common.c", "#define DOM_LORD \""+lord+"\"\n");
  write_file("/d/"+name+"/common.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/common.c", file);
  file = read_file("/std/dom/loader.c");
  write_file("/d/"+name+"/loader.c", "#define DOMAIN \""+name+"\"\n");
  write_file("/d/"+name+"/loader.c", file);
  save_object("/secure/master",1);
  write("Created domain "+name+".\n");
  log_file("PROMOTIONS", "Domain "+name+" created with a lord of "+lord+
              " by "+geteuid(previous_object())+"\n");
  return 1;
} /* create_domain() */

int create_creator(string name) {
  string file;

  seteuid("Root");
  if (!query_lord(geteuid(previous_object())))
    return 0;
  if (!"/secure/login"->test_user(name))
    return 0;

    /* should make the directory test askif the creator shall be promoted
       anyway*/

  if (file_size("/w/"+name) != -1) {
    write("Directory already exists or something.\n");
    return 0;
  }
  mkdir("/w/"+name);
  file = read_file("/std/creator/workroom.c");
  write_file("/w/"+name+"/workroom.c", "#define CREATOR \""+name+"\"\n");
  write_file("/w/"+name+"/workroom.c", file);
  file = read_file("/std/creator/workroom2.c");
  write_file("/w/"+name+"/workroom2.c","#define CREATOR \""+name+"\"\n");
  write_file("/w/"+name+"/workroom2.c",file);
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

  if (!query_lord(geteuid(previous_object())))
    return 0;
  if (sscanf(str, "%s %s", name, reason) != 2) {
    notify_fail("You need to give a reason!\n");
    return 0;
  }
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
  return 1;
} /* demote_creator() */

/* Do we need this ? Baldy.. */
status eligible_creator( object player )
{
    int		age;
    string	age_str;
    int		level;
    string	reasoning;

//  Why isn't write() columnizing for this object????  I'm forced to put
//  in my own newlines.  Hopefully, no one has a <79 column terminal.

    reasoning =
  "  You do not have a *right* to create here.  In order to enhance your\n"
+ "chances to be promoted, you should demonstrate by your actions that you\n"
+ "are worthy.\n"
+ "  If our Creators find lots of your bug, typo, and idea reports in their\n"
+ "directories, then your chances are improved.  If you have been a trouble-\n"
+ "maker here, your chances are very slim.  Harrassing the Lords for a\n"
+ "position will not help your chances either.\n"
+ "  Having access to a MUD's file system is a great responsibility.  It\n"
+ "cannot be given out to strangers who have not demonstrated their trust-\n"
+ "worthiness.  After investing a fair amount of your time and energy in\n"
+ "playing at DiscWorld, you are less likely to try to hurt it.  This is\n"
+ "why we cannot give out instant creatorships unless we know you from\n"
+ "elsewhere.  Please try to be understanding about our policy.\n\n";

    age   = - ( (int) player->query_time_on() );
    level = player->query_level();

    if ( ( level >= 100 ) && ( age > 86400 ) )
    {
	write(
  "  You have achieved the *minimum* requirements necessary to apply for a\n"
+ "creatorship at Final Realms.  You must now pass a review of the Lords to be\n"
+ "accepted.\n"
+ reasoning );
	return 1;
    }
/*
	Player does not qualify.  Tell him why.
*/
    age_str = "";

    if ( age >  86400 )  age_str += sprintf( "%d day" , age/86400 );
    if ( age > 172800 )  age_str += "s";

    if ( age%86400 > 3600)
    {
	if ( age > 86400 )  age_str += " and ";

	age_str += sprintf( "%d hour" , (age%86400)/3600 );
    }
    if ( age%86400 > 7200)  age_str += "s";

    write(
  "  The *minimum* requirements to apply for a creatorship at DiscWorld are\n"
+ "an overall level of 100 from your guild and an age of at least one day.\n"
+ "Your current level is " + level + " and your age is " + age_str + ".\n"
+ reasoning );
    return 0;
}
/* eligible_creator() */

/* EOF */
