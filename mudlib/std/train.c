int train(string str) {
  string skill_name, sk, g_o;
  string *bits;
  int cost, i, lvl, tmp, to, by, max_lvl, total_xp, total_cost, p_val;

  if ((g_o=(string)this_player()->query_guild_ob()) != our_guild && g_o) {
    notify_fail("You cannot advance here! Go to your own guild.\n");
    return 0;
  }
  if (!str) {
    notify_fail(sprintf("Syntax: %-*#s\n", this_player()->query_cols(),
        "advance <skill>\nadvance <skill> to <level>\n" +
        "advance <skill> by <level>\n"));
    return 0;
  }
  if ((sscanf(str, "%s to %d", sk, to) != 2) &&
      (sscanf(str, "%s by %d", sk, by) != 2)) {
    sk = str;
    by = 1;
  }
  bits = explode(implode(explode(sk, " "), "."), ".");
  if (!(skill_name = (string)SKILL_OB->query_skill(bits))) {
    notify_fail("I am sorry but the skill " + sk + " does not exist.\n");
    return 0;
  }
  lvl = (int)this_player()->query_skill(skill_name);
  if(!by && to) by = to - lvl;
  if(by <= 0) {
    if(by == 0) notify_fail("You are already at level " + lvl + " at " +
        skill_name + ".\n");
    else notify_fail("You cannot regress below your current skill level!\n");
    return 0;
  }
  if ((sizeof(explode(skill_name, "."))-1)*5 > lvl) {
    notify_fail("Not a high enough level in the outer skills to advance "+
                "that yet.\n");
    return 0;
  }
  if (!g_o)
    max_lvl = 5;
  else
    max_lvl = (int)our_guild->query_max_skill_level(skill_name);
  if (lvl >= max_lvl) {
    notify_fail("You cannot advance in that skill any further here.\n");
    return 0;
  }
  if (!g_o)
    cost = DEFAULT_COST; /* The guild trains cheaper.  Better thingys */
  else
    cost = (int)our_guild->query_skill_cost(skill_name);
  cost *= (int)SKILL_OB->query_skill_cost(skill_name);
  cost *= STD_COST/5;
  p_val = (int)this_player()->query_value();
  for (i=0;i<by;i++) {
    tmp = cost * ( ((lvl + i)/LEVEL_DIV) + 1);
    if(this_player()->query_xp() < tmp+total_xp) {
      if(!i) {
        notify_fail("Your lack of experience prevents you improving " +
          sk + ".\n");
        return 0;
      } else {
        write("Your lack of experience prevents you taking all the " +
        "advancement you requested.\n");
      }
      break;
    }
    if (lvl + i >= max_lvl) {
      write("Your guild hasn't the resources to train you as far as "+
            "you requested.\n");
      break;
    }
    if (((tmp/COST_DIV)+total_cost) > p_val) {
      if(!i) {
        notify_fail("Due to your sad lack of money the guild cannot train "+
                    "you in "+sk+", it would have cost you "+
                    MONEY_HAND->money_value_string(tmp/COST_DIV)+".\n");
        return 0;
      } else {
        write("Due to your sad lack of money the guild cannot train "+
             "you in "+sk+" to "+(i+lvl)+", it would have cost you "+
             MONEY_HAND->money_value_string(tmp/COST_DIV)+".\n");
      }
      break;
    }
    total_xp += tmp;
    total_cost += tmp/COST_DIV;
  }
  this_player()->adjust_xp(-total_xp);
  this_player()->pay_money(MONEY_HAND->create_money_array(total_cost));
  this_player()->add_skill_level(skill_name, i);
  this_player()->reset_all();
  event(this_object(), "guild_advance", bits, lvl, lvl+i);
  check_spells_commands(bits, lvl+i);
  write("You advance your skill in " + sk + " from " + lvl + " to " +
        (lvl + i) + " for " + total_xp + " xp and " +
        MONEY_HAND->money_value_string(total_cost) + ".\n");
  say(this_player()->query_cap_name()+" advances "+
      this_player()->query_possessive()+" skills.\n");
this_player()->reset_all();
this_player()->reset_hp();
  return 1;
} /* train()  */
