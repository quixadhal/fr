/*** head object ***/ 
/*** By wonderflug, my best work yet ***/

inherit "/std/item";

setup()
{
  set_name("head");
  set_short("Decapitated head of something"); 
  set_long("This is a gruesome head, apparently hacked off someone's "+
    "body rather messily.\n"); 
  set_main_plural("Decapitated heads");
  set_weight(50); 
}

init()
{
  ::init();
  if ( this_object()->query_property("owner") )
    set_short("Decapitated head of "+
      this_object()->query_property("owner"));
} 

