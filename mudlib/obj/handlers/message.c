
int setmin(string str) {
 /* if(!this_player()->query_property("setm")) {
    notify_fail("You are not allowed that power yet.\n");
    return 0;
  }*/
  str = "@" + str + " ";
  if (sizeof(explode(str, "$N")) < 2 || sizeof(explode(str, "$F")) < 2) {
    notify_fail("Must have a $N and a $F in your message in.\n");
    return 0;
  }
  this_player()->setmin(str);
  write("Ok.\n");
  return 1;
}


int setmout(string str) {
 /* if(!this_player()->query_property("setm")) {
    notify_fail("You are not allowed that power yet.\n");
    return 0;
  }*/
  str = "@" + str + " ";
  if (sizeof(explode(str, "$N")) < 2 || sizeof(explode(str, "$T")) < 2) {
    notify_fail("Must have a $N and a $T in your message out.\n");
    return 0;
  }
  this_player()->setmout(str);
  write("Ok.\n");
  return 1;
}


int setmmin(string str) {
 /* if(!this_player()->query_property("setmm")) {
    notify_fail("You are not allowed that power yet.\n");
    return 0;
  }*/
  str = "@" + str + " ";
  if (sizeof(explode(str, "$N")) < 2) {
    notify_fail("Must have a $N in your teleport message in.\n");
    return 0;
  }
  this_player()->setmmin(str);
  write("Ok.\n");
  return 1;
}


int setmmout(string str) {
 /* if(!this_player()->query_property("setmm")) {
    notify_fail("You are not allowed that power yet.\n");
    return 0;
  }*/
  str = "@" + str + " ";
  if (sizeof(explode(str, "$N")) < 2) {
    notify_fail("Must have a $N in your teleport message out.\n");
    return 0;
  }
  this_player()->setmmout(str);
  write("Ok.\n");
  return 1;
}
