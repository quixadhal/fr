#include <stdio.h>
 
#include <string.h>
 
#include "config.h"
#include "lint.h"
#include "interpret.h"
#include "mapping.h"
#include "buffer.h"
#include "object.h"
#include "exec.h"
 
/*
 * Write statistics about objects on file.
 */
 
extern struct object *obj_list;
 
int sumSizes(m, elt, t)
struct mapping *m;
struct node *elt;
int *t;
{
     int svalue_size PROT((struct svalue *));
 
     *t += (svalue_size(&elt->values[0]) + svalue_size(&elt->values[1]));
     *t += sizeof(struct node);
     return 0;
}
 
int svalue_size(v)
    struct svalue *v;
{
    int i, total;
 
    switch(v->type) {
    case T_OBJECT:
    case T_REAL:
    case T_NUMBER:
      return 0;
    case T_STRING:
      return (int)(strlen(v->u.string) + 1);
    case T_POINTER:
      /* first svalue is stored inside the vector struct */
      total = sizeof(struct vector) - sizeof(struct svalue);
      for (i = 0, total = 0; i < v->u.vec->size; i++) {
        total += svalue_size(&v->u.vec->item[i]) + sizeof(struct svalue);
      }
      return total;
    case T_MAPPING:
        total = sizeof(struct mapping);
        mapTraverse(v->u.map, (int (*)())sumSizes, &total);
        return total;
    case T_FUNCTION:
    return (int)(sizeof(struct funp) + svalue_size(&v->u.fp->obj) +
        svalue_size(&v->u.fp->fun));
    case T_BUFFER:
	/* first byte is stored inside the buffer struct */
    return (int)(sizeof(struct buffer) + v->u.buf->size - 1);
    case T_ANY:
        break;
    default:
      fatal("Illegal type: %d\n", v->type);
    }
    /*NOTREACHED*/
    return 0;
}
 
int data_size(ob)
    struct object *ob;
{
    int total = 0, i;
    if (ob->prog) {
        for (i = 0; i < (int)ob->prog->p.i.num_variables; i++) {
            total += svalue_size(&ob->variables[i]) + sizeof (struct svalue);
        }
    }
    return total;
}
 
void dumpstat(tfn)
char *tfn;
{
    FILE *f;
    struct object *ob;
    char *fn;
    int display_hidden;
 
    fn = check_valid_path(tfn, current_object, "dumpallobj", 1);
    if (!fn) {
                add_message("Invalid path '%s' for writing.\n", tfn);
                return;
        }
 
        f = fopen(fn, "w");
    if (!f) {
                add_message("Unable to open '%s' for writing.\n", fn);
                return;
        }
    add_message("Dumping to %s.",fn);
 
    display_hidden = -1;
    for (ob = obj_list; ob; ob = ob->next_all) {
        int tmp;
        if (ob->flags & O_HIDDEN) {
          if (display_hidden == -1)
            display_hidden = valid_hide(current_object);
          if (!display_hidden) continue;
        }
        if (ob->prog && (ob->prog->p.i.ref == 1 || !(ob->flags & O_CLONE)))
            tmp = ob->prog->p.i.total_size;
        else
            tmp = 0;
    fprintf(f, "%-20s %lu ref %2d %s %s (%d) %s\n", ob->name,
        tmp + data_size(ob) + sizeof (struct object), ob->ref,
        ob->flags & O_HEART_BEAT ? "HB" : "  ",
        ob->super ? ob->super->name : "--",/*ob->cpu*/ 0,
        (ob->swap_num >= 0) ? ((ob->flags & O_SWAPPED) ?
            "SWAPPED(out)" : "SWAPPED(in)") : "");
    }
    add_message("done.\n");
    fclose(f);
}
