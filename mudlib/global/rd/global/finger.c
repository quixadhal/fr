string password, email;
static string tmp_password, tmp;
string real_name, birth_day, desc, where;
// Added Guildwho, Dyraen - Dec '94
// modified who for immort invisibility - Kelaronus 1/26/95

void finger_commands() {
  add_action("chfn", "chfn");
  add_action("set_email","email");
  add_action("describe","describe");
  add_action("change_password","password");
  add_action("change_password","passwd");
} /* finger_commands() */

nomask int set_email(string str) {
    if (!str) {
      write("You current email address is "+email+"\n");
      write("To clear use \"email CLEAR\"\n");
      write("For the email address to be only visible by lords prepend a :\n");
      write("eg email :frog@frogcentral.froguni.swamp\n");
      return 1;
    }
    if (str == "CLEAR")
      email = "";
    else
      email = str;
    if (email != "")
      write("Email address set to "+str+".\n");
    else
      write("Email address is null.\n");
    return 1;
} /* set_email() */

void set_desc(string str) { desc = str; }
string query_desc() { return desc; }


/* describe recoded by the Forgers 7/28/94 */
int describe(string arg){
    tmp = "";
    if (!arg){
        if (desc){
            message("Usage : describe edit\n        describe clear\n","",
                     this_player());
            message( desc, "Description: ", this_player());
          }
        else {
            message("Usage : describe edit\n        describe clear\n","",
                     this_player());
            message("No description set.\n", "", this_player());
         }
    } else if (arg == "clear")
        desc = 0;
    else {
        message("Enter your description, quit and save with a ** on a "+
            "line by itself or abort with a ~q. Remember to add a space "+
         "between words, even after pressing return.\n", "", this_player());
        write("] ");
        input_to("do_desc");
    }
    return 1;
}

void do_desc(string arg){
    if(arg == "**"){
        desc = tmp;
        message(desc, "Description set to: ", this_player());
    } else if(arg == "~q"){
        message("Aborted, description not changed.\n", "", this_player());
    } else {
        tmp += arg;
        if(strlen(tmp) < 480){
            write("] ");
            input_to("do_desc");
        } else {
            if(strlen(tmp) > 480)
                tmp = tmp[0 .. 480];
            do_desc("**");
        }
    }
}

void set_password(string pass) {
  int i;
  if (sscanf(file_name(previous_object()), "/secure/login#%d", i))
    password = pass;
} /* set_password() */

int change_password2(mixed pass);

static int change_password() {
  if (password) {
    write("Please enter your old password : ");
    input_to("change_password2",1);
    return 1;
  }
  change_password2(0);
  return 1;
} /* change_password() */

static int change_password2(mixed pass) {
  string str;
  if (password) {
    str = crypt(pass,password);
    if (str != password) {
      write("\nIncorrect.\n");
      return 1;
    }
  }
  write("\nEnter new Password : ");
  input_to("change_password3",1);
  return 1;
} /* change_password2() */

static string tmppassword;

static int change_password3(string pass) {
  tmppassword = pass;
  write("\nPlease enter again : ");
  input_to("change_password4",1);
  return 1;
} /* change_password3() */

static int change_password4(string pass) {
  if (tmppassword != pass) {
    write("\nIncorrect.\n");
    return 1;
  }
  password = crypt(pass,password);
  write("\nOk.\n");
  return 1;
} /* change_password4() */

string query_birthday();

int chfn() {
  write("Change finger information.\n");
  write("Pressing return at the prompts will take the default.  The default "+
        "is the option in []'s.\n");
  write("What real name do you wish to use ["+real_name+"] ? ");
  input_to("real_name");
  return 1;
} /* chfn() */

int real_name(string str) {
  if (str && str != "")
    if (str == "none")
      real_name = 0;
    else
      real_name = str;
  if (real_name && real_name != "")
    write("Ok real name set to "+real_name+".\n");
  else
    write("Real name cleared.\n");
  write(
"Enter your location (ie Perth, oz, whatever) ["+where+"]\n"+
"(none for none) : ");
  input_to("get_where");
  return 1;
} /* real_name() */

