
inherit "/std/object";


void setup()
{
  set_name("holy symbol");
  add_alias("cross");
  add_alias("silver cross");
  set_short("Silver Cross of Lathander");
  set_long("\nSilver Cross of Lathander\n\n"+
	"     This is a heavy silver cross, the word 'Lathander' inscribed "+
	"across the horizontal arm.  It's very warm to the touch, seemingly "+
	"throbbing with the power of the Morning Lord.\n\n");
  set_value(0);
  set_weight(100);
  add_property("faith", "lathander");
}

