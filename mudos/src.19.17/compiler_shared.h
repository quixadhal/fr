#include "config.h"
#define _YACC_
#include "lint.h"
#include <string.h>
#include <stdio.h>
#ifndef LATTICE
#include <memory.h>
#endif
#ifdef __386BSD__
#include <stdlib.h>
#endif
#if defined(sun)
#include <alloca.h>
#endif
#if defined(NeXT) || defined(SunOS_5)
#include <stdlib.h>
#endif
#ifdef sun
#include <malloc.h>
#endif

#include "mudlib_stats.h"
#include "interpret.h"
#include "object.h"
#include "exec.h"
#include "instrs.h"
#include "switch.h"
#include "opcodes.h"
#include "incralloc.h"
#include "applies.h"

#define YYMAXDEPTH    600

/* NUMPAREAS ares are saved with the program code after compilation,
 * the rest are only temporary.
 */
#define A_PROGRAM		0	/* executable code */
#define A_FUNCTIONS		1	/* table of functions */
#define A_STRINGS		2	/* table of strings */
#define A_VARIABLES		3	/* table of variables */
#define A_LINENUMBERS		4	/* linenumber information */
#define A_INHERITS		5	/* table of inherited progs */
#define A_ARGUMENT_TYPES	6	/* */
#define A_ARGUMENT_INDEX	7	/* */
#define NUMPAREAS		8
#define A_CASE_NUMBERS		8	/* case labels for numbers */
#define A_CASE_STRINGS		9	/* case labels for strings */
#define A_CASE_LABELS		10	/* used to build switch tables */
#define A_STRING_NEXT		11	/* next prog string in hash chain */
#define A_STRING_REFS		12	/* reference count of prog string */
#define A_INCLUDES		13	/* list of included files */
#define A_PATCH			14	/* for save_binary() */
#define A_INITIALIZER           15
#define NUMAREAS		16

#define BREAK_ON_STACK          0x40000
#define BREAK_FROM_CASE         0x80000

#define SWITCH_STACK_SIZE  200
#define EXPR_STACK_SIZE  200

#define BREAK_DELIMITER       -0x200000
#define CONTINUE_DELIMITER    -0x40000000

/* make sure that this struct has a size that is a power of two */
struct case_heap_entry { int key; short addr; short line; };
#define CASE_HEAP_ENTRY_ALIGN(offset) offset &= -sizeof(struct case_heap_entry)

extern struct mem_block mem_block[NUMAREAS];

/*
 * Some good macros to have.
 */

#define BASIC_TYPE(e,t) ((e) == TYPE_ANY ||\
                         (e) == (t) ||\
                         (t) == TYPE_ANY)

#define TYPE(e,t) (BASIC_TYPE((e) & TYPE_MOD_MASK, (t) & TYPE_MOD_MASK) ||\
                (((e) & TYPE_MOD_POINTER) && ((t) & TYPE_MOD_POINTER) &&\
                BASIC_TYPE((e) & (TYPE_MOD_MASK & ~TYPE_MOD_POINTER),\
                (t) & (TYPE_MOD_MASK & ~TYPE_MOD_POINTER))))

#define FUNCTION(n) ((struct function *)mem_block[A_FUNCTIONS].block + (n))
#define VARIABLE(n) ((struct variable *)mem_block[A_VARIABLES].block + (n))

#if !defined(__alpha) && !defined(cray)
#define align(x) (((x) + 3) & ~3)
#else
#define align(x) (((x) + 7) & ~7)
#endif

/*
 * If the type of the function is given, then strict types are
 * checked and required.
 */
extern int exact_types;
extern int pragma_strict_types;
#ifdef SAVE_BINARIES
extern int pragma_save_binaries;/* here too :-) */
#endif
extern int approved_object;

extern int total_num_prog_blocks, total_prog_block_size;

extern int num_parse_error;
extern int d_flag;

#define SOME_NUMERIC_CASE_LABELS 0x40000
#define NO_STRING_CASE_LABELS    0x80000

