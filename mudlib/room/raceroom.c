inherit "std/room";
#define PATH "/doc/races/"

setup() 
{
  string human, halfelf, elf, halfling, orc, halforc, lizardman;
  string gnome, dwarf, goblin, drow;

// added by Radix for "no new" players from the site.
// REAL ugly but works  (:   2-20-95
   clone_object("/room/start/nonew")->move(this_object());
// following added by Radix the raceroom fixer
// disallow all combat in here, should anyhow   4-7-95

  set_light(60);
  set_short("The Hall of Creation");
  set_long(
"Your immaterial form has found it's way to the Hall of Creation.  Here, you "+
"will determine in part what you will become by selecting your race.  You "+
"immediately notice several large statues supporting the high-arched ceiling "+
"here.  Depicted herein are all the races: Drow, Dwarf, Elf, Half-Elf, Gnome, "+
"Goblin, Halfling, Human, Lizard-Man, Orc, and Half-Orc.\n\n"+
"You think that if you examined a statue, you might find out more about what "+
"that Race represents.\n\n"+
"When you have chosen your race after careful research (For you will only be "+
"allowed to choose -once-!) you must type:\n"+
"\n"+
"become <race>       For Example: become human\n\n");
add_item("statue","The statues are beautifully carved of solid granite, each "+
"one respresenting a race that you might choose to become.  If you would like "+
"to learn more about a particular race, you must examine one specifically, "+
"For example: exa human    -or-   exa drow.\n");
add_item("hall","The Hall of Creation is where all new mortals begin the "+
	"shaping of their lives.\n");
add_item("ceiling","The arched ceiling is painted with portraits of all the "+
	"ruling dieties and Gods.\n");

  human = read_file(PATH+"human");
  halfelf = read_file(PATH+"half-elf");
  elf = read_file(PATH+"elf");
  drow = read_file(PATH+"drow");
  dwarf = read_file(PATH+"dwarf");
  gnome = read_file(PATH+"gnome");
  halfling = read_file(PATH+"halfling");
  halforc= read_file(PATH+"half-orc");
  orc= read_file(PATH+"orc");
  goblin = read_file(PATH+"goblin");
  lizardman = read_file(PATH+"lizard-man");

  add_item("human", human);
  add_item("half-elf", halfelf);
  add_item("elf", elf);
  add_item("drow", drow);
  add_item("dwarf", dwarf);
  add_item("gnome", gnome);
  add_item("halfling", halfling);
  add_item("half-orc", halforc);
  add_item("orc", orc);
  add_item("goblin", goblin);
  add_item("lizard-man", lizardman);
}

int no_kill(string str) { return 1; }
void init()
{
  ::init();
  add_action("do_become", "be*come");
   add_property("nocast",1);
   add_property("noguild",1);
  /* Mask the action rearrange */
  add_action("do_rearrange", "rearrange");
   add_action("no_kill","at*tack");
   add_action("no_kill","kill");
}

int do_rearrange()
  {

   tell_object(this_player(),"Not allowed here, select a race and leave first.\n");
   return 1;
} /* do rearrange */

int do_become(string str)
{
 object me;
 string race;
 string startplace;
 int i;
 
 me = this_player();
 str = lower_case(str);
 if (str != "") i = str[0];
 
 /* The players should be able to pick a race only once.
  * Fixed by Baldrick, dec '94
  */

 if ((string)me->query_race_ob() != "/std/races/unknown")
   {
   startplace = "/room/start/" + me->query_race();
   me->move(startplace);
   notify_fail("Already chosen one before, moving you to your home.\n");
   return 0;
   } /* in (me */

 if (i == 'h')
 {
  i = str[1];
  if (i == 'u') race = "human";
  if (i == 'a')
  {
   i = str[5];
   if (i == 'e') race = "half-elf";
   if (i == 'o') race = "half-orc";
   if (i == 'i') race = "halfling";
  }
 }
 else if (i == 'e') race = "elf";
 else if (i == 'o') race = "orc";
 else if (i == 'l') race = "lizard-man";
 else if (i == 'd')
 {
   i = str[1];
   if (i == 'w') race = "dwarf";
   if (i == 'r') race = "drow";
   //if (i == 'u') race = "duck";
 }
 else if (i == 'g')
 {
   i = str[1];
   if (i == 'o') race = "goblin";
   if (i == 'n') race = "gnome";
 }
 if(race)
 {
   say(this_player()->query_cap_name()+" enters the "+race+" statue and "+
    "disappears.\nA new "+race+" statue suddenly appears.\n", this_player());
   me->set_race_ob("/std/races/"+race);
   write("You feel a strange sensation, and suddenly you wake up in your "+
         "childhood home.\nYou seem to remember you stuffed away some "+
         "equipment somewhere in case you should choose to leave, but "+
         "where ?\n");
   startplace = "/room/start/" + race;
   // me->move("/room/start/"+race);
   me->move(startplace);
   startplace->add_equipment();
   if(race == "half-elf")
   {
     me->add_language("human");
     me->add_language("elf");
   }
   else if(race == "half-orc")
   {
     me->add_language("orc");
     me->add_language("human");
   }
   else
     me->add_language(race);
   return 1;
 }
 notify_fail("No such race, try again.\n");
 return 0;
}
