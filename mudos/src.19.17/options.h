/*
 * options.h: defines for the compile-time configuration of MudOS
 */

/* Modified for Aurora, Chrisy
 */

#define AURORA "Chrisy"

/* NOTES:
 * Many of the configurable options are now set via the configuration file
 *  that is specified as the first argument to the driver.
 * See port.h for those #defines related to portability (compatibility) if
 *  you have problems compiling on your system.
 * Removing an efun from func_spec.c usually removes most, if not all,
 *  of the code associated with it.
 */

/* You must choose exactly one of these mallocs.
 *
 * SYSMALLOC: builtin system malloc.  No wrappers, no statistics.  Can
 *   be used in conjunction with BSD or SMALLOC (in which case you will get
 *   malloc statistics if DO_MSTATS is also defined).  SYSMALLOC incurs no
 *   additional cpu or memory overhead.
 * WRAPPEDMALLOC: wrapper for builtin system malloc.  Provides limited
 *   statistics, can be used in conjunction with BSDMALLOC/SMALLOC.  Limited
 *   additional cpu overhead and no additional memory overhead.
 * DEBUGMALLOC:  May be used in conjunction with BSDMALLOC/SMALLOC.  Provides
 *   statistics on precisely how much memory has been malloc'd (as well
 *   as the stats provided by WRAPPEDMALLOC).  Incurs a fair amount of
 *   overhead (both memory and cpu usage).
 *
 * [NOTE: BSDMALLOC and SMALLOC are also options however they must be
 *  selected from the Makefile rather than here since they are actual
 *  replacements for system malloc rather than wrappers for system malloc
 *  as are WRAPPEDMALLOC and DEBUGMALLOC.]
 */
#define SYSMALLOC
#undef WRAPPEDMALLOC
#undef DEBUGMALLOC

/* DO_MSTATS: do not define this unless BSDMALLOC or SMALLOC is chosen in the
 *   Makefile.  Defining this causes those replacement mallocs to keep
 *   statistics that the malloc_status() efun will print out (including total
 *   memory allocated/used).
 */
#undef DO_MSTATS

/* DEBUGMALLOC_EXTENSIONS: defining this (in addition to DEBUGMALLOC) enables
 * the set_malloc_mask(int) and debugmalloc(string,int) efuns.  These two
 * efuns basically allow you to cause certain malloc's and free's (with tags
 * selected by a specified mask) to print debug information (addr, tag,
 * description, size) to stdio (in the shell that invoked the driver) or to a
 * file.  Not defining this does reduce the overhead of DEBUGMALLOC from 16
 * bytes per malloc down to 8.  This macro has no effect if DEBUGMALLOC isn't
 * defined.
 */
#undef DEBUGMALLOC_EXTENSIONS

/* LOG_CATCHES: define this to cause errors that are catch()'d to be
 *   sent to the debug log anyway.
 */
#undef LOG_CATCHES

/* ARGUMENTS_IN_TRACEBACK: prints out function call arguments in error
 *   tracebacks, to aid in debugging.  Note: it prints the values of
 *   the arguments at the time of the error, not when the function
 *   was called.  It looks like this:
 *
 * Failed to load file: read_buffer
 * program: command/update.c, object: command/update line 15
 * '    commandHook' in '        clone/user.c' ('        clone/user#1')line 72
 * arguments were ("/read_buffer.c")
 * '           main' in '    command/update.c' ('      command/update')line 15
 * arguments were ("/read_buffer.c")
 */
#define ARGUMENTS_IN_TRACEBACK

/* LOCALS_IN_TRACEBACK: similar to ARGUMENTS_IN_TRACEBACK, but for local
 *   variables.  The output looks more or less like:
 *
 * locals: 1, "local_value"
 */
#define LOCALS_IN_TRACEBACK

/* MUDLIB_ERROR_HANDLER: If you define this, the driver doesn't do any
 *   handling of runtime errors, other than to turn the heartbeats of
 *   objects off.  Information about the error is passed in a mapping
 *   to the handle_error() function in the master object.  Whatever is
 *   returned is put in the debug.log.
 */
