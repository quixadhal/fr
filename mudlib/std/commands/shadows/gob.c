inherit "/std/object";

void setup() {
   //set_name("fightcurse");
   set_weight(0);
   set_value(0);
   reset_drop();
}


int query_auto_load() { return 1; }
init() {
   ::init();
   add_action("bingle_tell","t*ell");
   add_action("bingle_shout","sh*out");
   add_action("bingle_shout","shout!");
   add_action("bingle_say","sa*y");
   add_action("bingle_say","'*");
   add_action("bingle_loud_say","lsay");
   add_action("bingle_loud_say","\"*");
   add_action("bingle_whisper","whi*sper");
}

wibble_speech(string str)
{
 string *cow;
 int i;
 
   if(!str || str == "") return;
 cow=explode(str," ");
 for(i=0;i<sizeof(cow);i++)
  cow[i]=capitalize(cow[i]);
 str=implode(cow," ");
   str=replace(str,({"Your","Thine","YOUR","THINE","You're","Thou Art",
      "YOur","Thine","YOUr","Thine","youR","Thine","yoUR","Thine",
   "Nothing","Naught","Anything","Aught",
      "yOUR","Thine","You","Thou","YOU","THOU","YOu","Thou","YoU","Thou",
      "Doing","About","DOING","ABOUT","DOing","About","DoING","About",
      "Do ","Doth ","DO ","Doth ","Do?","Doth?","Do!","Doth!",
      "Not","Nary","NOT","NARY","NOt","Nary","Hello","Good Morrow",
      "HELLO","Good Morrow","Hi ","Greetings ","HI ","GREETINGS ",
      "Thief","Cowardly Ruffian","THIEF","Cowardly Ruffian",
      "Thieves","Cowardly Ruffians","THIEVES","COWARDLY RUFFIAN",
      "Paladin","Lord","PALADIN","LORD",
      "Assassin","Cowardly Murderer","ASSASSIN","COWARDLY MURDERER",
      "Wizard","Spell-Weaver","WIZARD","SPELL-WEAVER",
      "Stop","Desist","STOP","DESIST","Bury","Depose","BURY","DEPOSE",
    "Are","Art","ARE","ART","ARe","Art","ArE","Art",
    "Where","Wither","WHERE","WITHER","WHere","Wither",
    "Kill","Slay","KILL","SLAY","Killed","Expired","KILLED","EXPIRED",
    "ld ","lde ","st ","ste ","er ","ere ","p ","pe ","l ","le ",
    "h ","he ","H ","HE ","D ","DE ","L ","LE ","P ","PE ","R ","RE ",
    "n ","ne ","N ","NE ","r ","re ","d ","de ","l ","le ","G ","GE ",
    "g ","ge ","s ","se ","S ","SE ","b ","be ","B ","BE ","y ","ye ",
    "Stop","Desist","STOP","DESIST","Not","Nary","No ","Nay ",
    "Bury","Depose","BURY","DEPOSE"}));
  return str;
}
 
 
void bingle_loud_say(string arg)
{
 int x;
 
   arg=wibble_speech(arg);
 x=this_player()->do_loud_say(arg);
 return x;
}
 
void bingle_say(string arg)
{
 int x;
   string wool;
 
   if(!arg || arg=="") return;
   if( (string)this_player()->query_word_type(arg)=="ask")
   wool=({"Praytell, ","I'faith, ","Prithee, "})[random(3)];
    else
  wool=({"Verily, ","Truth, ","By my Troth, ","",""})[random(5)];
   arg=wibble_speech(arg);
  x=this_player()->do_say(wool+arg);
 return x;
}
 
void bingle_tell(string arg)
{
 int x;
    string *cow, woobie;
 
 
   if(!arg || arg == "") return;
   cow=explode(arg," ");
   woobie=cow[0];
    if( (string)this_player()->query_word_type(arg)=="ask")
   cow[0]=({"Praytell, ","I'faith, ","Prithee, "})[random(3)];
    else
  cow[0]=({"Verily, ","Truth, ","By my Troth, ","",""})[random(5)];
   arg=implode(cow," ");
 
   arg=wibble_speech(arg);
   arg=woobie+" "+arg;
  x=this_player()->do_tell(arg);
 return x;
}
 
void bingle_shout(string arg)
{
 int x;
   string wool;
 
   if(!arg || arg == "") return;
   if( (string)this_player()->query_word_type(arg)=="ask")
   wool=({"Praytell, ","I'faith, ","Prithee, "})[random(3)];
    else
  wool=({"Verily, ","Truth, ","By my Troth, ","",""})[random(5)];
   arg=wibble_speech(arg);
  x=this_player()->do_shout(wool+arg);
 return x;
}
 
void bingle_whisper(string arg)
{
 int x;
    string *cow, woobie;
 
   if(!arg || arg == "") return;
   cow=explode(arg," ");
   woobie=cow[0];
    if( (string)this_player()->query_word_type(arg)=="ask")
   cow[0]=({"Praytell, ","I'faith, ","Prithee, "})[random(3)];
    else
  cow[0]=({"Verily, ","Truth, ","By my Troth, ","",""})[random(5)];
   arg=implode(cow," ");
 
   arg=wibble_speech(arg);
   arg=woobie+" "+arg;
  x=this_player()->do_whisper(arg);
 return x;
}
 
