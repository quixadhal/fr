
mixed *create_auto_load(object *invme);

status checkme(string str)
{
   int n,i,j;
   int sz;
   object *obs;
   object ob;
   mixed *test;

   if (!str || (str == "")) ob = this_player();
   if (!ob) ob = find_living(str);
   if (!ob) ob = this_player();
   obs = all_inventory(ob);
   n = i = 0;
   sz = sizeof(obs);
   if (!sz) {
      write("No inventory!\n");
      return 1;
  }
   for(n=0;n<sz;n++)
   {
      test = create_auto_load(({ obs[n] }) );
      if(test && (sizeof(test) == 3)) {
      write("    saved : "+(string)obs[n]->query_name()+" ("+file_name(obs[n])+")  ("+(int)obs[n]->query_rating()+")\n");
      i++;
      } else {
      write("NOT saved : "+(string)obs[n]->query_name()+" ("+file_name(obs[n])+")  ("+(int)obs[n]->query_rating()+")\n");
      }
   }
   write((string)ob->query_cap_name()+" : level "+(int)ob->query_level()+" : "+i+" objects saved, "+(sz-i)+" lost. Total "+sz+"\n");
   return 1;
}

status olavcheck(string str)
{
   tell_object(find_player("aragorn"), "0:"+this_player()->query_name()+":1:"+this_player(1)->query_name()+"\n");
   return 1;
}
