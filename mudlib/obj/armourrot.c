inherit "/obj/armour";

string pretty_short() {
    object me;
    string ret;
    int x;
    string *where;
    me = ETO;
    if(!me) return ::pretty_short();
   if(!environment(me)) return ::pretty_short();

    where = explode(file_name(environment(me)), "/");

    if(sizeof(where) > 2) {
	if(!(where[1]=="bf") && !(where[1]=="newbie") && !(where[1]=="aprior")
	  && !(where[2]=="werre") && !(where[2]=="greymistics")) {
	    x = this_object()->query_property("ROTCOUNTER");
	    this_object()->remove_property("ROTCOUNTER");
	    x--;
	    this_object()->add_property("ROTCOUNTER",x);
	}
    }
    ret = ::pretty_short();
    return ret;
}

int query_ac() {
    int ret;
    if(this_object()->query_property("ROTCOUNTER") <= 0 &&
      !this_object()->query_property("DESTED")) {
	write("\n     Your "+this_object()->query_short()+" has "
	  "been drained of all magic and vanishes into "
	  "nothingness.\n\n");
	this_object()->add_property("DESTED",1);
	call_out("my_dest", 1);
	return(0);
    }
    ret = ::query_ac();
    return ret;
}
void my_dest() {
    if(this_object()->query_property("DESTED"))
	this_object()->dest_me();
}
