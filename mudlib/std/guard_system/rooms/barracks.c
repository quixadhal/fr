/** room to get guards...Raskolnikov **/
inherit "/std/room.c";

string MEMBER_PROP, POINT_SYSTEM_PROP, GUARD_OB_NAME, HANDLERS, NPCS;

void set_props(string m_prop, string p_prop);
void set_guard_ob_name(string name);
void set_paths(string handlers, string npcs);

void set_props(string m_prop, string p_prop) {
    MEMBER_PROP = m_prop;
    POINT_SYSTEM_PROP = p_prop;
}

void set_guard_ob_name(string name) {
    GUARD_OB_NAME = name;
}

void set_paths(string handlers, string npcs) {
    HANDLERS = handlers;
    NPCS = npcs;
}


void recruit_guards(string str)
{
    int guardnum, new_guardnum, rank, i, current_guardnum, flag;
    string handler;
    object guard, insignia, vaughn, me;
    mapping player_props, points;
    mixed *henchmen;

    if(!str) return 0;
    flag = 0;
    if(str == "guards")
    {
	if(!this_player()->query_property(MEMBER_PROP))
	{
	    write("You are not a member of the Guard!\n\n");
	    return 1;
	}
	insignia = present(GUARD_OB_NAME,
	  this_player());
	if(!insignia) {
	    tell_object(this_player(), "You need an insignia.\n\n");
	    return 1;
	}
	player_props = this_player()->query_property(MEMBER_PROP);
	handler = HANDLERS+"point_system_handler.c";
	guardnum = insignia->query_guardnum();
	/** if there was an error with henchmen getting dested **/
	henchmen = this_player()->query_henchmen();
	for(i=0;i<sizeof(henchmen);i++)
	    if(!henchmen[i])
		henchmen -= ({ henchmen[i] });
	if(henchmen == ({ }) ) {
	    me = this_player();
	    if(player_props["sec_guard_num"] == 1)
		this_object()->setup_sec_guard(me, player_props);
	    if(player_props["cur_guard_num"] > 0)
		this_object()->setup_reg_guard(me, 
		  player_props, guardnum);
	    flag = 1;
	}
	/** setup head guard **/
	if(player_props["sec_guard_num"] == 0) 
	    this_object()->setup_sec_guard(me, player_props);
	/** if they had a head guard already and he died, send **/
	/** Lt. Vaughn in to give em hell and take away any rank **/
	/** that they got with the guard that died (mostly in vaughn) **/
	if(player_props["lost_secretary"] == 1) {
	    player_props["lost_secretary"] = 0;
	    vaughn = clone_object(NPCS+"vaughn.c");
	    vaughn->move(environment(this_player()));
	    vaughn->do_demotion(this_player());
	}
	new_guardnum = player_props["num_more_guards"];
	current_guardnum = player_props["cur_guard_num"];
	/** if they went up in rank and got more guards give em more **/
	if(current_guardnum >= 1 && new_guardnum > 0) {
	    for(i=0;i<new_guardnum;i++) {
		guard = clone_object(NPCS+"guard_sig.c");
		guard->set_owner(this_player());
		guard->move(environment(this_player()));
		guard->set_protect_owner(1);
		guard->set_follow_owner(1);
		this_player()->add_henchman(guard);
		guard->set_guard_rank(this_player());
	    }
	    player_props["num_more_guards"] = 0;
	    return 1;
	}
	if(flag == 0) {
	    if(current_guardnum == guardnum) {
		notify_fail("You already have your alotted number of "
		  "guards.\n\n");
		return 0;
	    }
	    if(current_guardnum >= 1) {
		notify_fail("You still have recruits left and will "
		  "not be given more unless they ALL perish.\n\n");
		return 0;
	    }
	    /** if they are all out of regular guards give em more **/
	    if(guardnum > 1) 
		this_object()->setup_reg_guard(me,
		  player_props, guardnum);
	    return 1;
	}
	return 1;
    }
    flag = 0;
    return 1;
}

void setup_sec_guard(object player, mapping player_props) {
    string handler;
    object guard;
    mapping points;

    handler = HANDLERS+"point_system_handler.c";
    guard = clone_object(NPCS+"guard_sig_sec.c");
    guard->set_owner(player);
    guard->move(environment(player));
    guard->set_protect_owner(1);
    guard->set_follow_owner(1);
    player->add_henchman(guard);
    player_props["sec_guard_num"] = 1;
    player_props["cur_guard_num"] += 1;
    points = handler->setup_point_system(player);
    guard->add_property(POINT_SYSTEM_PROP, points);
    guard->set_guard_rank(player);
}

void setup_reg_guard(object me, mapping player_props, int guardnum) {
    int i;
    string handler;
    object guard;

    handler = HANDLERS+"point_system_handler.c";
    for(i=1;i<guardnum;i++)
    {
	guard = clone_object(NPCS+"guard_sig.c");
	guard->set_owner(me);
	guard->move(environment(me));
	guard->set_protect_owner(1);
	guard->set_follow_owner(1);
	me->add_henchman(guard);
	guard->set_guard_rank(me);
    }
    player_props["cur_guard_num"] = i;
    player_props["num_more_guards"] = 0;
}

/** setup the guard's stats **/
void levelset(object guard, object me)
{
    guard->set_guard_rank();
}

void init()
{
    ::init();
    add_action("recruit_guards", "recruit");
}
