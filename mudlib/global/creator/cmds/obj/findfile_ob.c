/* Hamlet - Apr 1996
   Finds a filename, given a starting path.  Returns all matches.
   Might take a while.  Look at the findfile command.  It calls it.
*/

/* The maximum size of a dir that will be allowed to be searched.
   Anything bigger will be skipped.
*/
#define MAX_DIR_SIZE 1000

/* This is the number of files to be processed before halting until
   the next heartbeat.  The higher this is, the more lag you'll experience,
   but the faster the search will complete.  Lower is just the opposite.
   Individual directories will not be divided among heartbeats, so
   MAX_DIR_SIZE is actually the hard limit and this is the soft limit.
*/
#define MAX_NUM_FILES 250

/* These are directories to avoid searching.  Any recursive dirs had
   better be in here.  Also dirs that are just not interesting enough
   to search through.
*/
#define AVOID_DIRS ({ "/players", "/creators", "/save", "/w/baldrick/oldlib" })

string fname;
string *dirs;
string *match;
string *tmp;
int i;
int MATCHED;
int RUNNING;
int ALL_MATCHES;
object me;

int num_files_searched;
int num_dirs_searched;
int iterations;

void do_a_pass();
void dest_me();

nomask void find_file(object arg_me, string path, string arg_fname, 
                      int ALL) {
  if(this_player(1))
    seteuid(geteuid(this_player(1)));
  else
    seteuid(geteuid(arg_me));
    
  tmp = arg_me->get_files(path);
  dirs = ({ });
  i = 0;
  MATCHED = 0;
  fname = arg_fname;
  me = arg_me;
  ALL_MATCHES = ALL;
  RUNNING = 1;

  num_files_searched = 0;
  num_dirs_searched = 0;
  iterations = 0;
    
  do_a_pass();
}

void do_a_pass() {
  string *tmp2 = ({ });
  int j,k;
  int current_files = 0;
  string *tmpdirs;
  string outstr = "";

  if(!me) {
    dest_me();
    return;
  }
  
  if(!sizeof(tmp)) {  /* We're done */
    tell_object(me,"\nFindfile search completed.  There were "+
                   MATCHED+" matches.\n");
    dest_me();
    return;
  }

  /* Actually display last iteration's matches. */
  if(sizeof(match = regexp(tmp,fname))) {
    MATCHED += sizeof(match);
    for(j=0; j<sizeof(match); j++)
      outstr += "Found: "+match[j]+"\n";
  }

  if(strlen(outstr))
    tell_object(me,outstr);
    
  if(!ALL_MATCHES && MATCHED) {
    tell_object(me,"\nFindfile search completed.\n");
    dest_me();
    return;
  }
  
  /* Move any directories found last iteration into the to-search list. */
  tmpdirs = allocate(sizeof(tmp));
  k = 0;
  
  for(j=0;j<sizeof(tmp);j++)
    if(file_size(tmp[j]) == -2) {
      tmpdirs[k] = tmp[j];
      k++;
    }

  num_dirs_searched += k;
  tmpdirs = tmpdirs[0..k-1];
  dirs += tmpdirs;
  tmp = ({ });
  
  /* Loop until we've found 'enough' files or we run out of data. */
  for(;i<sizeof(dirs);i++) {
    /* Are we avoiding this dir? */
    for(j=0;j<sizeof(AVOID_DIRS);j++)
      if(AVOID_DIRS[j] == dirs[i])
        break;
        
    if(j != sizeof(AVOID_DIRS)) {
      tell_object(me,"Skipping "+dirs[i]+".\n");
      continue;
    }
    else if(dirs[i][strlen(dirs[i])-1..strlen(dirs[i])-1] != "/")
      tmp2 = get_dir(dirs[i]+"/");
    else
      tmp2 = get_dir(dirs[i]);

    if(sizeof(tmp2) > MAX_DIR_SIZE) {
      tell_object(me,dirs[i]+" is too huge.  Skipping...\n");
      continue;
    }

    /* defer huge dirs until the next hb */
    if( (sizeof(tmp2) > MAX_NUM_FILES) && sizeof(tmp) )
      break;
      
    current_files += sizeof(tmp2);
    
    for(j=0;j<sizeof(tmp2);j++)
      if(dirs[i] == "/")
        tmp += ({ "/" + tmp2[j] });
      else
        tmp += ({ dirs[i] + "/" + tmp2[j] });
    
    /* do we have 'enough' files yet? */
    if(sizeof(tmp) > MAX_NUM_FILES) {
      i++;
      break;
    }
  }
  
  num_files_searched += current_files;
  iterations++;

  /* Optimization to try to speed array addition. */
  if(i > MAX_NUM_FILES) {
    dirs = dirs[i..sizeof(dirs)-1];
    i = 0;
  }

  if(!me) 
    dest_me();
  else
    call_out("do_a_pass",1);
}

void dest_me() {
  if(me)
    tell_object(me,"\nThere were "+num_dirs_searched+
                   " directories searched and "+num_files_searched+
                   " files considered,\nin "+iterations+" heartbeats.\n");
  destruct(this_object());
}

void reset() {
  if(!me || !RUNNING)
    dest_me();
}

int HALT(object per) {
  if(per == me) {
    remove_call_out("do_a_pass");
    tell_object(me,"\nFindfile search halting.  There were "+
                   MATCHED+" matches found.\n");
    dest_me();
    return 1;
  }
  
  return 0;
}

object PERSON_RUNNING_SEARCH() {  return me;  }
