inherit "/obj/armour";


set_in_use(int i)
{

   object ob;
   object TP;
 
   TP= this_player();

   ob=environment(TP);

	if (i==1) {
	   if (TP->query_tmp_dex() <=0) {
	      write("You hesitantly slip the ring unto your "+
		    "finger. As you do so, your feet seem a "+
		    "seem a little lighter, your limbs a little "+
		    "looser, and you hear a faint music carrying "+
		    "on the wind. You feel like...dancing.\n\n");
	      tell_room(ob, TP->query_cap_name()+
			"places the Ring of the Dark Dancer upon "+
			TP->query_possesive()+"finger, "+
			"a smile "+
			"passes over their face and they seem a "+
			"a little more relaxed. \n\n "+
			"",({TP}));
	      TP->adjust_tmp_dex(2);
	     }
	   else {
	      write("You slip the ring unto your finger.\n\n");
	      tell_room(ob, TP->query_cap_name() +
			"wears a Ring of the Dark Dancer. "+
			"\n\n",({TP}));
	    }
	  }
	else if (i==0)  {
	   write("You remove the ring from your finger, and "+
	         "life seems a lot more bland as you are tired "+
		 "and more lethargic for some reason.\n\n");
	   tell_room(ob, TP->query_cap_name() +
		     "suddenly appears a lot more lethargic. "+
		     "\n\n",({TP}));
	   TP->adjust_tmp_dex(-2);
	}
	::set_in_use(i);
}

void setup()
{
set_base_armour("ring");
set_name("mring");
set_short("ring of the Dark Dancer");
set_long("A silver ring with a black onynx carved into the shape of "+
	 "a scimitar holding figure which appears to be....dancing.\n"+
	 "A reward granted to Masquerade by Taniwha for completion "+
	 "of Juju quest. Coded by Caretaker. Not replacable.\n\n");
reset_drop();
 set_value(0);
}
