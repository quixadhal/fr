#define MIN_LVL 10
#define SP_COST 50

inherit "obj/monster";

mixed spell(string str, int skill, int cast);

int cast_spell(string str)
{
  int skill;
  mixed ret;

  str = (string)this_player()->expand_nickname(str);
  if (str==(string)this_player()->query_name())
   skill=(int)this_player()->query_skill_bonus("faith.spells.offensive");
  else
   skill=(int)this_player()->query_skill_bonus("faith.spells.offensive.target");
  if (skill<MIN_LVL)
  {
    notify_fail("You are not skillful enough.\n");
    return 0;
  }
  ret = spell(str, skill, 1);
  if (stringp(ret))
  {
    notify_fail(ret);
    return 0;
  }
  write("You start to cast Spiritual Hammmer (remember to wield hands).\n");
  say(this_player()->query_cap_name()+" starts to make magical gestures and "+
   this_player()->query_possessive()+" hands gets a shimmering hue.\n");
  return 1;
  }

mixed spell(string str, int skill, int cast)
{
  mixed ob;

  if ((int)this_player()->query_spell_effect("offensive"))
    return "You are already casting an offensive spell.\n";
  ob = find_match(str, environment(this_player()));
  if (sizeof(ob))
    ob = ob[0];
  else
    ob = 0;

  this_player()->add_spell_effect(1, "offensive", "Spiritual Hammer",
    this_object(), "hb_spell", ({ skill,ob,cast }));
  return 1;
}

int hb_spell(object attacker, mixed *params)
{
  int hp;
  mixed att;

  if (!params[1])
  {
    tell_object(previous_object(),
      "Your spell failed ... there is no one of that name here.\n");
    return 0;
  }
  if (params[2] && (int)previous_object()->adjust_gp(-SP_COST)<0)
  {
    tell_object(previous_object(), "Too low on power.\n");
    return 0;
  }
  say((string)previous_object()->query_cap_name() +
    " casts a spell on " + (string)params[1]->query_cap_name() +
    ", and a mighty hammer appears before "+(string)params[1]->query_objective()
    +".\n", params[1]);
  if(params[1] == previous_object())
    tell_object(params[1], "You cast Spiritual Hammer on yourself.\n");
  else
  {
   tell_object(params[1], (string)previous_object()->query_cap_name() +
    " casts a spell on you and a hammerlike substance pops up before you.\n");
   tell_object(previous_object(), "You cast Spiritual Hammer on " +
    (string)params[1]->query_cap_name() + ".\n");
  }

  if(params[1]->query_attack("blade"))
  {
    params[1]->remove_attack("blade");
    if(params[1] != previous_object())
    {
      say((string)previous_object()->query_cap_name()+"'s Spiritual Hammer "+
        "negates "+(string)params[1]->query_cap_name()+
        "'s Flame Blade.\n");
      write("Your Hammer destroys "+(string)params[1]->query_cap_name()+
          "'s Flame Blade.\n");
      return 0;
    }
    say((string)previous_object()->query_cap_name()+"'s Spiritual Hammer "+
        "negates "+(string)params[1]->query_possessive()+" Flame Blade.\n");
    write("Your Hammer destroys your Flame Blade.\n");
    return 0;  
  }

  params[1]->add_attack("hammer", 0, 100, 100+params[0]/5, 0, 0, "blunt");
  call_out("wear_off", 200+params[0], params[1]);
  return 50;
}

void wear_off(object target)
{
 if(target)
 {
  target->remove_attack("hammer");
  tell_object(target, "The Spiritual Hammer disappears.\n");
  tell_room(environment(target),(string)target->query_cap_name()+
   "'s mighty hammer disappears.\n", ({target}));
 }
}
