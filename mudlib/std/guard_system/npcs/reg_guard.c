inherit "/obj/henchman.c";

int guard_rank, guard_type;
object guard;
string MEMBER_PROP, GUARD_OB_NAME;

void set_member_prop(string m_prop);
void set_guard_ob_name(string name);

void set_member_prop(string m_prop) {
    MEMBER_PROP = m_prop;
}

void set_guard_ob_name(string name) {
    GUARD_OB_NAME = name;
}


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

void do_death() {
    mapping player_props;
    player_props = owner->query_property(MEMBER_PROP);
    player_props["cur_guard_num"] -= 1;
    ::do_death();
}

string extra_look() {
    object insignia;
    insignia = present(GUARD_OB_NAME, owner);
    return insignia->query_rank()+"\n\n";
}

