#define SKILL "dex.thief.pickpocket"
#define COST 20
#define MIN_LEV 10

/*
  Steal - fun fun fun
    thinking about modifying chance on size of object...  :)
*/

void fail(object who);


int steal(string str) {
  object me,*vat,*hoo;
  int bon,tlev,diff;
  string what, who;
  mixed thwap;

  me=this_player();
  notify_fail("Usage: steal <object> from <person/monster>\n");

  if (!str)
    return 0;
  if (sscanf(str,"%s from %s",what,who)!=2)
    return 0;

  hoo=find_match(who,environment(me));

  if (!sizeof(hoo)) {
    notify_fail("I don't see a "+who+" in here.\n");
    return 0;
  }

  vat=find_match(what,hoo[0]);
  if (!sizeof(vat)) {
    notify_fail("Hmmm, Kemosabe.  Me no find "+what+" on "+capitalize(who)+".\n");
    return 0;
  }

  if (hoo[0]->query_creator()) {   /* are we currently in a creator char :) */
    write("You wouldn't want to steal anything from a coder, would you?\n");
    return 1;
  }
  bon=(int)me->query_skill(SKILL);

  if ((int)me->query_gp()< COST) {
    notify_fail("You seem to be too worn out to do that.\n");
    return 0;
  }
  me->adjust_gp(-COST);

  tlev=(int)hoo[0]->query_level();  /* this may be a bit cheesy due to diffs */
                                      /* in guilds levels....sigh              */

  diff=bon-tlev;

  if ((diff<0)&&random(100)>2) {
    fail(hoo[0]);
    return 1;
  }
  if (random(100)<3) {   /* can't win all the time :) */
    fail(hoo[0]);
    return 1;
  }

  if (random(100)>(diff*10-(random(10)-5))) {
    /* get 10% for every level you are above hoo[0] */
    fail(hoo[0]);
    return 1;
  }

 /* thock in some stuff here to check for wielded/worn stuff - automatic fail */

  if (((object)hoo[0]->query_weapon() == vat[0])||
      ((int)vat[0]->query_worn())) {
    fail(hoo[0]);
    return 1;
  }

  if ((string)vat[0]->query_name()!="coin") {
    write("Ok.\n");
    vat[0]->move(me);
    return 1;
  }

  diff=random(bon*100)+2;
  if (diff>(int)hoo[0]->query_value())
    diff=(int)hoo[0]->query_value();

  thwap=(mixed)"/obj/handlers/money_handler"->create_money_array(diff);
  write("You snag "+(string)"/obj/handlers/money_handler"->money_string(thwap)+
        ".\n");

  hoo[0]->pay_money(thwap); /* this also smells of cheese - not only do we */
                            /* rob them, but we give them change - oh boy */

  me->adjust_money(thwap);
  return 1;
}


void fail(object who) {
  string bing,me;

  bing=(string)who->query_cap_name();
  me=(string)this_player()->query_cap_name();

  write("Oh bugger - "+bing+" seems to have noticed your activities.\n");
  tell_object(who,"You suddenly notice "+me+" groping around in your pockets.\n");
  tell_room(environment(this_player()),me+" suddenly has an embarrasing moment "+
            "in pocket picking.  "+bing+" doesn't look to happy.\n",
            ({who,this_player()}));

  if (!query_ip_name(who))
    who->attack_by(this_player());  /*  mean and nasty :) */
}
