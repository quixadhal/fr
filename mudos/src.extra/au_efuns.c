/* The efuns required to make a DWLib based mudlib work.
 * 21 Sept 1993 Chrisy
 */

#include "efuns.h"

#ifdef AURORA
#define F_RESET_EVAL_COST 

#ifdef F_EVENT
void
f_event(num_args, instruction)
int num_args, instruction;
{
  event((sp-num_args+1), (sp-num_args+2)->u.string, num_args-2,
        (sp-num_args+3));
  pop_n_elems(num_args-1);
}
#endif

#ifdef F_FILE_LENGTH
void
f_file_length(num_arg, instruction)
int num_arg, instruction;
{
  int l;

  l = file_length(sp->u.string);
  pop_stack();
  push_number(l);
}
#endif

#ifdef F_PLURALIZE
void
f_pluralize(num_arg, instruction)
int num_arg, instruction;
{
  char *s;
  extern char *pluralize();

  s = pluralize(sp->u.string);
  pop_stack();
  if (!s)
    push_number(0);
  else
    push_malloced_string(s);
}
#endif


#ifdef F_RESET_EVAL_COST
void
f_reset_eval_cost(num_args, instruction)
int num_args, instruction;
{
  eval_cost = 0;
  push_number(0);
}
#endif

#ifndef OLD_ADD_ACTION
#ifdef F_REMOVE_ACTION
/*
 * removes an action from objects in the inventory and enviroment of
 * current_object.  the "cmd" must be defined by the object.
 */
int remove_action(cmd, from)
  char *cmd;
  struct object *from;
{
  struct sentence **s, *t;
  int n;

  n = 0;
  for (s=&(from->sent); *s; ) {
    if ((*s)->ob == current_object) {
      if (strcasecmp((*s)->verb, cmd)) {
        s = &((*s)->next);
        continue;
      }
      t = *s;
      s = &((*s)->next);
      free_sentence(t);
      n++;
    }
  }
  return n;
} /* end of remove_action() */
#endif /* F_REMOVE_ACTION */

#ifdef F_ACTIONS_DEFINED
void f_actions_defined(num_arg, instruction)
int num_arg, instruction;
{
  struct vector *v;
  extern struct vector *actions_defined();
  struct object *arg1, *arg2;
  int arg3;

  if (num_arg && ((sp-num_arg+1)->type == T_OBJECT))
          arg1 = (sp-num_arg+1)->u.ob;
  else arg1 = 0;
  if ((num_arg > 1) && ((sp-num_arg)->type == T_OBJECT))
    arg2 = (sp-num_arg)->u.ob;
  else arg2 = 0;
  if (num_arg > 2) /* only first two arg types caught by parser */
    if (sp->type != T_NUMBER) bad_arg(3, instruction);
    else arg3 = sp->u.number;
  else arg3 = 0; /* defaults to no optional data */
  v = actions_defined(arg1, arg2, arg3);
  pop_n_elems(num_arg);
  push_vector(v);
  v->ref--; /* fix ref count */
}
#endif /* F_ACTIONS_DEFINED */
#endif
#endif
