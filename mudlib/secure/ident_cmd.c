/* Hamlet, Jan 1996.  -- This gets cloned to do the ident command.  The
                         Command is now more complex so integration can be
                         truly simple.
*/
object toident, querier;
object identd;
string pname;
string ipname;

varargs void dest_me(int i);

int do_ident(string name, object me) {
  seteuid("Root");
  if(!"/secure/master"->query_lord(geteuid(me)))
    return 0;
    
  toident = find_player(name);
  querier = me;
  pname = name;
  
  ipname = query_ip_name(toident);
  if(!ipname)
    ipname = query_ip_number(toident);
  
  if(!identd = clone_object("/secure/identd"))
    return 0;
    
  if(!identd->do_ident(toident, this_object())) {
    tell_object(me,"** Error with sockets or lack of authority.  "
                   "Check the log.\n");
    dest_me();
  }
  else
    call_out("dest_me",40,1);
  return 1;
}

void receive_ident_data(string userid, string hosttype) {
  if(!querier) {
    dest_me();
    return;
  }
  
  if( (userid == "none") && (hosttype == "available") )
    tell_object(querier,"\n** No Identd Available for "+capitalize(pname)+
                ".\n");
  else
    tell_object(querier,"\nInteractive: "+capitalize(pname)+" is "+
                   userid+"@"+ipname+" ("+hosttype+")\n");
                   
  dest_me();
}         

varargs void dest_me(int i) {
  if(i && querier)
    tell_object(querier,"** Ident timed out for "+capitalize(pname)+".\n");
  if(!i)
    remove_call_out("dest_me");
  
  destruct(this_object());
}
