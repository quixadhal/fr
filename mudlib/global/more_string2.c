static int fsize,
    topl,
    botl;
static string last_search="", *the_bit, finish_func, more_bit, stat_line;
static object finish_ob;
static int search_dir;

#define ROWS 22
#define HELP_FILE "/doc/helpdir/more"

void string_display_file() {
  int i;

  botl = topl + ROWS;
  for (i=topl;i<botl && i<fsize;i++)
    write(the_bit[i]+"\n");
}

void more_string_status_line() {
  string *frog;
  string s;
  int i, j,percentage;

  if (!stat_line)
    stat_line = "$N From $T to $B of $S ($%%) -- h for help. ";
  s = "";
  frog = explode(stat_line, "$");
  for (i=0;i<sizeof(frog);i++) {
    if (frog[i] == "") {
      s += "$";
      i ++;
    } else switch (frog[i][0]) {
      case 'N' :
          s += more_bit+frog[i][1..1000];
          break;
      case 'T' :
          s += topl+frog[i][1..1000];
          break;
      case 'B' :
          s += botl+frog[i][1..100];
          break;
      case '%' : {
          percentage = (botl*100)/fsize;
          if(percentage > 100) percentage = 100;
          s += percentage+frog[i][1..100];
          break;
      }
      case 'S' :
         s += fsize+frog[i][1..1000];
         break;
    }
  }
  write(s);
  return;
}

void string_next_page(string str) {
  int num,
      noargs,
      i,j,k,
      redraw;
  string s1, s2, *s3, s4, s5;

  if (!str)
    str = "";

  if (sscanf(str,"%d%s", num, str)!=2)
    noargs = 1;
  s1 = extract(str,1);
  str = extract(str,0,1);
/* case statements WEEEEEE */
  switch(str) {
  case "h" :
    cat(HELP_FILE);
    break;
  case "q" :
    if (finish_func)
      call_other(finish_ob, finish_func);
    return;
  case "" :
  case "f" :
/* go on a number of pages... */
    if (noargs)
      num = 1;
    topl += num*(ROWS);
    redraw = 1;
   break;
 case "u" :
   redraw = 1;
   if (noargs)
     num = ROWS/2;
   topl -= num;
   if (topl < 0)
     topl = 0;
   break;
 case "d" :
   redraw = 1;
   if (noargs)
     num = ROWS/2;
   topl += num;
   if (topl > fsize)
     topl = fsize - 2;
   break;
 case "/" :
/* sigh */
    i = topl+4;
    search_dir = 0;
    if (s1=="")
      s1 = last_search;
    if (!s1)
      s1 = "";
    if (s1[0] == '!') {
      s1 = s1[1..10000];
      for (i=topl+4;i<fsize;i++)
        if (sscanf(the_bit[k],"%s"+s1+"%s",s4,s5)!=2)
          if (num--<=0)
            break;
    } else
      for (i=topl+4;i<fsize;i++)
        if (sscanf(the_bit[k],"%s"+s1+"%s",s4,s5)==2)
          if (num--<=0)
            break;
    if (i==fsize)
      write("Sorry "+s1+" not found.\n");
    else
      topl = i-3;
    redraw = 1;
    break;
  case "?" :
    if (s1=="")
      s1 = last_search;
    if (!s1)
      s1 = "";
    search_dir = 0;
    if (s1[0] == '!') {
      s1 = s1[1..10000];
      for (i=topl+2;i>0;i--)
        if (sscanf(the_bit[k],"%s"+s1+"%s",s4,s5)!=2)
          if (num--<=0)
            break;
    } else
      for (i=topl+2;i>0;i--)
        if (sscanf(the_bit[k],"%s"+s1+"%s",s4,s5)==2)
          if (num--<=0)
            break;
    if (i==fsize)
      write("Sorry "+s1+" not found.\n");
    else
      topl = i-3;
    redraw = 1;
    break;
  case "N" :
    search_dir = !search_dir;
  case "n" :
    if (search_dir)
      return string_next_page(num+"?");
    return string_next_page(num+"/");
    break;
  case "b" :
    if (noargs)
      num = 1;
    if (topl>0) {
      topl -= num*(ROWS);
      redraw = 1;
      if (topl<0)
        topl = 0;
    }
    redraw = 1;
    break;
  case "g" :
    topl = num;
    if (topl>=fsize)
      topl = fsize-2;
    redraw = 1;
    break;
  case "G" :
    redraw = 1;
    if (noargs)
      topl = fsize - ROWS;
    else
      topl = num;
    if (topl>fsize)
      topl = fsize-2;
    break;
  case "p" :
  case "%" :
    redraw = 1;
    topl = fsize*num/100;
    break;
  case "P" :
    if (noargs)
      topl = fsize - ROWS;
    else
      topl = fsize*num/100;
    if (topl>fsize)
      topl = fsize - 2;
    redraw = 1;
    break;
  }
  if (redraw)
    string_display_file();
  if (topl<fsize) {
    more_string_status_line();
    input_to("string_next_page");
  } else
    if (finish_func)
      call_other(finish_ob, finish_func);
}

varargs int more_string(mixed str, string bity) {

  if (bity)
    more_bit = bity;
  else
    more_bit = "--- MORE";
  last_search = "";
 
  if (!pointerp(str)) 
    the_bit = explode(str,"\n");
  fsize = sizeof(the_bit);
  if (fsize == 0) {
    notify_fail("Empty String.\n");
    return 0;
  }
  topl = 0;
  if (fsize < ROWS)
    botl = fsize;
  else
    botl = ROWS;
  string_display_file();
  if (fsize >= ROWS) {
    more_string_status_line();
    input_to("string_next_page");
  } else if (finish_func) {
    call_other(finish_ob, finish_func);
  }
  return 1;
}

int set_finish_func(string str, object ob) {
  finish_func = str;
  if (!ob)
    finish_ob = previous_object();
  else
    finish_ob = ob;
}
