#include "config.h"
#include <sys/types.h>
#include <sys/stat.h>
#if !defined(SunOS_5)
#include <sys/dir.h>
#endif
#include <fcntl.h>
#include <setjmp.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <memory.h>
#if defined(sun)
#include <alloca.h>
#endif
#ifdef M_UNIX
#include <dirent.h>
#endif

#include "lint.h"
#include "opcodes.h"
#include "interpret.h"
#include "object.h"
#include "sent.h"
#include "exec.h"
#include "comm.h"
#include "debug.h"

extern int errno;
extern int current_time;
extern int comp_flag;

extern char *inherit_file;

/* prevents infinite inherit loops.
   No, mark-and-sweep solution won't work.  Exercise for reader.  */
extern int num_objects_this_thread; 

#ifndef NeXT
extern int readlink PROT((char *, char *, int));
extern int symlink PROT((char *, char *));
#endif /* NeXT */
     
#if !defined(hpux) && !defined(_AIX) && !defined(__386BSD__) \
	&& !defined(linux) && !defined(SunOS_5)
extern int fchmod PROT((int, int));
#endif /* !defined(hpux) && !defined(_AIX) */
char *last_verb;
     
extern int set_call PROT((struct object *, struct sentence *, int, int)),
       legal_path PROT((char *));
     
void pre_compile PROT((char *)),
       remove_interactive PROT((struct object *)),
       add_light PROT((struct object *, int)),
       add_action PROT((char *, char *, int)),
       ipc_remove(),
       set_snoop PROT((struct object *, struct object *)),
       print_lnode_status PROT((int)),
       start_new_file PROT((FILE *)), end_new_file(),
       move_or_destruct PROT((struct object *, struct object *)),
       load_ob_from_swap PROT((struct object *)), dump_malloc_data(),
       print_svalue PROT((struct svalue *)),
       debug_message_value(),
       destruct2();

#ifdef OLD_ADD_ACTION
void  add_verb PROT((char *, int));
#endif
 
extern int d_flag;
     
extern struct object *obj_list, *obj_list_destruct, *master_ob;

extern userid_t *backbone_uid;

extern struct object *current_object;      
       /* The object interpreting a function. */

extern struct object *command_giver;       
       /* Where the current command came from. */

extern struct object *current_interactive; 
       /* The user who caused this execution */
     
extern int num_parse_error;		/* Number of errors in the parser. */
     
/*******************************************************************/

#ifdef F_EVENT
/*
 * event call, calls "event_"+event_fun on all objects in event_ob,
 * with the params event_param.
 * if event_ob is an array, then calls "event_"+event_fun on all of the
 * objects in the array.
 */
void event(event_ob, event_fun, numparam, event_param)
  struct svalue *event_ob;
  char *event_fun;
  int numparam;
  struct svalue *event_param;
{
  struct object *ob;
  struct object *origin;
  char *name;
  int i;

  origin = current_object;
  name = (char *)XALLOC(strlen(event_fun)+7);
  strcpy(name, "event_");
  strcat(name, event_fun);
  if (event_ob->type == T_POINTER) {
    int ind;

    for (ind=0; ind<event_ob->u.vec->size; ind++) {
      if (event_ob->u.vec->item[ind].type != T_OBJECT
           || event_ob->u.vec->item[ind].u.ob->flags&O_DESTRUCTED)
        continue;
      push_object(origin);
      for (i=0;i<numparam;i++)
        push_svalue(event_param+i);
      (void)apply(name, event_ob->u.vec->item[ind].u.ob, numparam+1);
    }
  } else { /* (event_ob->type == T_OBJECT) */
    /*
     * first call on the original object.
     */
    push_object(origin);
    for (i=0;i<numparam;i++)
      push_svalue(event_param+i);
    (void)apply(name, event_ob->u.ob, numparam+1);
    /*
     * call on all the objects in it.
     */
    for (ob = event_ob->u.ob->contains; ob; ob = ob->next_inv) {
      if (ob == origin) continue;
      if (ob->flags & O_DESTRUCTED) continue;
      push_object(origin);
      for (i=0;i<numparam;i++)
        push_svalue(event_param+i);
      (void)apply(name, ob, numparam+1);
    }
  }
  FREE(name);
} /* end of event() */
#endif /* F_EVENT */

#ifdef F_FILE_LENGTH
/*
 * file_length() efun, returns the number of lines in a file.
 */
