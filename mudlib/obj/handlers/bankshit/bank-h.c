/* Bank handler. 
 * "Made" by Baldrick because of the need to add some neat wombles..
 * Gonna add the posibility to have different accounts on different banks.
 * I have to make set_percentage a mapping too. !!!!
 * Hmm, have to make a check if the bank is new, and create a mapping for it.
 * March '94
 */

#define SAVE_FILE "/save/bank.o"
#include "money.h"

mapping accounts;
int total_made;
static int total_account;

int account_cost,
    percentage;

void load_it();
void save_it();

void create() 
  {
  int i;
  //sscanf(file_name(this_object()), "%s#%d", SAVE_FILE, i);
  accounts = ([ ]);
  account_cost = 0;
  percentage = 90;
  // ::create();
  load_it();
}

int create_bank(string banker)
  {
  accounts  += ([banker : (["dummy": 1]) ]);
  save_it();
  return 1;
} /* create bank... */

int handle_balance(string banker) 
  {
  if (member_array(banker, m_indices(accounts)) == -1)
    {
    write ("BooHisss, someone has FooBared, tell a God.\n");
    return 0;
    }
  if (member_array(this_player()->query_name(), 
      m_indices(accounts[banker])) == -1) 
    {
    notify_fail("You do not have an account here.\n");
    return 0;
    }
  if (!accounts[banker][this_player()->query_name()]) 
    {
    write("Your account is empty.\n");
    return 1;
    }
  write("You have "+MONEY_HAND->money_value_string(
        accounts[banker][this_player()->query_name()])+" in your account.\n");
  return 1;
}

int handle_withdraw(string str, string banker) 
  {
  int amt, i, val;
  string s1, type;
  mixed *values;

  if (member_array(this_player()->query_name(), 
      m_indices(accounts[banker])) == -1) 
    {
    notify_fail("You do not have an account here.\n");
    return 0;
    }
  notify_fail("Syntax: "+query_verb()+" <amount> <type> coin[s]\n");
  if (!str)
    return 0;
  if (sscanf(str, "%d %s coin%s", amt, type, s1) != 3 &&
      sscanf(str, "%d %s", amt, type) != 2)
    return 0;
  if (amt <= 0) 
    {
    notify_fail("You must withdraw something.\n");
    return 0;
    }
  values = (mixed *)MONEY_HAND->query_values();
  if ((i=member_array(type, values)) == -1) 
    {
    notify_fail("I do not know of any "+type+" coins.\n");
    return 0;
    }
  val = amt*values[i+1];
  if (val > accounts[banker][this_player()->query_name()]) 
    {
    write("You do not have enough money in your account.\n");
    return 1;
    }
  this_player()->adjust_money(amt, type);
  accounts[banker][this_player()->query_name()] -= val;
  total_account -= val;
  save_it();
  write("You withdraw "+amt+" "+type+" coins.\n");
  say(this_player()->query_cap_name()+" withdraws some money from "+
      this_player()->query_possessive()+" account.\n");
  return 1;
}

int handle_deposit(string str, string banker) 
  {
  object *obs, cont;
  int i, total_amt, amt;

  if (member_array(this_player()->query_name(), 
      m_indices(accounts[banker])) == -1) 
    {
    notify_fail("You do not have an account here.\n");
    return 0;
    }
  if (!str) 
    {
    notify_fail("Syntax: "+query_verb()+" <money>\n");
    return 0;
  }
  cont = clone_object("/std/container");
  obs = find_match(str, this_player());
  for (i=0;i<sizeof(obs);i++)
    if (obs[i]->query_property("money"))
      obs[i]->move(cont);
  if (!sizeof(all_inventory(cont))) {
    cont->dest_me();
    notify_fail("You might want to deposit some money.\n");
    return 0;
  }
  obs = all_inventory(cont);
  for (i=0;i<sizeof(obs);i++)
    total_amt += (int)obs[i]->query_value();
  if (!total_amt) {
    notify_fail("Your money is not worth anything.\n");
    return 0;
  }
  amt = total_amt*percentage/100;
  accounts[banker][this_player()->query_name()] += amt;
  total_account += amt;
  total_made += total_amt - amt;
  save_it();
  write(capitalize((string)MONEY_HAND->money_value_string(total_amt))+
        " deposited to give a total account of "+
        MONEY_HAND->money_value_string(accounts[this_player()->query_name()])+
        ".\n");
  say(this_player()->query_cap_name()+" deposits some money into "+
      this_player()->query_possessive()+" account.\n");
  return 1;
}

