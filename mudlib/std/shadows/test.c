object my_player;

void dest_shadow();

int test_add() { return 0; }
void setup_shadow(object ob, int length) 
{
  if(!length)
     length = 100;
  shadow(ob,1);
  my_player = ob;
  call_out("dest_shadow", length);
}


string short() 
{
  if (!my_player)
    return "Sleep shadow";
  return my_player->short()+" [sleeping]";
}

void dest_shadow() 
{
  remove_action("do_suppress", "*");
  tell_object(my_player, "You wake from a recuperative sleep.\n");
  tell_room(environment(my_player), my_player->query_cap_name()+" wakes from "+
   my_player->query_possessive()+" sleep.\n", my_player);
  destruct(this_object());
}
 
string query_deity()
{
 return "Timion";
}
