inherit "std/guilds/cleric";

void setup(){
 set_name("Ducky");
 set_short("Priest of Ducky");
 set_long("This is a priest of Ducky, the god of evil in it's purest form.  "+
	"This priest doesn't look evil however, for evil is evil regardless "+
	"of outer cosmetics, law or order.\n\n");
 set_needed_align("evil");

 add_guild_command("detect unseen", 1);
 add_guild_command("turn",1);
 add_guild_command("sneak",1);
 add_guild_command("hide",1);
 add_guild_command("steal",5);
 add_guild_command("palm",5);
 add_guild_command("slip", 5);
 reset_get();
}

int query_legal_weapon(string type) {
   switch(type) {
      case "club":
      case "polearm":
         return 0;
      default:
         return 1;
   }
}

int query_legal_armour(string type) {
   switch(type) {
      case "leather":
      case "studded leather":
      case "studded":
      case "elfin chain":
      case "wooden shield":
         return 0;
      default:
         return 1;
   }
}

int query_legal_race(string race){
  switch (race) {
    case "halfling":
    case "fish":
       return 0;
    default:
       return 1;
    }
}

mixed query_legal_spheres(){
  return ({
  ({ "healing", "neutral" }),
  ({ "all", "neutral" }),
  ({ "combat", "major" }),
  ({ "necromantic", "major" }),
  ({ "protection", "neutral" }),
  ({ "elemental", "major" }),
  ({ "clericdivination", "minor" }),
  ({ "guardian", "neutral" }),
  ({ "weather", "minor" }),
  });
}

int query_advance_cost() { return 2000; }
int query_xp_cost() { return 2500; }

string query_title(object player){
 int lvl,sex;

 lvl = query_level(player);
 sex = (int)player->query_gender();
 if(sex>1) sex=1;

 if(lvl > 29) return (sex) ? "the Chosen Lord": "the Chosen Lady";
 if(lvl > 19) return (sex) ? "the Favoured Lord": "the Favoured Lady";
 if(lvl > 9) return (sex) ? "the Blighted Priest": "the Blighted Priestess";
 if(lvl > 4)  return "initiate";
 return (sex) ? "the servant wimp": "the servant wimpess";
}
