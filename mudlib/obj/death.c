inherit "std/object";

object person;

void person_died(string name)
{
  object ob;

  person=find_living(name);
  person->add_property("dead", 1);
  person->add_property("noregen", 1);
  call_out("talk", 3);
}

void talk()
{
 if(person)
 {
  tell_object(person,
"A cold voice fills your mind and starts to speak:\n"+
"The voice exclaims: Why are you so careless mortal ?\n" +
"The voice informs you: Bloody corpses like that are not very "+
"civilized you know.\n");
  call_out("talk2", 2);
 }
}

void talk1()
{
 if(person)
 {
  tell_object(person,
"The voice exclaims: Sorry, forgot to introduce myself, I'm Cyric.\n" +
"Cyric tells you: You really should be more afraid, I'm the God of DEATH.\n");
  if(this_player()->query_creator())
    tell_object(person,"Cyric asks you: So you thought yourself to be immune "+
     "DEATH, oh puny Creator ?\nCyric informs you: Noone escapes ME!\n");
  call_out("talk2", 5);
 }
}

void talk2()
{
 if(person)
 {
  tell_object(person,
"Cyric says: I suppose you'd like to have a chance of getting raised from "+
"the dead before you're mine forever.\n");
  call_out("talk3", 5);
 }
}

void talk3()
{
 if(person)
 {
  tell_object(person,
"Cyric informs you: I so love to watch puny mortals strive to get someone to "+
"raise them before I take the time to deal with them myself.\n");
  call_out("talk4", 6);
 }
}

void talk4()
{
 if(person)
 {
  tell_object(person,
"Cyric says: The worst of luck at playing GHOST mortal!\n");
  call_out("talk5", 1);
 }
}

void talk5()
{
 if(person)
 {
  tell_object(person, "Cyric cackles with glee.\n");
  call_out("talk6", 10);
 }
}

void talk6()
{
 if(person)
 {
  tell_object(person,
   "Cyric says: You'll see me again soon enough mortal. Be seing YOU!\n");
  person->remove_property("noregen");
  call_out("talk7", 4);
 }
}

void talk7()
{
 if(!person)
 {
  tell_object(person,"Cyric says: Get along now before I change my mind....\n"+
   "Cyric waves his scythe dismissively.\n");
  person->move_to_start();
  move(environment(person));
  call_out("talk8", 2);
 }
}

void talk8()
{
 int pos;

 if(person)
 {
  tell_object(person,
   "Cyric flies away, and the stench of Death lifts.\n");
  remove_call_out("timeout");
 }
}
