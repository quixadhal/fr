/* The "new" alignment system.
 * I am putting all alignment stuff here instead of that over poputaled player.
 * And the meaningof this is to make the whole alignment system more usable.
 * Baldrick, april '94
 * The really difficult stuff will be to implement workable
 * lawful / chaotic stuff, and test on it.
 */

int alignment;
string playerset_alname;
int playerset_al;

// Prototypes:
int set_playerset_alname(string goof);

void set_align(int i) 
  {
  alignment = i;
  return;
}

int adjust_align(int i)
  {
  if (alignment !=0)
    alignment += ( (i*10) / (alignment<0 ? - alignment:alignment) ); 
   else
    alignment += i;
  return alignment;
}

int query_align()
  {
  return alignment;
}

string query_align_name()
  {
  switch (alignment)
    {
    case -10000 .. -501 : return "extremely good";
    case -500 .. -200   : return "very good";
    case -199 .. -76    : return "good"; 
    case -75 .. 75      : return "neutral";     
    case 76 .. 199      : return "evil";     
    case 200 .. 500     : return "very evil";     
    case 501 .. 50000   : return "extremely evil";     
    }
} /* Query alias Name */

int do_alsetting()
  {
  if (playerset_alname)
    return notify_fail("Alignment already set, too late!\n");
  write ("Possible alignments:\n  - evil (e)\n  - neutral (n)\n  - good (g)\n" +
         "Enter choice:");
  input_to("set_playerset_alname");
  return 1;
}

int set_playerset_alname(string goof)
  {
  switch (goof)
    { 
    case "e":
    case "evil":
      playerset_alname = "evil"; 
      playerset_al = 250; 
      break;

    case "n":
    case "neutral":
      playerset_alname = "neutral"; 
      playerset_al = 0; 
      break;

    case "g":
    case "good":
      playerset_alname = "good"; 
      playerset_al = -250; 
      break;
    
    default:
      write ("Not set correctly, try once more:");
      input_to("set_playerset_alname");
    }
  write("Player Alignment set to "+playerset_alname+".\n");
  alignment = playerset_al;
  return 1;
}

string query_playerset_alname()
  {
  return playerset_alname;
} 

/* This is the nice part.. it reutrs 1 if the player plays his alignment..
 * Maybe not needed here, but nice to have..
 */
int compare_alignment(string compstr)
  {
  string name;

  name = query_align_name();
  if (compstr == name || compstr == name[5..8])
    return 1;
  return 0; 
}
