inherit "std/guilds/mage";

void setup()
{
set_name("battle wizard");
set_short("Battle Wizard");

set_long(
"The Battle Wizard's are a type of wizard that have been trained "+
"to do one thing...to destroy their enemy.  They are trained in all"+
" forms of magical combat.  Their weakness lies in the more 'formal'"+
" arts of magic that other mages prefer.  Though they are stronger in"+
" offensive magic than their fellow mage, they lack in the massive "+
"defensive and informational spells.  But, do not be fooled by the "+
"Battle Mage that runs outta of magical power, for they are trained"+
" to be as deadly with a weapon as a Priest of the Warrior God.\n");
reset_get();

add_command("judge",1);
}

int query_legal_weapon(string type)
{
  switch(type)
  {
    case "dagger":
    case "dirk":
    case "dart":
    case "quarterstaff":
    case "staff":
    case "sling":
    case "knife":
    case "sword":
    case "katana":
    case "spear":
    case "rapier":
         return 1;
    default: return 0;
  }
}  