extern int current_type;
extern int heart_beat; /* number of the heart_beat function */

extern int current_block;

extern struct program NULL_program;

extern struct program *prog; /* is returned to the caller */

extern short string_idx[0x100];
extern unsigned char string_tags[0x20];
extern short freed_string;

extern int current_line;
/*
 * 'inherit_file' is used as a flag. If it is set to a string
 * after yyparse(), this string should be loaded as an object,
 * and the original object must be loaded again.
 */
extern char *current_file, *inherit_file;
extern int current_line;
/*
 * 'inherit_file' is used as a flag. If it is set to a string
 * after yyparse(), this string should be loaded as an object,
 * and the original object must be loaded again.
 */
extern char *current_file, *inherit_file;

/*
 * The names and types of arguments and auto variables.
 */
extern char *local_names[MAX_LOCAL];
extern unsigned short type_of_locals[MAX_LOCAL];
extern int current_number_of_locals;

extern struct mem_block type_of_arguments;

/*
 * A mechanism to remember addresses on a stack. The size of the stack is
 * defined in config.h.
 */
extern int comp_stackp;
extern int comp_stack[COMPILER_STACK_SIZE];

extern int current_break_stack_need, max_break_stack_need;

#ifdef OPTIMIZE_FUNCTION_TABLE_SEARCH
extern int a_functions_root;
#endif

/* functions */
int check_declared PROT((char *str));
char *main_file_name();
char *get_two_types PROT((int type1, int type2));
void free_all_local_names(),
      smart_log PROT((char *, int, char *,int));
int yylex();
int verify_declared PROT((char *));
void copy_variables();
char *query_simul_efun_file_name();
int copy_functions PROT((struct program *, int type));
void type_error PROT((char *, int));
char *string_copy();
int compatible_types(int, int);
void add_arg_type(unsigned short);
int defined_function(char *);
void push_address();
void push_explicit(int);
int pop_address();
int find_in_table(struct function *, int);
void find_inherited(struct function *);
int define_new_function(char *, int, int, int, int, int);
void define_variable(char *, int, int);
char *get_type_name(int);
short store_prog_string(char *);
void free_prog_string(short);
int validate_function_call(struct function *, int, int);
/* inlines - if we're luckly, they'll get honored. */
INLINE
static void realloc_mem_block(m, size)
    struct mem_block *m;
    int size;
{
    while (size > m->max_size) {
	m->max_size <<= 1;
	m->block = (char *)
	DREALLOC((char *)m->block, m->max_size, 49, "realloc_mem_block");
    }
}

INLINE
static void add_to_mem_block(n, data, size)
    int n, size;
    char *data;
{
    struct mem_block *mbp = &mem_block[n];
    if (mbp->current_size + size > mbp->max_size)
	realloc_mem_block(mbp, mbp->current_size + size);
    if (data)
	memcpy(mbp->block + mbp->current_size, data, size);
    mbp->current_size += size;
}

INLINE
static void insert_in_mem_block(n, where, size)
     int n, where, size;
{
  struct mem_block *mbp = &mem_block[n];
  char *p;
  if (mbp->current_size + size > mbp->max_size)
    realloc_mem_block(mbp, mbp->current_size + size);
  /* memcpy can't handle overlapping blocks on some systems */
  p = mbp->block + mbp->current_size;
  while (p-->mbp->block + where) 
    *(p+size) = *p;
  mbp->current_size += size;
}

/*
 * Pop the argument type stack 'n' elements.
 */
INLINE
static void pop_arg_stack(n)
    int n;
{
    type_of_arguments.current_size -= sizeof (unsigned short) * n;
}

/*
 * Get type of argument number 'arg', where there are
 * 'n' arguments in total in this function call. Argument
 * 0 is the first argument.
 */
INLINE
static int get_argument_type(arg, n)
    int arg, n;
{
    return
	((unsigned short *)
	(type_of_arguments.block + type_of_arguments.current_size))[arg - n];
}

