/* identd - Dyraen */
/* patches -- Hamlet.  Fixed it so VAXen will actually reply.
                       Modifications so it can be built into the mudlib.
                       Instead of telling to 'me', now it either logs an
                       error to /log/ident.errors or, on success, does
                       me->receive_ident_data(userid, hosttype);
*/
/* Oh, don't blame me for "destructo".  I never liked He-Man. -- Hamlet */

#include <socket.h>

#define ERROR_LOG "ident.errors"

#define END { call_out("destructo",0); return 0; }
#define V_END { call_out("destructo",0);  return; }

object tp, ob;
string ip_num, iname;
int ip_port;

void log_error(string str);

int do_ident(mixed name, object me) {
  int fd, err;

  if (!name) END;
  if (!me) END;

  if (objectp(name)) ob = name;
  if (!ob)
    ob = find_player(name);
  if (!ob) END;

  if( (me && (me != ob)) && (!"/secure/master"->query_lord(geteuid(me))) ) 
    END;

  ip_num = query_ip_number(ob);
  iname = ob->query_name();
  ip_port = ob->ip_port();

  tp = me;

  err = socket_create(STREAM, "read_cb", "close_cb");
  if (err < 0) {
    log_error("** Socket Create Error: "+socket_error(err)+".\n");
    END;
  }
  fd = err;
  err = socket_bind(fd, 0);
  if (err < 0) {
    log_error("** Socket Bind Error: "+socket_error(err)+".\n");
    END;
  }
  err = socket_connect(fd, ip_num+" 113", "read_cb", "write_cb");
  if (err < 0) {
    log_error("** Socket Connect Error: "+socket_error(err)+".\n");
    END;
  }
  call_out("destructo",40);
  return 1;
} /* do_ident() */

void read_cb(int fd, string mess) {
  string userid, hosttype;
  string junk, junk2;
  int WAS_ERROR = 0;

  mess = replace_string(mess,"\n","");
  mess = replace_string(mess,"\r","");

  /* Note these if()s have a ; after them.  we don't do anything on success 
     :)  -- Hamlet
  */
    /* First, we'll see if it's ye standard unix output */
  if(sscanf(mess,"%s : USERID : %s : %s",junk,hosttype,userid) == 3);
    /* This is an odd UNIX format... maybe an old one. */
  else if(sscanf(mess,"%s: USERID: %s: %s",junk,hosttype,userid) == 3);
    /* Screwed up sVr4 system had this... */
  else if(sscanf(mess,"%s : USERID : %s :%s",junk,hosttype,userid) == 3);
    /* Might be a nasty, nasty VAX */
  else if(sscanf(mess,"%s:USERID:%s:%s",junk,hosttype,userid) == 3);
    /* Next few just keep us from logging junk from misinstalled authd's */
  else if(sscanf(mess,"%s: ERROR : NO-USER",junk) == 1)  WAS_ERROR = 1;
  else if(sscanf(mess,"%s:ERROR:NO-USER",junk) == 1)  WAS_ERROR = 1;
  else if(sscanf(mess,"%s: ERROR: NO-USER",junk) == 1)  WAS_ERROR = 1;
  else if(sscanf(mess,"%s: ERROR : UNKNOWN-ERROR",junk) == 1)  WAS_ERROR = 1;
  else if(sscanf(mess,"IPAD %s [%s]",junk,junk2) == 2)  WAS_ERROR = 1;
  else if(sscanf(mess,"Sorry, there are already %s",junk) == 1)  WAS_ERROR = 1;
  else {  /* We have an unknown response format or something else screwy */
    log_file(ERROR_LOG,"!ident "+iname+", "+ip_num+": "+
             mess+"\n");
    WAS_ERROR = 1;
  }

  /* Okay, some machines are far far too helpful, and the above stuff ends
     up catching data in userid that we really didn't want.  Maybe some day
     that stuff might be of some value.  Right now, let's just log it so
     we can see what we got and return it as part of host-type.
  */
  if(!WAS_ERROR && ((sscanf(userid,"%s %s",junk,junk2) == 2) ||
                    (sscanf(userid,"%s,%s",junk,junk2) == 2))) {
    userid = junk;
    hosttype += " : "+junk2;
    /* Let's only log ones we've never seen, come to think of it */
    if(junk2[0..7] == "#VMS_PID");
    else if(junk2[0..2] == "CLI");
    else
      log_file(ERROR_LOG,"$nifty: "+iname+", "+ip_num+": "+
               mess+"\n");
  }

  if(tp) {
    if (iname && userid)
      tp->receive_ident_data(userid,hosttype);
    else
      tp->receive_ident_data("none","available");
    socket_close(fd);
  }
  call_out("destructo",0);
} /* read_cb() */

void write_cb(int fd) {
// int rport, i, j, k, err;
  int k, err;

  if (!ob) {
    socket_close(fd);
    V_END;
  }

  sscanf(explode(socket_address(ob)," ")[1],"%d",k);

/*  Dunno what this stuff was for, but it doesn't seem needed with v21.7.
    Maybe sockets weren't directly mapped before...  - Hamlet
  i = k/256;
  j = k%256;
  rport = j*256+i;
*/

//   err = socket_write(fd, rport+",2001\n");
  err = socket_write(fd, sprintf("%d,%d\r\n",k,ip_port));
  if (err <0) {
    log_error("** Socket Write Error: "+socket_error(err)+".\n");
    V_END;
  }
} /* write_cb() */

void close_cb(int fd) {
  if (tp) {
    tp->receive_ident_data("none","available");
    V_END;
  }
} /* close_cb() */

void destructo() {
  if (clonep(this_object())) {
    remove_call_out("destructo");
    destruct(this_object());
  }
} /* destructo() */

void log_error(string str) {
  log_file(ERROR_LOG,"** "+ctime(time())+" "+iname+": "+str);
}
