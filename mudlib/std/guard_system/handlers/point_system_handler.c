/** coded by Raskolnikov Sept 96 **/
/** awards the points and the money for the STFG **/
inherit "/std/object.c";

string *assignments, *bonus_races, *bonus_guilds, KILLER_PROP,
MEMBER_PROP, POINT_SYSTEM_PROP;
mapping points;

void set_assignments(string *assigns);
void set_bonus_races(string *b_races);
void set_bonus_guilds(string *b_guilds);
void setup_points(mapping pnts);
void set_props(string k_prop, string m_prop, string p_prop);

string *query_assignments() { return assignments; }

void set_assignments(string *assigns) {
    assignments = assigns;
}

void set_bonus_races(string *b_races) {
    bonus_races = b_races;
}

void set_bonus_guilds(string *b_guilds) {
    bonus_guilds = b_guilds;
}

void setup_points(mapping pnts) {
    /*
    points = ([
      "monster_set_name" : ({ "points_worth", "number_allowed_to_kill" }),
      "total_number_of_points",
      "points_acquired_with_this_head_guard",
      "pcs_killed" : ([
	"player_name" : ({
	  "race",
	  "guild_name",
	  "level",
	  "xp",
	  "total_number_of_times_killed",
	  "total_number_of_times_checked",
	})
      ]),
    ]);
    */

    points = pnts;
}

void set_props(string k_prop, string m_prop, string p_prop) {
    KILLER_PROP = k_prop;
    MEMBER_PROP = m_prop;
    POINT_SYSTEM_PROP = p_prop;
}

mapping setup_point_system(object owner) {
    int point_total;
    mapping player_props;

    player_props = owner->query_property(MEMBER_PROP);
    point_total = player_props["point_total"];
    points["point_total"] = point_total;
    return points;
}

void update_point_system(object secretary) {
    int i;
    string *point_keys, *lpoint_keys;
    mapping points, latest_points;
    object owner;

    owner = secretary->query_owner();
    points = secretary->query_property(POINT_SYSTEM_PROP);
    point_keys = keys(points);
    latest_points = setup_point_system(owner);
    lpoint_keys = keys(latest_points);
    /** update mapping with new assignments **/
    for(i=0;i<m_sizeof(latest_points);i++) 
	if(member_array(lpoint_keys[i], point_keys) == -1) 
	    points[lpoint_keys[i]] = latest_points[lpoint_keys[i]];
    secretary->add_property(POINT_SYSTEM_PROP, points);
}

void determine_point_total(object victim, object *killers) {
    int i, killer_index, number_allowed;
    string *check_monster, monster, pc_name;
    object killers_room, victims_room, owner, secretary;
    mapping points;

    secretary = previous_object();
    owner = secretary->query_owner();
    if(!secretary->query_property(POINT_SYSTEM_PROP)) {
	points = setup_point_system(owner);
	secretary->add_property(POINT_SYSTEM_PROP, points);
    }
    points = secretary->query_property(POINT_SYSTEM_PROP);
    if(victim->query_timed_property(KILLER_PROP) &&
      interactive(victim)) {
	pc_name = victim->query_name();
	if(!sizeof(points["pcs_killed"][pc_name])) {
	    points["pcs_killed"][pc_name] = ({ 0, 0, 0, 0, 0, 0, });
	    points["pcs_killed"][pc_name][0] = victim->query_race();
	    points["pcs_killed"][pc_name][1] = victim->query_guild_name();
	    points["pcs_killed"][pc_name][2] = victim->query_level();
	    points["pcs_killed"][pc_name][3] = victim->query_xp();
	    points["pcs_killed"][pc_name][4] += 1;
	    return 1;
	}
	points["pcs_killed"][pc_name][2] = victim->query_level();
	points["pcs_killed"][pc_name][3] += victim->query_xp();
	points["pcs_killed"][pc_name][4] += 1;
	return 1;
    }
    killer_index = member_array(owner, killers);
    killers_room = environment(owner);
    victims_room = environment(victim);
    if(killer_index != -1 && (killers_room == victims_room)) {
	monster = victim->query_name();
	check_monster = m_indices(points);
	if(member_array(monster, check_monster) != -1) {
	    points["point_total"] += points[monster][0];
	    points["points_with_current_sec"] += points[monster][0];
	    number_allowed = points[monster][1];
	    if(number_allowed > 1) {
		points[monster][1] = number_allowed - 1;
		return 1;
	    }
	    points = m_delete(points, monster);
	    secretary->add_property(POINT_SYSTEM_PROP, points);
	}
    }
    return 1;
}

void award_bounty(object hunter, object secretary) {
    int i, level, bounty, numtimes_killed, numtimes_checked;
    string *pc_names, temp_pcname, guild, race;
    mapping points;

    points = secretary->query_property(POINT_SYSTEM_PROP);
    pc_names = keys(points["pcs_killed"]);
    for(i=0;i<sizeof(pc_names);i++) {
	temp_pcname = pc_names[i];
	numtimes_killed = points["pcs_killed"][temp_pcname][4];
	numtimes_checked = points["pcs_killed"][temp_pcname][5];
	while(numtimes_killed != numtimes_checked) {
	    points["pcs_killed"][temp_pcname][5] += 1;
	    numtimes_checked += 1;
	    level = points["pcs_killed"][temp_pcname][2];
	    guild = points["pcs_killed"][temp_pcname][1];
	    race = points["pcs_killed"][temp_pcname][0];
	    bounty = level*4;
	    if(member_array(guild, bonus_guilds) != -1) bounty += 20;
	    if(member_array(guild, bonus_races) != -1) bounty += 20;
	    hunter->adjust_money(bounty, "platinum");
	    tell_object(hunter, "You are paid "+bounty+" "
	      "platinum coins for ridding the City "
	      "of "+capitalize(temp_pcname)+".\n\n");
	}
    }
    return 1;
}

