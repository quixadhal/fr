// File taken from the VikingMUD lib.
//
// Original comment:
//
// Written by Kniggit 930525
 
#include <standard.h>
#include <cmd.h>

#ifndef __COMPILER__
#define __COMPILER__ "gcc"
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
   string mach, vers, name, up, cc, tmp;
   int obs, memory, width;
   
   r = rusage();
   obs = sizeof( objects() );
   //write("OBS\n");
   mach = __ARCH__;
#ifndef MSDOS
   cc = __COMPILER__;
#else
   cc = "GCC probably, but who knows.";
#endif
   //write("Version\n");
   name = capitalize(MUD_NAME);
   vers = __VERSION__;
   //write("CPU\n");
   cpu = ((r["utime"] + r["stime"]) / uptime() / 10.0);
   width = 15;
   memory = memory_info();
   //write("pretty_time");
   up = pretty_time(uptime(), 4);
   
   tmp = PAD("Mud name", name, width) +
         PAD("Architecture", mach, width) +
         PAD("Driver", vers, width) +
         PAD("Compiler", cc, width) +
         PAD("Driver uptime", up, width) +
         PAD("Cpu usage", sprintf("%5.2f%%",cpu), width) +
         PAD("No of users", sizeof(users()), width) +
         PAD("Memory usage", memory, width) +
         PAD("Objects", obs + " loaded.", width);
   write(sprintf("\n%-*#s\n", 80, tmp));
   return 1;
}

short_help() { return "Show some information about Fr's system usage.\n"; }

