// Pray command.  Coded by Timion.
// Updated by Timion 12 May 97
 
object me;
int x;
 

 
int check_pray(object me, string str)
{
  string god;
  int num;
 
  if(me->query_time_remaining("nopray"))
  {
    tell_object(me,"You are still cursed and may not pray.\n");
    return 0;
  }

  god=me->query_deity();
    if(!(god) || god=="none" || god == "None")
	{
	tell_object(me,"You call out to noone, and noone answers.\n");
	return 0;
	}
  switch( lower_case(str) )
  {
    case "healing":
      if(god=="ducky")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Healing.\n");
        return 0;
      }
      break;

    case "money":
      if(god=="taniwha")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Money.\n");
        return 0;
      }
      break;

    case "power":
      if(god=="timion")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Power.\n");
        return 0;
      }
      break;

    case "experience":
	if(god=="virga" || god=="raisa")
//    if(1)
      {
        tell_object(me,"Your Diety refuses to hear a prayer for "
          "Experience.\n");
        return 0;
      }
      break;

    case "bless":
    case "blessing":
	if(god=="bivins" || god=="grimbrand" || god=="radix")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Blessing.\n");
        return 0;
      }
      break;

    case "strength":
      if(god=="hokemj")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Strength.\n");
        return 0;
      }
      break;

    case "wisdom":
      if(god=="baldrick")
      {
        tell_object(me,"Your Diety refuses to hear a prayer for Wisdom.\n");
        return 0;
      }
      break;

  }
 
if(god=="timion"||god=="hokemj"||god=="taniwha"||god=="virga"||god=="raisa")
  num=300+(me->query_time_remaining("prayed"));
else
  num=500+(me->query_time_remaining("prayed"));
  if( (num>=5000) && (num<=8000) )
  {
    tell_object(me,capitalize(god)+" tells you: Desist in annoying me "
      "or face my wrath!\n");
    me->add_timed_property("prayed",num, num);
    return 0;
  }
 
  if (num>=8001)
  {
    tell_object(me,capitalize(god)+" tells you: I have had it with your "
      "incessant whining.  Bother me no more, you are cursed in my eyes.\n");
    me->set_hp(1);
    me->adjust_tmp_con(-1);
    me->adjust_tmp_str(-1);
    me->adjust_tmp_wis(-1);
    me->adjust_tmp_int(-1);
    me->adjust_tmp_dex(-1);
    me->adjust_tmp_cha(-2);
    me->add_timed_property("nopray",num,num);
    return 0;
  }

  if(random(num)<=75)
  {
    tell_object(me,"Your prayers are heard!\n");
    me->add_timed_property("prayed",num+500,num+500);
    return 1;
  }
  else
  {
    tell_object(me,"Your prayers go unanswered.\n");
    me->add_timed_property("prayed",num, num);
    return 0;
  }

  return 0;
}
 
 
int pray(string str,object who)
{
  object me = ( who ? who : this_player() );
 
  if ( sizeof(me->query_attacker_list()) )
  {
    tell_object(me, "You can't show proper respect in the middle of a "
      "fight!\n");
    return 1;
  }

  switch( lower_case(str) )
  {
    case "healing":
      if(check_pray(me,str))
      {
        x = 1+random(5) * (int)me->query_level();
        tell_object(me, "You are healed for "+x+" hit points!\n");
        me->adjust_hp(x,me);
      }
      return 1;

    case "money":
      if(check_pray(me,str))
      {
        x = 1+random(3) * (int)me->query_level();
        tell_object(me, "You are given "+x+" platinum coins!\n");
        me->adjust_money(x,"platinum");
      }
      return 1;
    case "power":
      if(check_pray(me,str))
      {
        x = 1+random(5) * (int)me->query_level();
        tell_object(me, "You are energized for "+x+" guild points!\n");
        me->adjust_gp(x);
      }
      return 1;
    case "experience":
      if(check_pray(me,str))
      {
        x = 100+random(1000) * (int)me->query_level();
        tell_object(me, "You are granted "+x+" experience points!\n");
        me->adjust_xp(x);
      }
      return 1;
    case "bless":
    case "blessing":
      if(check_pray(me,str))
      {
        x=random(5)+1;
        tell_object(me, "You have been blessed!\n");
        me->adjust_tmp_cha(x);
      }
      return 1;
    case "strength":
      if(check_pray(me,str))
      {
        x=random(5)+1;
        tell_object(me, "Divine strength flows through your veins!\n");
        me->adjust_tmp_str(x);
      }
      return 1;
    case "wisdom":
      if(check_pray(me,str))
      {
        x=random(2)+1;
        tell_object(me, "You are granted wisdom beyond your years.\n");
        me->adjust_tmp_wis(x);
        me->adjust_tmp_int(x);
      }
      return 1;
    default:
      tell_object(me, "Pray for what?\nAvailable options: "
        "Healing, Money, Power, Experience, Blessing, Strength, Wisdom."
        "\nSyntax: pray money\n");
      return 1;
  }
}
 