#undef MUDLIB_ERROR_HANDLER

/* SOCKET_EFUNS: define this to enable the socket efunctions.  This
 *   causes HAS_SOCKETS to be defined for all LPC objects.
 */
#define SOCKET_EFUNS

/* OPTIMIZE_FUNCTION_TABLE_SEARCH: define this if you want the function
 *   table to be sorted for faster lookups (ie binary search).  The flipside
 *   of this is that there is some overhead in maintaining the sorted table.
 *
 * WARNING: Currently broken, I think.  -Beek
 */
#define OPTIMIZE_FUNCTION_TABLE_SEARCH

/* CONFIG_FILE_DIR specifies a directory in which the driver will search for
 *   config files by default.  If you don't wish to use this define, you may
 *   always specify a full path to the config file when starting the driver.
 */
#ifndef LATTICE
#define CONFIG_FILE_DIR "/usr/mud/mudos/etc"
#else
#define CONFIG_FILE_DIR "/usr/mud/mudos/etc"
#endif

/* OLD_COMMAND: if this is defined, then the command() efun may take a 2nd
 *   argument specifying on which object to perform the command.
 */
#undef OLD_COMMAND

/* MATH: determines whether or not the math efuns (for floats) are included.
 */
#define MATH

/* MATRIX: determines whether or not the 3d graphics efuns (for floats)
 *   are included - see func_spec.c for a list.
 */
#undef MATRIX

/* LAZY_RESETS: if this is defined, an object will only have reset()
 *   called in it when it is touched via call_other() or move_object()
 *   (assuming enough time has passed since the last reset).  If LAZY_RESETS
 *   is #undef'd, then reset() will be called as always (which guaranteed that
 *   reset would always be called at least once).  The advantage of lazy
 *   resets is that reset doesn't get called in an object that is touched
 *   once and never again (which can save memory since some objects won't get
 *   reloaded that otherwise would).
 */
#undef LAZY_RESETS

/* SAVE_EXTENSION: defines the file extension used by save_object().
 *   and restore_object().  Some sysadmins run scripts that periodically
 *   scan for and remove files ending in .o (but many mudlibs are already
 *   set up to use .o thus we leave .o as the default).
 */
#define SAVE_EXTENSION ".o"

/* SANE_EXPLODE_STRING: define this if you want to prevent explode_string
 *   from stripping off more than one leading delimeters.  #undef it for the
 *   old behavior.
 */
#undef SANE_EXPLODE_STRING

/* EACH: define this if you want the each() operator for mappings.  Undefining
 *   EACH save about 12 bytes per allocated mapping but will make the each()
 *   efun unavailable.  Many people think each() is a bad efun to have but
 *   its here because people use it and would gripe if I took it away.  The
 *   alternative to each() is to use keys() and iterate over the returned
 *   array.
 */
#undef EACH

/* STRICT_TYPE_CHECKING: define this if you wish to force formal parameter
 *   to include types.  If this is undef'd, then grossnesses like:
 *   func(obj) { string foo;  foo = allocate(3); } are allowed.
 */
#undef STRICT_TYPE_CHECKING

/* IGNORE_STRICT_PRAGMA: define this if you wish the #pragma strict_types to
 *   be ignored.  This should normally be #undef'd but is useful in
 *   certain situations.
 */
#undef IGNORE_STRICT_PRAGMA

/* NO_ANSI: define if you wish to disallow users from typing in commands that
 *   contain ANSI escape sequences.  Defining NO_ANSI causes all escapes
 *   (ASCII 27) to be replaced with a space ' '.
 */
#define NO_ANSI

/* OPC_PROF: define this if you wish to enable OPC profiling. Allows a dump
 *   of the # of times each efun is invoked (via the opcprof() efun).
 */
#undef OPCPROF

/* TRAP_CRASHES:  define this if you want MudOS to call crash() in master.c
 *   and then shutdown when signals are received that would normally crash the
 *   driver.
 */
