/*
 * Ipcheck.c
 * Inspired to hard-code stopping salford logins.
 * 4 March 1994 Chrisy
 */

#include "config.h"
#ifdef SunOS_5
#include <stdlib.h>
#endif
#if defined(__386BSD__) || defined(SunOS_5)
#include <unistd.h>
#endif
#ifndef LATTICE
#include <varargs.h>
#endif
#include <sys/types.h>
#ifndef LATTICE
#include <sys/time.h>
#else
#include <time.h>
#endif
#ifndef LATTICE
#include <sys/ioctl.h>
#endif
#ifdef __386BSD__
#include <sys/param.h>
#endif
#define TELOPTS
#ifndef LATTICE
#include <netdb.h>
#include <fcntl.h>
#endif
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#ifndef LATTICE
#include <memory.h>
#else
#include "amiga.h"
#define read(s,t,l) read_socket(s,t,l)
#define write(s,t,l) write_socket(s,t,l)
#define close(s) close_socket(s)
#endif

#include "comm.h"

int CheckValidIP(struct sockaddr_in *addr)
{
	/* okay. #1 - jsut hard check for IP's beginning 146.87 :)
	 * anarchist used 146.87.119.60 last time ;)
	 * perhaps one day i'll scan an array, and perhaps domain
	 * lookups? Hmm. have to suss that out ;)
	 * Chrisy
	 */

	unsigned long a, b;

	a = ntohl(addr->sin_addr.s_addr);

	b = (146<<24) + (87<<16);

	a &= 0xffff0000;

	if(a == b)
		return 1;

	return 0;
}
