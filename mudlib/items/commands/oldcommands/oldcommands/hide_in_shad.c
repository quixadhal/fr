#define SKILL "dex.thief.hide"
#define HIDE_SKILL 150
#define COST 10
#define SHADOW "/std/commands/shadows/hide"

int hide_in_shadows(string str) {
  int sk_bon;
  object ob;

  if ((int)this_player()->query_gp() < COST) {
    notify_fail("Not enough guild points to hide.\n");
    return 0;
  }
  this_player()->adjust_gp(-COST);
  sk_bon = (int)this_player()->query_skill_bonus(SKILL);
  if (sk_bon > random(HIDE_SKILL) && !this_player()->query_hide_shadow()) {
/* they succeeded. */
    ob = clone_object(SHADOW);
    ob->setup_shadow(this_player());
    tell_room(environment(this_player()),
              this_player()->query_cap_name()+" "+
              this_player()->query_mmsgout()+".\n");
  } else
    say(this_player()->query_cap_name()+" fails to hide in the shadows.\n");
  write("Ok, you hide in the shadows.\n");
  return 1;
}

string help() {
  return "Syntax: hide\n\nAllows you to hide in shadows.  This allows "+
    "you to escape glancing eyes.  It relies on the skill, "+ SKILL +
    "and it costs "+ COST +" guild points regardless of success or failure."+
    "\n\nExample:\n> hide\nOk, you hide in shadows.\n\nSee also: "+
    "sneak.\n";
}