#define TRAP_CRASHES

/* DROP_CORE: define this if you want the driver to attempt to create
 *   a core file when it crashes via the crash_MudOS() function.  This
 *   define only has an affect if -DDEBUG isn't defined in the makefile
 *   (except for the SIGINT and SIGTERM signals which are always trapped).
 *
 * [NOTE: keep this undefined for now since it seems to hang some machines
 *  upon crashing (some DECstations apparently).  If you want to get a core
 *  file, undef'ing TRAP_CRASHES should work.]
 */
#undef DROP_CORE

/* THIS_PLAYER_IN_CALL_OUT: define this if you wish this_player() to be
 *   usable from within call_out() callbacks.
 */
#define THIS_PLAYER_IN_CALL_OUT

/* AUTO_SETEUID: when an object is created it's euid is automatically set to
 *   the equivalent of seteuid(getuid(this_object())).  undef AUTO_SETEUID
 *   if you would rather have the euid of the created object be set to 0.
 */
#define AUTO_SETEUID

/* AUTO_TRUST_BACKBONE: define this if you want objects with the backbone
 *   uid to automatically be trusted and to have their euid set to the uid of
 *   the object that forced the object's creation.
 */
#define AUTO_TRUST_BACKBONE

/* PRIVS: define this if you want object privledges.  Your mudlib must
 *   explicitly make use of this functionality to be useful.  Defining this
 *   this will increase the size of the object structure by 4 bytes (8 bytes
 *   on the DEC Alpha) and will add a new master apply during object creation
 *   to "privs_file".  In general, priveleges can be used to increase the
 *   granularity of security beyond the current root uid mechanism.
 *
 * [NOTE: for those who'd rather do such things at the mudlib level, look at
 *  the inherits() efun and the 'valid_object' apply to master.]
 */
#undef PRIVS

/* HEARTBEAT_INTERVAL: define heartbeat interval in microseconds (us).
 *   1,000,000 us = 1 second.  The value of this macro specifies
 *   the frequency with which the heart_beat method will be called in
 *   those LPC objects which have called set_heart_beat(1).
 *
 * [NOTE: if SYSV is defined, alarm() is used instead of ualarm().  Since
 *  alarm() requires its argument in units of a second, we map 1 - 1,000,000 us
 *  to an actual interval of one (1) second and 1,000,001 - 2,000,000 maps to
 *  an actual interval of two (2) seconds, etc.]
 */
#define HEARTBEAT_INTERVAL 2000000

/* OLD_HEARTBEAT: define this if you want the old heartbeat semantics.
 *   In the new semantics, set_heart_beat(ticks), specifies the number of
 *   HEARTBEAT_INTERVAL ticks to be used, where ticks can be > 1 for
 *   multiple tick intervals.  If you define this all values for ticks > 1
 *   will be mapped to ticks = 1.
 */
#undef OLD_HEARTBEAT

/* LARGEST_PRINTABLE_STRING: defines the size of the vsprintf() buffer in
 *   comm.c's add_message(). Instead of blindly making this value larger,
 *   mudlib should be coded to not send huge strings to users.
 */
#define LARGEST_PRINTABLE_STRING 16384

/* MESSAGE_BUFFER_SIZE: determines the size of the buffer for output that
 *   is sent to users.
 */
#define MESSAGE_BUFFER_SIZE 4096

/* APPLY_CACHE_BITS: defines the number of bits to use in the call_other cache
 *   (in interpret.c).  Somewhere between six (6) and ten (10) is probably
 *   sufficient.
 */
#define APPLY_CACHE_BITS 11

/* CACHE_STATS: define this if you want call_other (apply_low) cache statistics.
 */
#define CACHE_STATS

/* CAST_CALL_OTHERS: define this if you want to require casting of call_other's;
 *   this was the default behavior of the driver prior to this addition.
 */
#undef CAST_CALL_OTHERS

