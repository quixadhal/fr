inherit "/obj/henchman.c";

string *assignments, *current_assigns, *race_prefs, *guild_prefs,
info_string, KILLER_PROP, QUIT_PROP, MEMBER_PROP, GUARD_OB, 
GUARD_OB_NAME, HEAD_GUARD_NAME, LOGS, ASSIGN, HANDLERS, 
POINT_SYSTEM_PROP;

void set_assignments(string *assigns);
void set_current_assigns(string *cur_assigns);
void set_race_prefs(string *r_prefs);
void set_guild_prefs(string *g_prefs);
void set_info(string info);
void set_paths(string logs, string assigns, string handlers);
void set_props(string k_prop, string q_prop, string m_prop, 
  string p_prop);
void set_guard_ob(string path, string name);
void set_head_guard_name(string name);
int check_insignia(object player);

string *query_guild_prefs() { return guild_prefs; }
string *query_race_prefs() { return race_prefs; }

void set_assignments(string *assigns) {
    assignments = assigns;
}

void set_current_assigns(string *cur_assigns) {
    current_assigns = cur_assigns;
}

void set_race_prefs(string *r_prefs) {
    race_prefs = r_prefs;
}

void set_guild_prefs(string *g_prefs) {
    guild_prefs = g_prefs;
}

void set_info(string info) {
    info_string = info;
}

void set_paths(string logs, string assigns, string handlers) {
    LOGS = logs;
    ASSIGN = assigns;
    HANDLERS = handlers;
}

void set_props(string k_prop, string q_prop, string m_prop, 
  string p_prop) {
    KILLER_PROP = k_prop;
    QUIT_PROP = q_prop;
    MEMBER_PROP = m_prop;
    POINT_SYSTEM_PROP = p_prop;
}

void set_guard_ob(string path, string name) {
    GUARD_OB = path;
    GUARD_OB_NAME = name;
}

void set_head_guard_name(string name) {
    HEAD_GUARD_NAME = name;
}

void init() {
    add_action("join", "join");
    add_action("info", "info");
    add_action("leave_guard", "leave");
    add_action("request_assignment", "request");
    add_action("retire_guard", "retire");
    ::init();
}

void join(string what) {

    if(member_array(this_player()->query_guild_name(),
	guild_prefs) == -1) {
	do_command("say You are not "
	  "the sort we are looking for.\n\n");
	return 1;
    }

    if(member_array(this_player()->query_race(),
	race_prefs) == -1) {
	do_command("say You are not "
	  "the sort we are looking for.\n\n");
	return 1;
    }

    if(this_player()->query_timed_property(KILLER_PROP)) {
	if(member_array(this_player()->query_guild_name(),
	    guild_prefs) == -1) {
	    do_command("say You've got "
	      "a lot of nerve.  Get out of here or die.\n\n");
	    this_object()->attack_ob(this_player());
	    return 1;
	}
    }


    if(this_player()->query_property(QUIT_PROP)) {
	do_command("say We knew "
	  "you would be back.  Sorry, we're not interested.\n\n");
	return 1;
    }

    if(this_player()->query_property(MEMBER_PROP)) {
	do_command("say You are "
	  "already a member of the guard and as much as I wish "
	  "we had more like you, there is no need for you to "
	  "join again.\n\n");
	return 1;
    }

    clone_object(GUARD_OB)->move(this_player());
    write_file(LOGS+"GUARD_MEMBERS", ctime(time())+": "+
      this_player()->query_cap_name()+ " joined the guard.\n");
    do_command("cheer "+this_player()->query_name());
    do_command("say Congratulations "
      ""+this_player()->query_cap_name()+", "
      "you are now a member of the guard!");
    return 1;
}

void leave_guard(string what) {

    if(!what) {
	tell_object(this_player(), "Type 'leave guard' to quit the "
	  "guard.\n");
	return 1;
    }
    if(what != "guard") {
	tell_object(this_player(), "Type 'leave guard' to quit the "
	  "guard.\n");
	return 1;
    }
    if(!query_property(MEMBER_PROP)) {
	do_command("say You are not "
	  "even a member of the guard.\n\n");
	return 1;
    }


    tell_object(this_player(), "You will not be able to rejoin the "
      "guard.  Are you sure you want to leave (y/n)?  ");
    input_to("check_leave_guard", 1);
    return 1;
}

void check_leave_guard(string what) {
    object insignia;

    if((what != "y") && (what != "yes") && (what != "n") &&
      (what != "no")) {
	tell_object(this_player(), "Type yes to leave the guard or "
	  "no to stay in the guard.\n\n");
	input_to("check_leave_guard", 1);
	return 1;
    }

    if((what == "no") && (what == "n")) {
	do_command("say Ahhh, you've "
	  "decided to stay with us, then?  Good choice!\n\n");
	return 1;
    }

    insignia = present(GUARD_OB_NAME, this_player());
    this_player()->remove_extra_look(insignia);
    insignia->dest_me();
    this_player()->remove_property(MEMBER_PROP);
    this_player()->add_property(QUIT_PROP, 1);
    write_file(LOGS+"GUARD_MEMBERS", ctime(time())+": "+
      this_player()->query_cap_name()+ " QUIT the guard.\n");
    do_command("say Very well, quitter, leave and never come back!");
    do_command("spit "+this_player()->query_name());
    return 1;
}

