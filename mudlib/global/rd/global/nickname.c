/*
 * The great and wonderful alias driver by me ;)
 * pinkfish.
 */
// Just a little help from Inky for a size limit 
// Added auto-nicknames - Dyraen, Jan '95
// 1995 Jul 19  Dyraen      Upped MAX_NICK to 40.
 
static mapping auto_nicknames;
mapping map_nicknames;
 
#define MAX_NICK 40   // Max number of nicknames - Inky.
#define ME ([ "me" : (string)this_player()->query_name() ])
 
void create() {
  auto_nicknames = (["pc":"platinum coins","gc":"gold coins",
    "sc":"silver coins","cc":"copper coins","bc":"brass coins",]);
}
 
mapping query_nicknames() { return map_nicknames + ([ ]); }
 
mapping query_auto_nicknames() { return ME + auto_nicknames; }
 
mapping query_all_nicknames() { return map_nicknames + ME + auto_nicknames; }
 
void nickname_commands() {
  add_action("delete_nickname", "dn*ickname");
  add_action("nickname", "ni*ckname");
  add_action("flush_nickname","flushnickname");
}
 
int add_nickname(string str) {
  string s1,s2;
  int i;
 
  if (sscanf(str,"%s %s",s1,s2)!=2) {
    notify_fail("You are a frog\n");
    return 0;
  }
  if (!map_nicknames)
    map_nicknames = ([ ]);
      // Added by Inky 6-25-94 to limit list size
  if (sizeof(map_nicknames) > MAX_NICK) {
    if (!this_player()->query_creator()) {
      write("Your nickname list is full.  Consider "+
        "dnickname or flushnickname to make space.\n");
      return 1;
    }
    write("Consider trimming some nicknames ...\n");
  }
  if (!map_nicknames[s1]) {
    map_nicknames[s1] = s2;
    write("Added nickname "+s1+" as "+s2+".\n");
    return 1;
  }
  write("Changed nickname "+s1+" from "+map_nicknames[s1]+" to "+s2+".\n");
  map_nicknames[s1] = s2;
  return 1;
}
 
   // Added by Inky 
int flush_nickname(string arg) {
   if (!arg || (arg != "really")) {
      write("This command will flush all your nicknames.\n");
      write("Use 'flushnickname really' to commence.\n");
      return 1;
   }
   map_nicknames = ([ ]);
   write("All nicknames flushed.\n");
   return 1;
}
 
string expand_nickname(string str) {
  string *array;
  int i,j;
 
  if (stringp(str))
    array = explode(lower_case(str)," ");
  else
    return str;
  if (!map_nicknames)
    map_nicknames = ([ ]);
  for (i=0;i<sizeof(array);i++) {
    if (map_nicknames[array[i]])
      array[i] = map_nicknames[array[i]];
    if (array[i] == "me") 
      array[i] = (string)this_player()->query_name();
    if (auto_nicknames[array[i]])
      array[i] = auto_nicknames[array[i]];
  }
  return implode(array," ");
}
 
int delete_nickname(string str) {
  int i;
  if (!map_nicknames)
    map_nicknames = ([ ]);
  if (!map_nicknames[str]) {
    notify_fail("That nickname does not exist.\n");
    return 0;
  }
  map_nicknames = m_delete(map_nicknames, str);
  write("Deleted nickname : "+str+"\n");
  return 1;
}
 
int print_nicknames() {
  int pos, i, cols;
  string str, str1, str2, bit, *tmp;
  mapping tmp_nicknames;
 
  bit = "";
  str1 = "";
  str2 = "";
  if (!map_nicknames)
    map_nicknames = ([ ]);
  tmp = m_indices(map_nicknames);
  cols = (int)this_player()->query_cols();
  write("Player Defined :\n");
  for (i=0;i<sizeof(tmp);i++) {
    str = tmp[i]+": "+map_nicknames[tmp[i]]+"  ";
    if (strlen(str)>39)
      printf(tmp[i]+": %-=*s\n", cols - strlen(tmp[i]), map_nicknames[tmp[i]]);
    else if (strlen(str) > 19)
      str1 += str+"\n";
    else
      str2 += str+"\n";
  }
  if (strlen(str1))
    printf("%-#*s\n", cols, str1);
  if (strlen(str2))
    printf("%-#*s\n", cols, str2);
 
  bit = "";
  str1 = "";
  str2 = "";
  if (!auto_nicknames)
    auto_nicknames = ([ ]);
  tmp_nicknames = ME + auto_nicknames;
  tmp = m_indices(tmp_nicknames);
  cols = (int)this_player()->query_cols();
  write("Auto Defined :\n");
  for (i=0;i<sizeof(tmp);i++) {
    str = tmp[i]+": "+tmp_nicknames[tmp[i]]+"  ";
    if (strlen(str)>39)
      printf(tmp[i]+": %-=*s\n", cols - strlen(tmp[i]), tmp_nicknames[tmp[i]]);
    else if (strlen(str) > 19)
      str1 += str+"\n";
    else
      str2 += str+"\n";
  }
  if (strlen(str1))
    printf("%-#*s\n", cols, str1);
  if (strlen(str2))
    printf("%-#*s\n", cols, str2);
  return 1;
}
 
int nickname(string str) {
  string s1,s2;
  int i;
 
  if (!map_nicknames)
    map_nicknames = ([ ]);
  if (!str || str == "")
    return print_nicknames();
 
  if (sscanf(str,"%s %s",s1,s2)!=2) {
    s1 = str;
    if (map_nicknames[s1]) {
      write("Setting for nickname "+str+" is "+map_nicknames[str]+".\n");
      return 1;
    }
    if (auto_nicknames[s1]) {
      write("Setting for nickname "+str+" is "+auto_nicknames[str]+".\n");
      return 1;
    }
    if (s1 == "me") {
      write("Setting for nickname "+str+" is "+
            (string)this_player()->query_name()+".\n");
      return 1;
    }
    notify_fail("That nickname does not exist.\n");
    return 0;
  }
  return add_nickname(str);
}