int file_length(file)
  char *file;
{
  struct stat st;
  FILE *f;
  unsigned int i;
  int ret;

  file = check_valid_path(file, current_object, "file_size", 0);
  if (!file) return -1;
  if (stat(file, &st) == -1)
    return -1;
  if (st.st_mode == S_IFDIR)
    return -2;
  if (!(f = fopen(file, "r")))
    return -1;
  ret = 0;
  for (i=0; i<st.st_size; i++) if (fgetc(f) == '\n') ret++;
  fclose(f);
  return ret;
} /* end of file_length() */
#endif /* F_FILE_LENGTH */

#ifdef F_PLURALIZE
/*
 * NB: it is always preferable for objects to set thier plural using
 *     "set_plural()" (on std/object), but if the relevant programmer hasn't
 *     done so, "query_plural()" (also on std/object) calls this efun for
 *     a hopefully reasonable approximate.  objects should _always_ call
 *     call "query_plural()" to get the plural form of an object's "short()",
 *     failure to do so is treason, and subject to punishment by summary
 *     execution.  The Computer is your friend.
 */
/******************
 * Unsafe at the moment, must handle very short strings....
 ******************/
#define PLURAL_FOUND FREE(rel); return pre
char *pluralize(str)
  char *str;
{
  char *pre, *rel;
  int i;
 
  if (strlen(str) == 1) return 0;

  pre = XALLOC(100);
  rel = XALLOC(200);
  /*
   * first, get rid of determiners.  pluralized forms never have them ;)
   */  
  if (!((sscanf(str, "a %[^]", pre, rel) == 2) ||
        (sscanf(str, "an %[^]", pre, rel) == 2) ||
        (sscanf(str, "the %[^]", pre, rel) == 2))) {
    strcpy(rel, str);
  }
  /*
   * only pluralize the last word, ie: lose adjectives.
   */
  pre[0] = '\0';
  for (i=strlen(rel); i; i--) {
    if (rel[i-1] == ' ') {
      int j;
      for (j=0; j<i; j++) pre[j] = rel[j];
      pre[i] = '\0';
      strcpy(rel, rel+i);
    }
  }
  i = strlen(rel) - 1;
  /*
   * trap the exceptions to the rules below and special cases.
   */
  if (!strcasecmp(rel, "fish") || !strcasecmp(rel, "deer")
      || !strcasecmp(rel, "sheep")) {
    strcat(pre, rel);
    PLURAL_FOUND;
  }
  if (!strcasecmp(rel, "child")) {
    strcat(pre, rel);
    strcat(pre, "ren");
    PLURAL_FOUND;
  }
  if (!strcasecmp(rel, "tooth")) {
    strcat(pre, "teeth");
    PLURAL_FOUND;
  }
  if (!strcasecmp(rel, "smurf")) {
    strcat(pre, "smurfs");
    PLURAL_FOUND;
  }
  if (!strcasecmp(rel, "ox") || !strcasecmp(rel, "vax")) {
    strcat(pre, rel);
    strcat(pre, "en");
    PLURAL_FOUND;
  }
  if (!strcasecmp(rel, "bus")) {
    strcat(pre, rel);
    strcat(pre, "es");
    PLURAL_FOUND;
  }
  /*
   * now handle "rules" ... god I hate english!!
   */
  /*
   * *x -> *xes (fox -> foxes)
   * *s -> *ses (pass -> passes)
   * *ch -> *ches (church -> churches)
   * *sh -> *shes (brush -> brushes)
   */
  if ((rel[i] == 's') || (rel[i] == 'x') || 
      !strcasecmp(rel+i-1, "ch") || !strcasecmp(rel+i-1, "sh")) {
    strcat(pre, rel);
    strcat(pre, "es");
    PLURAL_FOUND;
  }
  /*
   * *ff -> *ves (staff -> staves)
   * *fe -> *ves (knife -> knives)
   */
  if (!strcasecmp(rel+i-1, "ff") || !strcasecmp(rel+i-1, "fe")) {
    rel[i-1] = '\0';
    strcat(pre, rel);
    strcat(pre, "ves");
    PLURAL_FOUND;
  }
  /*
   * *f -> *ves (half -> halves)
   * *ef -> *efs (chef -> chefs) (really a rule for a special case)
   */
  if (rel[i] == 'f') {
    if (rel[i-1] == 'e') {
      strcat(pre, rel);
      strcat(pre, "s");
      PLURAL_FOUND;
    }
    rel[i] = '\0';
    strcat(pre, rel);
    strcat(pre, "ves");
    PLURAL_FOUND;
  }
  /*
   * *y -> *ies (gumby -> gumbies)
   */
  if (rel[i] == 'y') {
    rel[i] = '\0';
    strcat(pre, rel);
    strcat(pre, "ies");
    PLURAL_FOUND;
  }
  /*
   * *us -> *i (virus -> viri)
   */
  if (!strcasecmp(rel+i-1, "us")) {
    rel[i-1] = '\0';
    strcat(pre, rel);
    strcat(pre, "i");
    PLURAL_FOUND;
  }
  /*
   * *man -> *men (foreman -> foremen)
   */
  if (!strcasecmp(rel+i-2, "man")) {
    rel[i-1] = 'e';
    strcat(pre, rel);
    PLURAL_FOUND;
  }
  /*
   * *is -> *es (this is from gordons pluralize ... )
   */
  if (!strcasecmp(rel+i-1, "is")) {
    rel[i-1] = 'e';
    strcat(pre, rel);
    PLURAL_FOUND;
  }
  /*
   * *o -> *s (also from gordon)
   */
  if (rel[i] == 'o') {
    rel[i] = '\0';
    strcat(pre, rel);
    strcat(pre, "s");
    PLURAL_FOUND;
  }
  /*
   * default: (* -> *s)
   */
  strcat(pre, rel);
  strcat(pre, "s");
  PLURAL_FOUND;
} /* end of pluralize() */
#endif /* F_PLURALIZE */

