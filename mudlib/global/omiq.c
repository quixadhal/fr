/* Hamlet -- October 1995.
   This is called by various things that behave differently during 
   omiqs and/or flag games.  Don't change the functions just the #defines
   below.  It is not necessary to set OMIQ to true to set FLAG to true.
*/

#define OMIQ 0
#define FLAG 0

int omiq_in_progress() {  return (OMIQ || FLAG);  }

int flag_in_progress() {  return FLAG;  }