int get_where(string str) {
  if (str && str != "")
    if (str == "none")
      where = 0;
    else
      where = str;
  if (where && where != "")
    write("Ok location set to "+where+".\n");
  else
    write("Real name cleared.\n");
  write("Enter your birthday (ddmm) ["+query_birthday()+
        "] (none for none) : ");
  input_to("birthday");
  return 1;
} /* get_where() */

string convert_birthday(string str) {
  /* we assume it is 4 characters long */

  int day, month, tot;
  string retval;

  sscanf(str, "%d", tot);
  day = tot / 100;
  month = tot % 100;
  switch(day) {
    case 11:
      retval = "11th"; break;
    case 12:
      retval = "12th"; break;
    case 13:
      retval = "13th"; break;
    default:
      switch(day%10) {
        case 1:
          retval = day+"st"; break;
        case 2:
          retval = day+"nd"; break;
        case 3:
          retval = day+"rd"; break;
        default:
          retval = day+"th";
      }
  }
  retval += " of ";
  switch(month) {
    case 1:
      return retval + "January";
    case 2:
      return retval + "February";
    case 3:
      return retval + "March";
    case 4:
      return retval + "April";
    case 5:
      return retval + "May";
    case 6:
      return retval + "June";
    case 7:
      return retval + "July";
    case 8:
      return retval + "August";
    case 9:
      return retval + "September";
    case 10:
      return retval + "October";
    case 11:
      return retval + "November";
    case 12:
      return retval + "December";
  }
  return retval;
} /* convert_birthday() */

int valid_birthday(string str) {
#define LENGTHS ({ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 })

  int tot, month, day;

  if(strlen(str) != 4) {
    return 0;
  }
  if(!sscanf(str, "%d", tot)) {
    return 0;
  }
  month = tot % 100;
  day = tot / 100;
  if(month > 12 || month < 1) {
    return 0;
  }
  if(day < 1) {
    return 0;
  }
  return day <= LENGTHS[month];
} /* valid_birthday() */

string query_birthday() {
  if(birth_day) {
    return birth_day;
  }
  return "Unknown";
} /* query_birthday() */

int set_birthday(string str)
{ /* added so wizzes can set player's birthdays if they foul up */
  if(valid_birthday(str)) {
     birth_day = convert_birthday(str);
     this_object()->save_me();
     return 1;
  }
  return 0;
} /* set_birthday() */

void birthday(string str) {
  if (str == "") {
    if (birth_day)
      write("Birthday unchanged from "+query_birthday()+".\n");
    else
      write("Birthday left as blank.\n");
  } else {
    if(query_birthday() != "Unknown") {
      write("You can't change when you were born! Please ask a Creator or " +
        "a Lord to change it if you made an error.\n");
    } else if(!valid_birthday(str)) {
        write("Invalid Birthday.  Birthday cleared.\n");
        birth_day = 0;
    } else {
      birth_day = convert_birthday(str);
      write("Birthday set to " + query_birthday() + ".\n");
      this_object()->birthday_gifts();
    }
  }
  this_object()->save_me();
  write("What email address do you wish to use.  Set to none to clear.\n");
  write("Putting a : in front of it means that only the creators and lords "+
        "can read it.\n");
  write("["+email+"] : ");
  input_to("get_email");
} /* birthday() */

void get_email(string str) {
  if (str == "")
    if (!email || email == "")
      write("Email address left blank.\n");
    else
      write("Email address left as "+email+".\n");
  else if (str == "none") {
    email = 0;
    write("Email address cleared.\n");
  } else {
    email = str;
    write("Email address set to "+email+".\n");
  }
  this_object()->save_me();
} /* get_email() */

int query_is_birthday_today() {
    string cmonth, dummy, bmonth;
    int cdate, bdate;

    if(sscanf(ctime(time()), "%s %s %d %s", dummy, cmonth, cdate, dummy)!=4)
        return 0; /* error in date */
    if(sscanf(query_birthday(), "%d%s of %s", bdate, dummy, bmonth) !=3)
        return 0; /* no bday set */
    if(cmonth == bmonth[0..2] && cdate == bdate)
        return 1;
} /* query_is_birthday_today() */

string query_real_name() { return real_name; }
string query_where() { return where; }
