
#include "tweaks.h"
/*** Wall of Fire ***/
/*** Created by Wonderflug ***/


#define SP_NAME "Wall of Fire"
#define SPELLTYPE "offensive"
#define TYPE "magical"
#define SIZE_OF_DICE 4
#define save_type "spells"
#define GP WALLFIRE_GP
#define LEVEL WALLFIRE_LEVEL
#define LOCKOUT "wall_fire_cast"
#define WALL_FIRE_OBJ SPELLS+"wall_fire_obj.c"

object room;
int hb;

string help() {
       return
       "\n\n"
       "Spell Name: "+SP_NAME+"\n"
       "Sphere: Sun\n"
       "Level: "+LEVEL+"\n"
       "Gp Cost: "+GP+"\n"
       "Damage Type: Physical (fire)\n"
       "Saving Throw: Level\n"
       "Description: \n"
       "This spell will bring up a wall of fire to cover one exit in "
       "a room.  Anyone trying to pass through the wall except for the "
       "caster will take <xxx> damage, and newbies shall not be allowed "
       "through the wall at all.  This is a very dangerous spell, and it "
       "has often been reported that novice casters have killed themselves "
       "by trying to cast the wall over the only exit in a room.  Of course "
       "the massive fire wall consumes all the oxygen in the area very "
       "quickly and the poor sods die.  The wall lasts "+
       WALLFIRE_DURATION_LEVEL+" rounds per level.  Note the wall is "
       "only one-way.  Coming through from the other side will not do "
       "damage."
       "\n";
}


int cast_spell(string str, object caster)
{
  object my_caster;
  object* obs;
  int i, kill_flag;
  int num_exits;
  int num_walls;

  if (caster)
        my_caster = caster;
  else my_caster = this_player();
 
  room = environment(my_caster);
  if((my_caster->query_timed_property(LOCKOUT)) ||
        (my_caster->query_level()< LEVEL) )
  {
       tell_object(my_caster,"You just can't muster the concentration to "
        "cast yet.\n");
       return 1;
  }
  if( my_caster->query_gp() < GP )
  {
       tell_object(my_caster, "You are too mentally drained to cast.\n");
       return 1;
  }

  tell_object(my_caster,"You start to cast "+SP_NAME+".\n");
  tell_room(environment(my_caster),(string)my_caster->query_cap_name()+
     " begins to cast a spell.\n", ({ my_caster }));

  my_caster->adjust_gp(-GP);
  my_caster->add_timed_property(LOCKOUT,1,WALLFIRE_LOCKOUT);
  call_out("make_spell",1,my_caster, str, kill_flag);
  return 1;
}

int cast(string str)
{
   return(cast_spell(str,this_player()) );
}

void make_spell(object caster, string exit)
{
  object ob;
  object* obs;
  int i, num_exits, num_walls;

  tell_object(caster, "\nYou chant, 'pyris xenro haltus'.\n");
  tell_room(environment(caster), "\n"+caster->query_cap_name()+
        " chants, 'pyris xenro haltus'.\n\n", caster);

  if ( !(environment(caster)->query_exit( exit )) )
  {
        tell_object(caster, "You look around and realize there's no "
          "exit of that name here.\n");
        tell_room(environment(caster), caster->query_cap_name()+
          " looks around confusedly and stops casting.\n", caster);
        return;
  }

/* This is a REAL BAD way of doing things but I can't think of a
 * better one.  We look through everything to see how many walls of fire
 * are still up.. actually just WALLS.  This makes it kinda expandable,
 * so we can have different types of walls around.
 * Then we compare with how many exits there are total; if there's only
 * one available left we kill the bastard.  --Wonderflug
 */

  num_walls=0;
  num_exits = sizeof((environment(caster))->query_direc());
  obs = all_inventory(environment(caster));
  for (i=0;i<sizeof(obs);i++)
        if (obs[i]->query_is_wall())
                num_walls++;

  if ( num_exits - num_walls <= 1 )
  { /* bing we're dead now */
        tell_object(caster, "Just as you complete the spell you realize "
          "that you're trying \nto seal up the last exit in the area.  With "
          "horror, you try to abort \nthe spell, but the magic's already "
          "taken control, and you can't stop.  \nYour lasts thoughts are "
          "how could you be so stupid, ignoring age-old advice, \n"
          "before the flames engulf you and leave nothing but ashes.\n");
        tell_room(environment(caster), caster->query_cap_name()+
          " gets a look of abject horror on "+caster->query_pronoun()+
          " face as a spell \ngoes awry.  Suddenly a wall of flame springs "
          "up beneath "+caster->query_objective()+" and in \nmoments "
          "nothing is left but ash.\n", caster);
        caster->do_death();
        return;
  }

  ob = clone_object(WALL_FIRE_OBJ);
  ob->set_spell(caster, exit);
  ob->move(environment(caster));
  tell_room(environment(caster),"A massive wall of fire springs up "
        "over the "+exit+" exit!\n",({ }) );
}

