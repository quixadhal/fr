inherit "/global/creator";

#define  O_TYPE "P"

nomask
string query_gtitle()
{
  string patronage;
  patronage = "/secure/patrons"->query_patronage(name);
  if(query_female())
    return "the Patroness of "+patronage;
   return "the Patron of "+patronage;
}
	    
nomask
string query_object_type() 
  {
  return O_TYPE;
  }  /* query_object_type() */

