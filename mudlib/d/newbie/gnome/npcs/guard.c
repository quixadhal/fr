inherit "obj/monster.c";
void setup()
{
set_name("guard");
set_short("Guard");
set_long("This is an average looking guard.  It is quite muscular, "
    "and it looks you up and down as you pass by it.  You wonder if you should even consider bothering it.\n\n");
set_max_hp(20);
set_dex(15);
set_str(15);
set_con(19);
set_wis(8);
set_int(8);
set_cha(8);
set_level(4);
set_al(0);
set_gender(random(2)+1);
load_chat(40,({
  1, "The guard looks at you suspiciously as you pass by.",
}));
clone_object("/d/newbie/gnome/armour/shield.c")->move(this_object());
clone_object("/d/newbie/gnome/armour/helmet.c")->move(this_object());
clone_object("/d/newbie/gnome/armour/chainmail.c")->move(this_object());
clone_object("/d/newbie/gnome/weapons/short_sword.c")->move(this_object());
command("equip");
}

