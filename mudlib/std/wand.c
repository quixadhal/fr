inherit "/std/item";

string  enchant_string()
{
   int charges;
   charges = query_enchant();
   switch(charges)
   {
      case 0:
      return "Nope, nothing left in this one, it's an EX wand.";
      case 1:
      case 2:
      return "Still a bit of life left in it.";
      case 3:
      case 4:
      case 5:
      return "A few shots left in the 'ol stick yet.";
      case 6..9:
      return "Plenty of life left in this one.";
      default:
      return "Hey this is a healthy one, good for many more.";
   }
}
int query_enchant()
{
   return query_property("charges");
}
int adjust_enchant(int i)
{
   add_property("charges",query_property("charges")+i);
   return query_property("charges");
}
int set_enchant(int i)
{
   add_property("charges",i);
   return query_property("charges");
}
