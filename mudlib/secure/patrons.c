/* patron.c
 * A patron is just above a builer, on FR it means he has some of his work 
 * in the game.
 */

/* you *have* to remove "foo" or it will be  a security risc.
 */

string query_patronage(string str);

string query_patronage(string str)
{
 switch(str)
 {
   case "foo":
    return "a domain";
    break;
  default:
    return 0;
 }
}  