string info() {
    return info_string;
}

void get_assignment(string str) {
    int i, ind;
    string *assigned, handler, *assigns;
    object assign_ob, *henchmen, secretary, owner, insignia;
    mapping player_props;

    if(member_array(str, current_assigns) == -1) {
	do_command("say That was not one of your choices.");
	input_to("get_assignment");
	return 1;
    }

    owner = this_player();
    insignia = present(GUARD_OB_NAME, owner);
    handler = HANDLERS+"point_system_handler";
    player_props = this_player()->query_property(MEMBER_PROP);
    henchmen = this_player()->query_henchmen();
    for(i=0;i<sizeof(henchmen);i++)
	if(henchmen[i] != 0)
	    if(henchmen[i]->query_sec_guard() == 1)
		secretary = henchmen[i];
    if(!secretary) {
	do_command("say You need a Head guard first.");
	return 1;
    }

    if(m_sizeof(player_props)) {
	if(m_sizeof(player_props["assignments"]))
	    assigned = player_props["assignments"];
	if(member_array(str, assigned) != -1) {
	    do_command("say You were already give that assignment.");
	    return 1;
	}
	assigns = handler->query_assignments();
	ind = member_array(str, assigns);
	assign_ob = clone_object(ASSIGN+assigns[ind+1]);
	assign_ob->move(this_player());
	do_command("say Here is your assignment.  Good Luck!");
	handler->update_point_system(secretary);
	insignia->update_player_props(owner);
    }
    return 1;
}

void request_assignment(string what) {
    int i;

    if((what != "assignment") && (what != "special assignment")) {
	do_command("say Request what?");
	return 1;
    }
    if(what == "special assignment") {
	do_command("say Which assignment would you be "
	  "interested in?");
	for(i=0;i<sizeof(current_assigns);i++) 
	    tell_object(this_player(), current_assigns[i]+"\n");
	input_to("get_assignment");
	return 1;
    }
    if(!this_player()->query_property(MEMBER_PROP)) {
	do_command("say Get out "
	  "of here, you filthy beggar.\n\n");
	return 1;
    }
    do_command("say We cannot "
      "handout assignments at this time.  Please come back "
      "in a few days.\n\n");
    return 1;
}


void event_enter(object guest, string mess, object from) {
    if(member_array(guest->query_race(), race_prefs) != -1) {
	call_out("do_greeting",1,guest);
	return(1);
    }
    if(member_array(guest->query_race(), race_prefs) == -1 ||
      (guest->query_property("quit_stormfront_guard")))
    {
	call_out("do_hate",0,guest);
	return(1);
    }
    return 1;
}

do_hate(object obj) {
    do_command("say ARGH!  Go back to the "
      "hole from which you came!\n");
    return(1);
}

do_greeting(object obj) {
    object insignia;
    mapping player_props;

    insignia = present(GUARD_OB_NAME, obj);
    player_props = obj->query_property(MEMBER_PROP);
    if(player_props) {
	do_command("greet "+obj->query_name());
	call_out("secretary_check", 3, player_props, obj);
	return 1;
    }

    do_command("bow formally "+obj->query_name());
    return 1;
}

void secretary_check(mapping player_props, object obj) {
    int player_points, sec_points, cur_gnum, new_gnum;
    string handler, old_rank, new_rank;
    object insignia, head_guard;
    mapping points;

    insignia = present(GUARD_OB_NAME, obj);
    handler = HANDLERS+"point_system_handler.c";
    head_guard = present(HEAD_GUARD_NAME,
      environment(this_object()));
    if(head_guard) {
	points = head_guard->query_property(POINT_SYSTEM_PROP);
	player_points = player_props["point_total"];
	sec_points = points["point_total"];
	old_rank = insignia->query_rank();
	cur_gnum = insignia->query_guardnum();
	if(player_points != sec_points) {
	    player_props["point_total"] = sec_points;
	    insignia->init();
	    new_gnum = insignia->query_guardnum();
	    new_rank = insignia->query_rank();
	    if(old_rank != new_rank) {
		tell_object(obj, this_object()->query_cap_name()+" "
		  "confers with your Head Guard "
		  "and awards you a new rank.  Congratulations!\n\n");
		player_props["num_more_guards"] = new_gnum - cur_gnum;
	    }
	}
	handler->award_bounty(obj, head_guard);
	return 1;
    }
    return 1;
}

void do_demotion(object guard) {
    tell_object(guard, this_object()->query_cap_name()+" "
      "enters the barracks with "
      "a stern look on his face.\n\n");
    do_command("say You are supposed to protect these "
      "infantry men and bring them back alive.");
    do_command("glare "+guard->query_name());
    do_command("shake");
    call_out("stage_two", 6, guard);
    return 1;
}

void stage_two(object guard) {
    object insignia;

    insignia = present(GUARD_OB_NAME, guard);
    do_command("say Let this be a lesson to you!");
    tell_object(guard, "\n"+this_object()->query_cap_name()+" "
      "strips you of any rank that you "
      "achieved with your previous Head Guard.\n\n");
    do_command("curse");
    tell_object(guard, "\n"+this_object()->query_cap_name()+" "
      "goes back to his office.\n\n");
    insignia->init();
    dest_me();
    return 1;
}


