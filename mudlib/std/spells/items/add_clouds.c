/* Taniwha 1995. code for giving players the cloud spells */
/* the givee's are in the Hoerk quest
*/
int add_spell(object tp,int x)
{
   switch(tp->query_guild_name())
   {
      case "tempus":
      case "Lolth":
      case "cle-war":
      case "tymora":
      case "lathander":
         if(x) tp->add_spell("blade barrier","bbarrier",1);
         else tp->add_spell("silence","silence",1);
      break;
      case "wizard":
      case "drow_wizard":
      case "necromancer":
      case "conjurer":
      case "abjurer":
      case "enchanter":
      case "illusionist":
      case "invoker":
      case "wizthief":
      case "wiz-war":
      case "transmuter":
         if(x) tp->add_spell("confusion","ccloud",1);
         else tp->add_spell("stinking cloud","scloud",1);
      break;
      }
}
