/* Display various information about the mud's status.

   File taken from the VikingMUD lib.  Written by Kniggit 930525

   Hamlet tweaked me some, May 1997.
*/
 
/* Add named_livings() when we go to v22 */

#include <standard.h>
#include <cmd.h>

#ifndef __COMPILER__
#define __COMPILER__ "probably gcc"
#endif

inherit CMD_BASE;

void setup()
{
  position = 0;
  dodest = 1;
}

#define PAD(x,y,z)      sprintf("%-*s: %s\n",z,x,"" + y)

static int cmd(string str, object me)
{
   mapping r;
   float cpu;
   string mach, vers, name, up, cc, loadav, tmp;
   int obs, memory, callouts, width;
   
   r = rusage();
   obs = sizeof( objects() );
   mach = __ARCH__;
#ifndef MSDOS
   cc = __COMPILER__;
#else
   cc = "GCC probably, but who knows.";
#endif
   name = capitalize(mud_name()) + "   (" + query_host_name() + " " + 
          __PORT__ + ")";
   vers = __VERSION__;
   cpu = ((r["utime"] + r["stime"]) / uptime() / 10.0);
   width = 15;
   memory = memory_info();
   up = pretty_time(uptime(), 4);
   loadav = query_load_average();
   callouts = sizeof(call_out_info());
   
   tmp = PAD("Mud name", name, width) +
         PAD("Driver", vers, width) +
         PAD("Architecture", mach, width) +
         PAD("Compiler", cc, width) +
         PAD("Driver uptime", up, width) +
          PAD("Avg Cpu usage", sprintf("%4.2f%%", cpu), width) +
         PAD("Load Average", loadav, width) +
         PAD("No of users", sizeof(users()), width) +
         PAD("Objects", obs + " loaded.", width) +
         PAD("Call Outs", callouts + " pending.", width) +
         PAD("Memory usage", memory, width);
   tell_object(me,sprintf("\n%-*#s\n", 80, tmp));
   return 1;
}

short_help() { 
  return "Show some information about the mud's system usage.\n"; 
}
