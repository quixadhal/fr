/** coded by Raskolnikov - July 1996 **/

inherit "/global/nickname.c";
void henchman_commands(string str)
{
    int num, i, j, order1, order2, order3, order4;
    string *command_list, henchname, com, dest;
    object henchman, *henchmen, *ob, *obs, owner;

    command_list = ({"protect", "unprotect", "follow", "unfollow",
      "equip", "wear", "unwear", "hold", "unhold", "drop", 
      "get", "attack", "stop" });
    order1 = sscanf(str, "%s %d %s %s", henchname, num, com, dest);
    if(order1 != 4) {
	order3 = sscanf(str, "%s %d %s", henchname, num, com);
	if(order3 != 3) {
	    order2 = sscanf(str, "%s %s %s", henchname, com, dest);
	}
    }
    if(order1 == 4 || order2 ==3) {
	henchname = expand_nickname(henchname);
	dest = expand_nickname(dest);
	com = expand_nickname(com);
	if(order1 == 4) {
	    henchman = present(henchname+" "+num, 
	      environment(this_player()));
	    if(!henchman) {
		notify_fail("There is no "+henchname+" with that number.\n");
		return 0;
	    }
	}
	if(order2 == 3) {
	    henchman = present(henchname, environment(this_player()));
	    if(!henchman) {
		notify_fail("There is no "+henchname+" here.\n");
		return 0;
	    }
	}
	if(this_player() != henchman->query_owner()) {
	    notify_fail("That is not your henchman!\n\n");
	    return 0;
	}
	if(member_array(com, command_list) == -1) {
	    notify_fail("You do not know the command "
	      ""+com+"\n");
	    return 0;
	}
	ob = find_match(dest, henchman);
	if(!sizeof(ob)) ob = find_match(dest, environment(this_player()));
	if(!sizeof(ob)) {
	    notify_fail(henchman->query_cap_name()+" cannot find "
	      ""+dest+".\n");
	    return 0;
	}
	switch(com) {
	case "wear":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    henchman->do_command("wear "+dest);
	    break;
	case "unwear":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    henchman->do_command("unwear "+dest);
	    break;
	case "hold":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    for(i=0;i<sizeof(ob);i++)
		henchman->do_command("hold "+ob[i]->query_name());
	    break;
	case "unhold":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    for(i=0;i<sizeof(ob);i++)
		henchman->do_command("unhold "+ob[i]->query_name());
	    break;
	case "drop":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    for(i=0;i<sizeof(ob);i++)
		henchman->do_command("drop "+ob[i]->query_name());
	    break;
	case "get":
	    tell_object(this_player(), henchman->query_cap_name()+" "
	      "executes your command.\n");
	    henchman->do_command("get "+dest);
	    break;
	case "attack":
	    tell_room(environment(this_player()),
	      this_player()->query_cap_name()+" screams: Attack!!\n\n");
	    for(i=0;i<sizeof(ob);i++) 
		henchman->attack_ob(ob[i]);
	    break;
	}
	return 1;
    }
    if(order3 != 3) {
	order4 = sscanf(str, "%s %s", henchname, com);
    }
    if(order3 == 3 || order4 == 2) {
	henchname = expand_nickname(henchname);
	com = expand_nickname(com);
	if(order3 == 3) {
	    henchmen = find_match(henchname+" "+num,
	      environment(this_player()));
	    if(!henchmen[0]) {
		notify_fail("There is no "+henchname+" with that number.\n");
		return 0;
	    }
	}
	if(order4 == 2) {
	    henchmen = find_match(henchname, environment(this_player()));
	    if(!sizeof(henchmen)) {
		notify_fail("There is no "+henchname+" here.\n");
		return 0;
	    }
	}
	for(i=0;i<sizeof(henchmen);i++) {
	    if(this_player() != henchmen[i]->query_owner()) {
		tell_object(find_player("raskolnikov"),
		  "blah\n");
		notify_fail("That is not your henchman!\n\n");
		return 0;
	    }
	}
	if(member_array(com, command_list) == -1) {
	    notify_fail("No such command : "+com+".\n");
	    return 0;
	}
	switch(com) {
	case "protect":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->set_protect_owner(1);
		tell_object(this_player(), henchmen[i]->query_cap_name()+""
		  " protects you.\n");
	    }
	    break;
	case "unprotect":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->set_protect_owner(0);
		tell_object(this_player(), henchmen[i]->query_cap_name()+""
		  " stops protecting you.\n");
	    }
	    break;
	case "follow":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->set_follow_owner(1);
		tell_object(this_player(), henchmen[i]->query_cap_name()+""
		  " follows you.\n");
	    }
	    break;
	case "unfollow":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->set_follow_owner(0);
		tell_object(this_player(), henchmen[i]->query_cap_name()+""
		  " stops following you.\n");
	    }
	    break;
	case "equip":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->init_equip();
		tell_object(this_player(), henchmen[i]->query_cap_name()+" "
		  "executes your command.\n");
	    }
	    break;
	case "attack":
	    tell_room(environment(this_player()),
	      this_player()->query_cap_name()+" screams: Attack!!\n\n");
	    ob = ({ });
	    obs = all_inventory(environment(this_player()));
	    for(i=0;i<sizeof(obs);i++) {
		if(!obs[i]->query_property("stfg") && 
		  obs[i]->query_stormfront_guard() != 1)
		    ob += ({ obs[i] });
	    }
	    for(i=0;i<sizeof(henchmen);i++) {
		for(j=0;j<sizeof(ob);j++) {
		    henchmen[i]->attack_ob(ob[j]);
		}
	    }
	    break;
	case "stop":
	    for(i=0;i<sizeof(henchmen);i++) {
		henchmen[i]->remove_call_outed();
		henchmen[i]->reset_attacker_list();
		tell_room(environment(this_player()), 
		  henchmen[i]->query_cap_name()+" stopped all fights.\n");
	    }
	    break;
	}
	return 1;
    }
    notify_fail("Usage : order <target> <targetnum> "
      "<command> <destination>\n Note: targetnum is optional\n");
    return 0;
}
