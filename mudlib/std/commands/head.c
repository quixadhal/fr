inherit "/std/item";

string MY_HEAD = "Unknown";
string query_hair_cut();

// useful'ish - Radix
int query_decapitated_head() { return 1; }

void setup()
   {set_name("head");
    set_short("Decapitated Head");
    set_main_plural("Decapitated Heads");
    set_weight(50);
    call_out("GET_MY_NAME", 5);
   }

void init()
   {::init();
    set_long("You have to hold back your breakfast as you look at this "
        "gruesome display of barbary.  Savagely hacked from the shoulders "
        "you wonder where the rest of "+query_hair_cut()+" is.\n\n");
    }

string query_hair_cut()
   {if(MY_HEAD == "Unknown")
       return "the body";
    return MY_HEAD;
   }

void set_head_name(string str)
   {MY_HEAD = str;
    this_object()->add_property("victim", str);
    this_object()->init();
   }

void GET_MY_NAME()
   {MY_HEAD = this_object()->query_property("victim");
    if(!MY_HEAD)
       MY_HEAD = "Unknown";
   }
