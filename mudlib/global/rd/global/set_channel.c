void create() { seteuid("Root"); }
int trams(string str)
{
    return find_player(str)->add_channel("chat","on");
}

int remove_newbie_chan(string str)
{
    return find_player(str)->remove_channel("newbie");
}

int do_thel(object ob)
{
   return ob->add_t_channel("thelbane","on");
}

int block_chat(object pl, string reason) {
  if (!"/secure/master"->query_lord(geteuid(this_player())))
    return 0;
  if (!objectp(pl))
    return 0;
  if (!stringp(reason))
    return 0;
  log_file("CHAT",ctime(time())+" "+this_player()->query_cap_name()+
           " blocked "+pl->query_cap_name()+"'s chat.\nReason: "+
           reason+".\n");
  pl->add_channel("chat","nope");
  pl->do_efun_write("You have abused chat repeatedly, and as a "+
                    "result your chat privileges have been blocked "+
                    "for an extended period of time. If you wish to "+
                    "have your chat re-enstated, then take your case "+
                    "to "+this_player()->query_cap_name()+".\n");
  return 1;
} /* block_chat() */

int remove_chat(object pl, string reason) {
  if (!"/secure/master"->query_lord(geteuid(this_player())))
    return 0;
  if (!objectp(pl))
    return 0;
  if (!stringp(reason))
    return 0;
  log_file("CHAT",ctime(time())+" "+this_player()->query_cap_name()+
           " removed "+pl->query_cap_name()+"'s chat.\nReason: "+
           reason+".\n");
  pl->remove_channel("chat");
  pl->do_efun_write("You have had chat removed. To get it back, "+
                    "you will need to redo the chat quest. Repeated "+
                    "offences will lead to your losing of the channel "+
                    "for an extended period of time.\n");
  return 1;
} /* remove_chat() */