/* INTERACTIVE_CATCH_TELL: define this if you want catch_tell called on
 *   interactives as well as NPCs.  If this is defined, user.c will need a
 *   catch_tell(msg) method that calls receive(msg);
*/
#undef INTERACTIVE_CATCH_TELL

/* NONINTERACTIVE_STDERR_WRITE: if defined, all writes/tells/etc to
 *   noninteractive objects will be written to stderr prefixed with a ']'
 *   (old behavior).
 */
#define NONINTERACTIVE_STDERR_WRITE

/* TRACE: define this to enable the trace() and traceprefix() efuns.
 *   (keeping this undefined will cause the driver to run faster).
 */
#undef TRACE

/* RESTRICTED_ED: define this if you want restricted ed mode enabled.
 */
#define RESTRICTED_ED

/* NO_SHADOWS: define this if you want to disable shadows in your driver.
 */
#undef NO_SHADOWS

/* NO_LIGHT: define this to disable the set_light() and driver maintenance
 *   of light levels in objects.  You can simulate it via LPC if you want...
 */
#undef NO_LIGHT

/* NO_MUDLIB_STATS: define this to disable domain and author stats
 *   maintenance by the driver.  These mudlib stats are more domain
 *   based than user based, and replaces the traditional wiz_list stats.
 */
#undef NO_MUDLIB_STATS

/* SNOOP_SHADOWED: define this if you want snoop to report what is
 *   sent to the player even in the event that the player's catch_tell() is
 *   shadowed and the player may not be seeing what is being sent.  Messages
 *   of this sort will be prefixed with $$.
 */
#undef SNOOP_SHADOWED

/* RECEIVE_SNOOP: define this if you want snoop text to be sent to
 *   the receive_snoop() function in the snooper object (instead of being
 *   sent directly via add_message()).  This is useful if you want to
 *   build a smart client that does something different with snoop messages.
 */
#undef RECEIVE_SNOOP

/* PROFILE_FUNCTIONS: define this to be able to measure the CPU time used by
 *   all of the user-defined functions in each LPC object.  Note: defining
 *   this adds three long ints (12 bytes on 32-bit machines) to the function
 *   header structs.  Also note that the resolution of the getrusage() timer
 *   may not be high enough on some machines to give non-zero execution
 *   times to very small (fast) functions.  In particular if the clock
 *   resolution is 1/60 of a second, then any time less than approxmately 15k
 *   microseconds will resolve to zero (0).
*/
#undef PROFILE_FUNCTIONS

/* DISALLOW_BUFFER_TYPE: if this is #define'd then LPC code using the 'buffer'
 *   type won't be allowed to compile (since the 'buffer' type won't be
 *   recognized by the lexer.
 */
#undef DISALLOW_BUFFER_TYPE

/* BINARIES: define this to enable the 'save_binary' pragma.
 *   This pragma, when set in a program, will cause it to save a
 *   binary image when loaded, so that subsequent loadings will
 *   be much faster.  The binaries are saved in the directory
 *   specified in the configuration file.  The binaries will not
 *   load if the LPC source or any of the inherited or included
 *   files are out of date, in which case the file is compiled
 *   normally (and may save a new binary).
 *
 *   In order to save the binary, valid_save_binary() is called
 *   in master.c, and is passed the name of the source file.  If
 *   this returns a non-zero value, the binary is allowed to be
 *   saved.  Allowing any file by any wizard to be saved as a
 *   binary is convenient, but may take up a lot of disk space.
 *
 * WARNING: Currently, this doesn't work on 64 bit machines (ie DEC Alpha).
 *          Might not work on Linux or IRIX/
 */
#define BINARIES

/* ALWAYS_SAVE_BINARIES: define this to cause every LPC file to behave
 *   as if it contains a line '#pragma save_binary'.  This #define has no
 *   affect if BINARIES is not defined.
*/
#define ALWAYS_SAVE_BINARIES

/* LPC_TO_C: define this to enable LPC->C compilation.
 *
 * [NOTE: In addition, you must uncomment the C_EFUNS line in your
 *  Makefile or GNUmakefile.  This is done separately to save non-LPC_TO_C
 *  users from having to yacc & compile unused files.]
 * [NOTE: BINARIES must also be defined for LPC->C to work.  Actually
 *  using binaries is not required, though.] 
 */
