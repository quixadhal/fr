/*** temp shadow for Spirit Armour spell ***/

#include "tweaks.h"

object my_player;

void setshadow(object ob) 
{
   shadow(ob,1);
   my_player = ob;
}

void destruct_shadow()
{
  destruct(this_object());
}


status wear_ob(object ob)
{
  tell_object(my_player,
	"You have no need of material protection with your spirit "+
	"to protect you.\n");
  return 0;
}
 
int do_wear(string str)
{
  tell_object(my_player,
	"You have no need of material protections with your spirit "+
	"to protect you.\n");
  return 1;
}

int query_total_ac()
{
  int i;
  if ( !(my_player->query_timed_property_exists(SPIRIT_ARMOUR_PROPERTY)) )
  {
  /* should never happen unless it gets dested by someone/thing */
   call_out("destruct_shadow",0,0);
	return (my_player->query_total_ac());
  }

  if ( my_player->query_timed_property(SPIRIT_ARMOUR_PROPERTY) )
  	return ( 10 - (int)my_player->query_body_ac() - (SPIRIT_ARMOUR_BASE 
      +( (5+(int)my_player->query_level())/SPIRIT_ARMOUR_LEVEL_MOD)) );
  else 
  {
	if ((string)my_player->query_guild_name() != "necromancer")
	{
	  my_player->adjust_hp(-random(4)-random(4)-2);
	  tell_object(my_player,
	    "You feel some of your life essence burn away!\n");
	  say(my_player->query_cap_name()+" is wracked with pain for "+
	    "a moment as the grey mist that surrounded "+
	    my_player->query_objective()+" dissipates.\n",my_player);
	}
	tell_object(my_player,"Your spirit armour fades away.\n");
   call_out("destruct_shadow",0,0);
	return (my_player->query_total_ac());
  }
}

int query_spirit_armour_spell() { return 1; }

/*** query_armour_spell <- identifies which spell, if its say a shield 
 spell, it would be query_shield_spell(), etc. ***/