int handle_create_account(string banker) 
  {
  if (!accounts)
    return (notify_fail("booHiss.\n"));

  if (member_array(this_player()->query_name(), 
      m_indices(accounts[banker])) != -1) {
    notify_fail("You already have an account here.\n");
    return 0;
  }
  if (account_cost) 
    {
    if (this_player()->query_value() < account_cost) 
      {
      write("You do not have enough money to open an account.\n");
      return 1;
      }
    write("It will cost you "+MONEY_HAND->money_value_string(account_cost)+
          " to open the account.\nDo you still want to ? ");
    input_to("check_open");
    return 1;
    }
  accounts[banker][this_player()->query_name()] = 0;
  write("Account created.\n");
  save_it();
  return 1;
}

int handle_check_open(string str, string banker) 
  {
  str = lower_case(str);
  if (str[0] != 'y' && str[0] != 'n') {
    write("I don't understand.  Do you want to open an account ? ");
    input_to("check_open");
    return 1;
  }
  if (str[0] == 'n') {
    write("Ok, not opening the account.\n");
    return 1;
  }
  accounts[banker][this_player()->query_name()] = 0;
  write("Account created.\n");
  save_it();
  total_made += account_cost;
  this_player()->pay_money((mixed *)MONEY_HAND->create_money_array(account_cost));
  return 1;
}

/* This deletes all the accounts a player has.
 * Baldrick.
 */
int refresh_account(string name)
  {
  write ("Bing, "+ name + "\n");
  if(member_array(name,m_indices(accounts)) == -1)
    return 0;
  accounts = m_delete(accounts, name);  
  save_it();
  return 1;
  }

int handle_close_account(string banker) 
  {
  int amt;

  if (member_array(this_player()->query_name(), m_indices(accounts)) == -1) {
    notify_fail("You do not have an account here, so how can you close it?\n");
    return 0;
  }
  if ((amt = accounts[this_player()->query_name()])) {
    write("You get "+MONEY_HAND->money_value_string(amt)+" when you close "+
          "the account.\n");
    this_player()->adjust_money(MONEY_HAND->create_money_array(amt));
    total_account -= amt;
  } else {
    write("You close your account.\n");
  }
  say(this_player()->query_cap_name()+" closes " +
    this_player()->query_possessive() + " account.\n");
  accounts = m_delete(accounts, this_player()->query_name());
  save_it();
  return 1;
}

void load_it() 
  {
  restore_object(SAVE_FILE,1);

  if (!total_account) 
    {
    string *str;
    int i;
  if (accounts)
    str = keys(accounts);
   else
    str =({ });
    //for (i=0;i<sizeof(str);i++)
     // total_account += accounts[str[i]];
    }
}

void save_it() 
  {
  save_object(SAVE_FILE,1);
}

/* These can't be used right now.. have to map these too!
 * Baldrick.
 */
void set_percentage(int per) { percentage = per; }
int query_percentage() { return percentage; }

void set_account_cost(int i) { account_cost = i; }
int query_account_cost() { return account_cost; }

mixed *stats() {
  return ({ ({ "Percentage", percentage }),
            ({ "Account cost", account_cost }),
            ({ "Total made", total_made }),
            ({ "Total account", total_account }) });
}
