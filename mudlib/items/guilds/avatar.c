inherit "/std/guilds/mage";

void setup()
{
  set_name("Avatar");
  set_short("Avatar");
  set_long("This is the Avatar's Guild.  This guild was made to make "+
   "learning spells for Avatar's easy.\n");
  reset_get();

}

void init()
{
  add_action("manifest", this_object());
::init();
}
  
int do_manifest()
{
  object ob;
  if(!shadow(this_player(),0)) 
   {
    ob=clone_object("/w/eerevann/ava_shad");
    ob->set_up_shadow(this_player());
   }
}



string query_spell_directory() {return "/std/spells/combined/";}

int query_dice() { return 18; }

int query_thac0_step() { return 1; }

void set_gp(object ob)
{ 
 ob->set_max_gp( (int)ob->query_level() * 30 );
}

void set_hp(object ob)
{ 
ob->set_max_hp(query_dice()*level); 
}

int query_legal_armour(string type)
{
	  return 1;

}

int query_legal_weapon(string type)
{
	   return 1;

}

int query_legal_race(string race)
{
	  return 1;
}

mixed query_legal_spheres()
{
   return ({"abjuration","alteration","illusion","lesserdivination",
       "greaterdivination", "necromancy",
       "invocation","conjuration","enchantment","clericdivination",
       "all", "animal", "astral", "charm", "combat", "creation",
       "elemental", "guardian", "healing", "necromantic", "plant",
       "protection", "summoning", "sun", "weather"});
}
