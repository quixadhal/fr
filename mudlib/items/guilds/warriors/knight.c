inherit "/std/guild";

string help()
{
 return "Knight help to go here.\n";
 reset_get();
}

int query_skill_cost(string skill)
{
 return 0;
}

void setup()
{
 set_name("Knight");
 set_short("Knight");
 set_long("Knight long desc to go here.\n");
 reset_get();
}

int query_advance_cost() { return 750; }

int query_legal_race(string race)
{
 switch(race)
 {
  case "half-orc":
  case "lizard-man":
  case "troll":
  case "orc":
  case "drow":
  return 0;
  default:
  return 1;
  }
}

int query_legal_weapon(string type)
{
 switch(type)
 {
  case "broad sword":
  case "long sword":
  case "mace":
  case "morning star":
  return 1;
  default:
  return 0;
 }
}

int query_legal_armour(string type)
{
 switch(type)
 {
  case "bronze plate":
  case "field plate":
  case "full plate":
  case "plate mail":
  case "plate":
  case "shield":
  case "medium shield":
  case "large shield":
  case "great helm":
  case "full helm":
  case "visored helm":
  case "gauntlet":
  return 1;
  default:
  return 0;
 }
}
