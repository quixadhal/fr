mixed find_unique_match(string find,mixed in)
{
mixed *olist;
   int i,j;
   olist = find_match(find,in);
   for(i = 0; i < sizeof(olist); i++)
   {
      for(j = sizeof(olist)-1; j > i; j--)
      {
         if(olist[j] == olist[i]) olist = delete(olist,j,1);
      }
   }
   return olist;
}
mixed find_one_match(string find,mixed in)
{
mixed *olist;
   int i,j;
   olist = find_match(find,in);
   if(sizeof(olist)> 1)
   {
      olist = delete(olist,1,sizeof(olist)-1);
   }
   return olist;
}
