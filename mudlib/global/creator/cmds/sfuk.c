/* Sorted netstat for catching those multiplayers.  Lists player names,
   IP name, and room they're in, sorted by IP number.
*/
/* Hamlet wrote June 1995 */
/* Grimbrand wrote some mean nasty additions Jan 1996. */
/* yes... the code needs optimized.  I'm lazy, what can I say? */
/* Hamlet added ident stuff, Jan 1996 */
/* Use peopler->get_people() for the object *players - Radix July 96 */

#include <standard.h>
#include <cmd.h>
inherit CMD_BASE;

void setup()
{
  position = 1;
}

static int cmd(string str, object me) {
  object *players;
  string *info;
  int *sortstuff;
  int sz;
  int i,j,k;
  int least, tmp;
  int relevant, hits;
  string ipn;
  object ob;
  int LORD_PER = 0;

  if("/secure/master"->query_lord(this_player(1)->query_name()))
    LORD_PER = 1;
  
  /* initialization */
  if(!str) 
    players = users();
  else
    players = (object *)"/obj/handlers/peopler"->get_people(str);
  sz = sizeof(players);
  info = allocate(4 * sz);
  sortstuff = allocate(sz);
  for(i=0;i<sz;i++) {
    info[i*4]       = query_ip_number(players[i]);
    info[(i*4)+1]   = players[i]->query_name();
    if(LORD_PER && (tmp = players[i]->query_ident()))
      info[(i*4)+2] = tmp+"@"+query_ip_name(players[i]);
    else
      info[(i*4)+2]   = query_ip_name(players[i]);
    if(environment(players[i]))
      info[(i*4)+3] = virtual_file_name(environment(players[i]));
    else
      info[(i*4)+3] = "No environment";
  }
  
  for(i=0;i<sz;i++)
    sortstuff[i] = i*4;
    
  /* sorting */
  for(j=0;j<(sz-1);j++) {
    least = j;
    for(k=j+1;k<sz;k++)
      if( info[sortstuff[k]] < info[sortstuff[least]] )
        least = k;
    
    tmp = sortstuff[least];
    sortstuff[least] = sortstuff[j];    
    sortstuff[j] = tmp;
  }
                    
  /* output */
    tell_object(this_player(),
                "Name         IP Name                       Room\n"); 

    for(i=0;i<sz;i++) {
      k = strlen(info[sortstuff[i]+3]); 
      j = k - 36;
      if( (tmp = strlen(info[sortstuff[i]+2]) - 29) > 0)
        j += tmp;
      if(j<0) j = 0;
    
      tell_object(this_player(),sprintf("%-13s%-29s %-s\n",
                  info[sortstuff[i]+1], info[sortstuff[i]+2], 
                  info[sortstuff[i]+3][j..k]));
    }
  return 1;
}
