/** coded by Raskolnikov August 96 **/
/** gives the player his STFG props and extra_look rank **/
/** also contains the ordering ability for henchmen **/
inherit "/std/item";
inherit "/std/guard_system/handlers/henchcomms.c";
int guardnum;
string rank, MEMBER_PROP, KILLER_PROP, HANDLERS, *race_prefs, *guild_prefs;

void set_member_prop(string m_prop);
void set_killer_prop(string k_prop);
void set_handler_path(string path);
int check_insignia(object player);

void set_handler_path(string path) {
    HANDLERS = path;
}

void set_member_prop(string m_prop) {
    MEMBER_PROP = m_prop;
}

void set_killer_prop(string k_prop) {
    KILLER_PROP = k_prop;
}

void set_race_prefs(string *r_prefs) {
    race_prefs = r_prefs;
}

void set_guild_prefs(string *g_prefs) {
    guild_prefs = g_prefs;
}


/*
player_props = ([
  "point_total",
  "current_number_of_guards_with_player",
  "has_secretary_guard",
  "number_guards_to_get_because_increase_in_rank",
  "lost_secretary_so_need_to_demote",
   "assignments",
]);
*/


void init()
{
    int i, insignia_check;
    mapping player_props;
    player_props = environment(this_object())->query_property(MEMBER_PROP);
    insignia_check = check_insignia(environment(this_object()));
    if(insignia_check == 1)  
	call_out("notify_dest", 0, environment(this_object()));
    if(!player_props) {
	i = environment(this_object())->query_level();
	player_props = ([
	  "point_total" : i,
	  "cur_guard_num" : 0,
	  "sec_guard_num" : 0,
	  "num_more_guards" : 0,
	  "lost_secretary" : 0,
	  "assignments" : ({ }),
	]);
	environment(this_object())->add_property(MEMBER_PROP, 
	  player_props);
    }
    i = player_props["point_total"];
    switch(i)
    {
    case 5..19:
	rank = "Private";
	guardnum = 1;
	break;
    case 20..39:
	rank = "Field Corporal";
	guardnum = 1;
	break;
    case 41..69:
	rank = "Sergeant";
	guardnum = 2;
	break;
    case 70..99:
	rank = "Master Sergeant";
	guardnum = 2;
	break;
    case 100..129:
	rank = "Master Sergeant";
	guardnum = 2;
	break;
    case 130..159:
	rank = "First Sergeant";
	guardnum = 3;
	break;
    case 160..189:
	rank = "Sergeant Master";
	guardnum = 3;
	break;
    case 190..219:
	rank = "Lieutenant";
	guardnum = 4;
	break;
    case 220..249:
	rank = "Captain";
	guardnum = 4;
	break;
    case 250..1000:
	rank = "Major";
	guardnum = 5;
	break;
    }
    environment(this_object())->add_extra_look(this_object());
    add_action("henchman_commands", "order");
    ::init();
}

int query_guardnum() { return guardnum; }

string extra_look() { return rank+"\n"; }

string query_rank() { return rank; }

void update_player_props(object owner) {
    int i;
    string *prop_keys, *latest_assigns, *current_assigns, handler;
    mapping props;

    handler = HANDLERS+"point_system_handler";
    props = owner->query_property(MEMBER_PROP);
    latest_assigns = handler->query_assignments();
    if(undefinedp(props["assignments"])) {
	props["assignments"] = latest_assigns;
	return 1;
    }
    /** update mapping with new assignments **/
    current_assigns = props["assignments"];
    for(i=0;i<sizeof(latest_assigns);i++)
	if(member_array(latest_assigns[i], current_assigns) == -1)
	    current_assigns += ({ latest_assigns[i] });
    props["assignments"] = current_assigns;
    owner->add_property(MEMBER_PROP, props);
}

void notify_dest(object player) {
    tell_object(player, "You are not a member of the guard "
      "and therefore you can not have this object.\n");
    player->remove_property(MEMBER_PROP);
    player->add_timed_property(KILLER_PROP, 1, 10000);
    destruct(this_object());
    return 1;
}

int check_insignia(object player) {
    if(member_array(player->query_guild_name(),
	guild_prefs) == -1)  
	return 1;
    if(member_array(player->query_race(),
	race_prefs) == -1)  
	return 1;
    return 0;
}