#ifdef F_ACTIONS_DEFINED
/*
 * Returns the actions defined by "by" on "on" in the format:
 * (assuming all data possible is returned)
 * ({
 *   "command", ({
 *     object_defining_action,
 *     "function called",
 *     short_verb,
 *     priority
 *   })
 * })
 * if "by" is NULL then returns all commands defined.
 * "on"defaults to command_giver.
 * "flags" has the following format:
 *   0000 : no optional data, return array of command names.
 *   1xxx : include the object defining the action.
 *   x1xx : include the name of the function called.
 *   xx1x : include position of star + 1 (0 if not exist).
 *   xxx1 : include the actions priority.
 */
struct vector *actions_defined(by, on, flags)
  struct object *by, *on;
  int flags;
{
  /* number of bits in:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
  static char bits[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
  struct sentence *s;
  struct vector *ret;
  int num, ind;

  if (!on) on = command_giver;
  num = 0;
  for (s = on->sent; s; s = s->next) if (!by || s->ob == by) num++;
  if (!num) return allocate_array(0);
  if (flags) num *= 2;
  ret = allocate_array(num);
  num = 0;
  for (s = on->sent; s; s = s->next) if (!by || s->ob == by) {
    ret->item[num].type = T_STRING;
    ret->item[num].subtype = STRING_MALLOC;
    ret->item[num].u.string = string_copy(s->verb);
    num++;
    if (!flags) continue;
    /* wonder if this would be better as a series of for loops */
    ret->item[num].type = T_POINTER;
    ret->item[num].u.vec = allocate_array((int)bits[flags]);
    ind = 0;
    if (flags & 0x8) { /* then include object defining */
      ret->item[num].u.vec->item[0].type = T_OBJECT;
      ret->item[num].u.vec->item[0].u.ob = s->ob;
      add_ref(s->ob, "actions_defined");
      ind++;
    }
    if (flags & 0x4) { /* then include function name */
      ret->item[num].u.vec->item[ind].type = T_STRING;
      ret->item[num].u.vec->item[ind].subtype = STRING_MALLOC;
      ret->item[num].u.vec->item[ind].u.string = string_copy(s->function);
      ind++;
   }
    if (flags & 0x2) { /* then include star */
      ret->item[num].u.vec->item[ind].type = T_NUMBER;
      ret->item[num].u.vec->item[ind].u.number = s->star + 1;
      ind ++;
    }
    if (flags & 0x1) { /* then include priority */
      ret->item[num].u.vec->item[ind].type = T_NUMBER;
      ret->item[num].u.vec->item[ind].u.number = s->priority;
    }
    num++;
  }
  return ret;
} /* end of actions_defined() */
#endif /* F_ACTIONS_DEFINED */
