inherit "std/guilds/mage";

void setup()
{
set_name("shalafixi walkers");
set_short("Shalafixi Walkers");

set_long(
"The Shalafixi Walkers are probably the most mysterious of wizards"
".  They are a silent group that are known to be elementalists.  It"
" seems as if they have formed a bond with the elemental planes, "
"and have actually found a way to summon creatures, communicate, "
"and travel to and from the elemental planes.  They are a very"
" elite group that is made mostly of elves.  They are very picky"
" on racial requirements, but are the only wizard type group that"
" permits halflings to join.  They claim halflings have the "
"'gift and innocence' to be powerful Shalafixi Walkers.\n");
reset_get();
}

int query_xp_cost() { return 3000; }
int query_legal_race(string race) {
switch(race) {
  case "dwarf":
  case "gnome":
  case "goblin":
  case "half-elf":
  case "orc":
  case "drow":
  case "half-orc":
  case "lizard-man":
  case "troll": return 0;
  default       :return 1;
 }
}
