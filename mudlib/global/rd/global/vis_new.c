// /global/vision.c

// 1995 Jun 30 Laggard      look and glance (renamed x_) are moved here,
//                          better speed than external, access to this_player()
//                          verbose renamed long_view, and moved here.
//                          new show_view() does glance/look
// 1995 August 11 Asmodean  Altered x_look to handle output in trans.
// 1995 August 28 Dyraen    Changed write()'s to do_efun_write()'s. As
//                          trans is still causing problems.


#include <commands.h>
inherit "global/more_string";

#define TO this_object()

int long_view;


int query_verbose()
{
  return long_view;
}


int brief_verbose(string str)
{
  if (str == "on")
    long_view = (query_verb() == "verbose");
  else if (str == "off")
    long_view = (query_verb() == "brief");
  else if (str) {
    notify_fail("Usage: "+query_verb()+" <on/off>\n");
    return 0;
  } else
    long_view = !long_view;

  if (long_view)
    write("You are in verbose mode.\n");
  else
    write("You are in brief mode.\n");
  return 1;
}


int x_glance(string arg)
{
    object me = this_object();
    object here = environment(me);
    object *ob;
    int i, dark;
    string ret = "";
    string exits = 0;

    if (!here)
    {
        notify_fail("You are in limbo...."
            +" Sorry, you can't look at anything.\n");
        return 0;
    }
    dark = me->check_dark((int)here->query_light());

    if (!arg || !stringp(arg) || arg == "")
    {
        if (me->query_creator())
            TO->do_efun_write(file_name(here)+"\n");

        if(!dark)
        {
            ret = (string)here->query_contents();

            if ( function_exists("query_short_exit_string", here) )
            {
                // only rooms have this function {Laggard}
                exits = here->query_short_exit_string();
            }
        }
        if ( !exits )
        {
            exits = "";
        }
        TO->do_efun_write((string)here->short(dark) + exits + ".\n" + ret);
        return 1;
    }

    if (!sscanf(arg, "at %s", arg))
    {
        notify_fail("Glance at something!\n");
        return 0;
    }

    ob = find_match(arg, ({ me, here }) );

    if (sizeof(ob))
    {
        for (i=0;i<sizeof(ob);i++)
        {
            write(ob[i]->short(dark)+".\n");
        }
        return 1;
    }

    notify_fail("You do not think that the "+arg+" is here.\n");
    return 0;
}


int x_look(string arg)
{
    object me = this_object();
    object here = environment(me);
    object *ob;
    int i, dark;
    string ret;

    if (!here)
    {
        notify_fail("You are in limbo...."
            +" Sorry, you can't look at anything.\n");
        return 0;
    }
    dark = me->check_dark((int)here->query_light());

    if (!arg || !stringp(arg) || arg == "")
    {
        if (me->query_creator())
            TO->do_efun_write(file_name(here)+"\n");
/*
        tell_object(me,
            (string)me->fix_string(this_object()->query_cols(),
            (int)me->query_creator(),here->long(0, dark)));
*/
        TO->do_efun_write(here->long(0,dark));
        me->adjust_time_left(-LOOK_TIME);
        return 1;
    }

    sscanf(arg, "at %s", arg);

    ob = find_match(arg, ({ me, here }) );
    ret = "";
    me->adjust_time_left(-LOOK_TIME);

    if (sizeof(ob))  // should be same as glance above?
    {
        if (pointerp(ob))
        {
            for (i=0;i<sizeof(ob);i++)
            {
                ret += ob[i]->long(arg, dark);
                me->adjust_time_left(-EXAMINE_ITEM_TIME);
            }
        }
        else
        {
            ret += ob->long(arg, dark);
            me->adjust_time_left(-EXAMINE_ITEM_TIME);
        }
        more_string(ret, "Look");
        return 1;
    }

    notify_fail("You do not think that the "+arg+" is here.\n");
    return 0;
}



int x_examine(string arg)
{
    return x_look("at "+arg);
}


int show_view()
{
    return long_view ? x_look("") : x_glance("");
}

