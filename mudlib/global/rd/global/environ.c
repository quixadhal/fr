/* added by Akira 95/04/13 to support damage from adverse environments */
static int ti,tii;
#define START_EFFECTS_TIME 7
#define RECOVERY_RATE	3
#define RESTART_RATE	2
#define ARMOUR_FACTOR	10

int resistance_calc(int base, int resistance) {
	int damage;
	damage = (base * (100 - resistance)) / 100;
	return damage;
}

int apply_effects(object ob, string type, string check) {
	int damage,severity,immunity,resist;

	damage = 0;
	if (ti > (ob->query_con() * START_EFFECTS_TIME)) {
		resist = (int)ob->query_resistance(type);
		severity = (int)environment(ob)->query_property(type);
		immunity = (int)ob->query_property(check) +
			   (ob->query_ac(type) / ARMOUR_FACTOR);
		damage = resistance_calc(severity,resist) - immunity;
	} 
	return damage;
}

void adverse_environment(object ob)
{
  string mess;
  int speed,severity,threshold;
  if (!environment(ob)) {
	return;
  }
  if (ob->query_property("dead")) return;
   
  /* atmospheric effects */
  if (speed = environment(ob)->query_property("adverse")) {
 	if (ti < 1000) ti=ti + speed;
	if (environment(ob)->query_property("water")) {
		severity = apply_effects(ob,"water","water breathing");
		if (!environment(ob)->query_underwater())
			severity = severity / 50;
		if (severity > 0) {
			ob->adjust_hp(-1 * severity,environment(ob));
			write("You're drowning!\n");
		}
        }
	if (environment(ob)->query_property("dry")) {
		severity = apply_effects(ob,"dry","desert dweller");
		if (environment(ob)->query_light() < 30)
			severity = severity / 2;
		if (severity > 0) {
			ob->adjust_hp(-1 * severity,environment(ob));
			write("You're dehydrating!\n");
		}
        }
	if (environment(ob)->query_property("air")) {
		severity = apply_effects(ob,"air","non breathing");
		if (severity > 0) {
			ob->adjust_hp(-1 * severity,environment(ob));
			write("You're sufficating!\n");
		}
        }
	if (environment(ob)->query_property("cold")) {
		severity = apply_effects(ob,"cold","arctic dweller");
		if (severity > 0) {
			ob->adjust_hp(-1 * severity,environment(ob));
			write("You're freezing!\n");
		}
        }
	if (ti > (ob->query_con() * START_EFFECTS_TIME)) {
		ti = ti - (ob->query_con() * RESTART_RATE);
	}
  } else {
	ti = ti - (ob->query_con() * RECOVERY_RATE);
	if (ti < 0) ti = 0;
  }

  /* light sensitivity effects */
  if (threshold = ob->query_property("light sensitive")) {
     if ((severity=environment(ob)->query_light() - threshold) > 0) {
	if (tii < 1000) ti++;
	if (tii > (ob->query_con() * START_EFFECTS_TIME)) {
	    tii = tii - (ob->query_con() * RESTART_RATE);
	    ob->adjust_hp(resistance_calc(severity,
			  ob->query_resistance("light")),environment(ob));
	    write("The light in the area burns your skin.\n"); 
	}
     } else { 
	tii = tii - (ob->query_con() * RECOVERY_RATE); 
	if (tii < 0) tii = 0;
     }
  }
}
