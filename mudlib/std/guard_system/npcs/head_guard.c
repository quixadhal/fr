inherit "/obj/henchman.c";

int guard_rank, guard_type;
object guard;
string MEMBER_PROP, POINT_SYSTEM_PROP, HANDLERS, GUARD_OB_NAME;

void set_props(string m_prop, string p_prop);
void set_path(string handler);
void set_guard_ob_name(string name);

void set_props(string m_prop, string p_prop) {
    MEMBER_PROP = m_prop;
    POINT_SYSTEM_PROP = p_prop;
}

void set_handler(string path) {
    HANDLERS = path;
}

void set_guard_ob_name(string name) {
    GUARD_OB_NAME = name;
}


int query_sec_guard() { return 1; }

int query_guard_rank() { return guard_rank; }

void set_guard_rank(object player)
{
    call_out("setup_guard", 2, player);
}

void setup_guard(object player)
{
    guard_rank = player->query_level();
    set_level(guard_rank);
}

int query_guard_type() { return guard_type; }

int set_guard_type(int type)
{
    guard_type = type;
}

void init()
{
    ::init();
    set_join_room_mess("The guard rushes to the side of his "
      "commanding officer.");
    set_join_me_mess("The guard rushes to your side.");
    set_leave_room_mess("The guard leaves with his commanding "
      "officer.");
    add_extra_look(this_object());
}


/** check to see if what died is part of the point or bounty systems **/
void event_death(object ob, object *obs) {
    string handler;
    handler = HANDLERS+"point_system_handler.c";
    handler->determine_point_total(ob, obs);
}

void do_death() {
    int sec_total_points, sec_points, player_points;
    mapping player_props, points;

    points = this_object()->query_property(POINT_SYSTEM_PROP);
    player_props = owner->query_property(MEMBER_PROP);
    sec_total_points = points["point_total"];
    sec_points = points["points_with_current_sec"];
    player_points = player_props["point_total"];
    /** take away all points gained with this secretary **/
    /** adjust the rank back when they got to get another secretary **/
    player_props["point_total"] = sec_total_points - sec_points;
    player_props["sec_guard_num"] = 0;
    player_props["cur_guard_num"] -= 1;
    player_props["lost_secretary"] = 1;
    ::do_death();
}

string extra_look() {
    object insignia;
    insignia = present(GUARD_OB_NAME, owner);
    return insignia->query_rank()+"\n\n";
}
