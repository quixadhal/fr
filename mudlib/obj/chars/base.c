inherit "/obj/monster";
static object myfriend;
void set_friend(object friend) 
{
   myfriend = friend;
}

void event_fight_in_progress(object ob1,object ob2)
{
   if(ob1 && !interactive(ob1) && ob1 != myfriend) ob1->attack_by(this_object());
   if(ob2 && !interactive(ob2) && ob2 != myfriend) ob2->attack_by(this_object());
}
void attack_by(object ob)
{
   if(ob == myfriend)
   {
      tell_room(environment(this_object()),"The "+this_object()->query_cap_name()+" sighs and returns to the grave.\n");
      call_out("dest_me",0);
   }
   ::attack_by(ob);
}
void attack_ob(object ob)
{
   if(ob == myfriend) return;
   ::attack_ob(ob);
}