#undef LPC_TO_C

/*
 * RUNTIME_LOADING: define this to enable runtime loading of LPC->C
 *   objects.  Has no effect if LPC_TO_C is off.
 * WARNING: This is experimental code.  It is known to work on the
 *          following architectures:  SunOS 4.1, Linux, and SGI.
 */
#define RUNTIME_LOADING

/* ALWAYS_SAVE_COMPILED_BINARIES: define this to cause every file that
 *   is compiled to C code to behave as if it contains a line
 *   '#pragma save_binary'.  This #define has no affect if BINARIES and
 *   LPC_TO_C are not defined.
 */
#define ALWAYS_SAVE_COMPILED_BINARIES

/* TRACE_CODE: define this for to enable code tracing (the driver will print
 *   out the previous lines of code to an error) eval_instruction() runs about
 *   twice as fast when this is not defined (for the most common eoperators).
 */
#undef TRACE_CODE

/* Some maximum string sizes
 */
#define SMALL_STRING_SIZE     100
#define LARGE_STRING_SIZE     1000
#define COMMAND_BUF_SIZE      2000

/* Number of levels of nested datastructures allowed -- this limit prevents
 * crashes from occuring when saving objects containing variables containing
 * recursive datastructures (with circular references).
 */
#define MAX_SAVE_SVALUE_DEPTH 25

/* Miscellaneous config options that should probably be in the runtime
 * config file.
 */
/* MAX_LOCAL: maximum number of local variables allowed per LPC function */
#define MAX_LOCAL 30              /* get_config_int(8)  */
/* MAX_USERS: maximum number of simultaneous interactive users allowed */
#define MAX_USERS 40              /* get_config_int(12) */
/* MAX_EFUN_SOCKS: maximum number of efun sockets */
#define MAX_EFUN_SOCKS 16         /* get_config_int(24) */

#define EVALUATOR_STACK_SIZE 1000 /* get_config_int(4)  */
#define COMPILER_STACK_SIZE 200   /* get_config_int(5)  */
#define MAX_TRACE 30              /* get_config_int(6)  */
#define LIVING_HASH_SIZE 101      /* get_config_int(20) */

/* NEXT_MALLOC_DEBUG: define this if using a NeXT and you want to enable
 *   the malloc_check() and/or malloc_debug() efuns.  Run the 'man malloc_debug'
 *   command on the NeXT to find out what the arguments to malloc_debug(int)
 *   mean.  The malloc_check() efun calls the NeXT NXMallocCheck() system
 *   call which does a consistency check on malloc's data structures (this
 *   consistency check is done at each malloc() and free() for certain
 *   malloc_debug() levels).  A non-zero return value indicates there was
 *   a consistency problem.  For those NeXT users wanting a bit more
 *   performance out of malloc, try defining NEXT_MALLOC_DEBUG and calling the
 *   malloc_debug(-1) efun (with an arg of -1).  This will turn all
 *   malloc debugging off and call malloc_singlethreaded() which the NeXT
 *   malloc man page claims can make NeXT system malloc 10% to 15% faster.
 *
 * [NOTE: This #define has no affect on the driver if not using the
 *  NeXTSTEP OS.]
 *
 * Warning: if you use a NeXT and define NEXT_MALLOC_DEBUG, be sure to
 *          protect the use of the malloc_check() and malloc_debug() efuns
 *          since setting certain debug levels can cause malloc() and free()
 *          to become _very_ slow (protect efuns by using simul_efuns and
 *          valid_override).
 *
 * [NOTE: malloc_debug(6) is a good compromise between efficiency and
 *  completeness of malloc debugging (malloc/free will be about half as fast).]
 */
#undef NEXT_MALLOC_DEBUG

/* Current version of the driver.
 * (the patchlevel is automatically appended to the end)
 */
#define VERSION "0.9."
