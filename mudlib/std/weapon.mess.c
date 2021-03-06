inherit "/std/basic/print_object";
/* this handles the standard messages for the given weapon types
 * types = blunt, sharp, pierce, burn
 * subtypes =
 *  blunt - hands, feet
 *  sharp - claws, bite
 *  pierce - beak
 *  fire
 *  cold
 *  acid
 *  magic
 */

mapping weapon_mess;

void create() {
  weapon_mess =
([ "blunt" :
  ({
1, ({
   "You snick $hname$.\n",
   "$mcname$ snicks you.\n",
   "$mcname$ snicks $hname$.\n",
    }),
3, ({
   "You bruise $hname$.\n",
   "$mcname$ bruises you.\n",
   "$mcname$ bruises $hname$.\n"
    }),
5, ({
   "You hit $hname$.\n",
   "$mcname$ hits you.\n",
   "$mcname$ hits $hname$.\n",
    }),
7, ({
   "You hit $hname$ hard.\n",
   "$mcname$ hits you hard.\n",
   "$mcname$ hits $hname$ hard.\n",
    }),
9, ({
   "You smash $hname$.\n",
   "$mcname$ smashes you.\n",
   "$mcname$ smashes $hname$.\n",
     }),
11, ({
   "You crush $hname$.\n",
   "$mcname$ crushes you.\n",
   "$mcname$ crushes $hname$.\n"
     }),
0,   ({
   "You mash $hname$ up.\n",
   "$mcname$ mashes you up.\n",
   "$mcname$ mashes $hname$ up.\n"
     }),
  }),
"blunt-hands" : ({
1,  ({
   "You snick $hname$.\n",
   "$mcname$ nicks you.\n",
   "$mcname$ nicks $hname$.\n",
     }),
2,  ({
   "You tickle $hname$ in the stomach.\n",
   "$mcname$ tickles you in the stomach.\n",
   "$mcname$ tickles $hname$ in the stomach.\n",
     }),
3,  ({
   "You punch $hname$.\n",
   "$mcname$ punches you.\n",
   "$mcname$ punches $hname$.\n",
     }),
4, ({
   "You elbow $hname$ in the face.\n",
   "$mcname$ elbows you in the face.\n",
   "$mcname$ elbows $hname$ in the face.\n",
     }),
5, ({
   "You jab $hname$ in the stomach.\n",
   "$mcname$ jabs you in the stomach.\n",
   "$mcname$ jabs $hname$ in the stomach.\n",
     }),
6, ({
   "You viciously hook $hname$ under the chin.\n",
   "$mcname$ viciously hooks you under the chin.\n",
   "$mcname$ viciously hooks $hname$ under the chin.\n",
     }),
0,   ({
   "You beat $hname$ to a pulp.\n",
   "$mcname$ beats you to a pulp.\n",
   "$mcname$ beats $hname$ to a pulp.\n",
     }),
  }),
"blunt-feet" : ({
1, ({
   "You snick $hname$.\n",
   "$mcname$ snicks you.\n",
   "$mcname$ snicks $hname$.\n",
    }),
2, ({
   "You tickle $hname$ in the stomach with your toes.\n",
   "$mcname$ tickles you in the stomach with $mposs$ toes.\n",
   "$mcname$ tickles $hname$ in the stomach with $mposs$ toes.\n",
    }),
3, ({
   "You kick $hname$.\n",
   "$mcname$ kicks you.\n",
   "$mcname$ kicks $hname$.\n",
    }),
4, ({
   "You boot $hname$ visciously.\n",
   "$mcname$ boots you visciously.\n",
   "$mcname$ boots $hname$ visciously.\n",
    }),
5, ({
   "You kick $hcname$ in the face.\n",
   "$mcname$ kicks you in the face.\n",
   "$mcname$ kicks $hcname$ in the face.\n",
     }),
6, ({
   "You visciously kick $hcname$ in the stomach.\n",
   "$mcname$ visciously kicks you in the stomach.\n",
   "$mcname$ visciously kicks $hcname$ in the stomach.\n",
    }),
0, ({
   "You kick $hcname$ into a bloody mess.\n",
   "$mcname$ kicks you into a bloody mess.\n",
   "$mcname$ kicks $hcname$ into a bloody mess.\n",
    }),
}),
"sharp" : ({
1, ({
   "You snick $hname$.\n",
   "$mcname$ snicks you.\n",
   "$mcname$ snicks $hname$.\n",
    }),
3, ({
   "You scratch $hname$.\n",
   "$mcname$ scratches you.\n",
   "$mcname$ scratches $hname$.\n"
    }),
5, ({
   "You nick $hname$.\n",
   "$mcname$ nicks you.\n",
   "$mcname$ nicks $hname$.\n",
    }),
7, ({
   "You cut $hname$.\n",
   "$mcname$ cuts you.\n",
   "$mcname$ cuts $hname$.\n",
     }),
9, ({
   "You slice $hname$ up.\n",
   "$mcname$ slices you up.\n",
   "$mcname$ slices $hname$ up.\n",
     }),
11, ({
   "You hack $hname$ up.\n",
   "$mcname$ hacks you up.\n",
   "$mcname$ hacks up $hname$.\n",
     }),
0,  ({
   "You cut $hname$ into small pieces.\n",
   "$mcname$ cuts you into small pieces.\n",
   "$mcname$ cuts $hname$ into small pieces.\n",
    }),
  }),
"sharp-claws" : ({
1, ({
   "You snick $hname$.\n",
   "$mcname$ snicks you.\n",
   "$mcname$ snicks $hname$.\n",
    }),
3, ({
   "You scratch $hname$.\n",
   "$mcname$ scratches you.\n",
   "$mcname$ scratches $hname$.\n"
    }),
5, ({
   "You nick $hname$.\n",
   "$mcname$ nicks you.\n",
   "$mcname$ nicks $hname$.\n",
    }),
7, ({
   "You claw $hname$.\n",
   "$mcname$ claw you.\n",
   "$mcname$ claw $hname$.\n",
     }),
9, ({
   "You slice $hname$ up.\n",
   "$mcname$ slices you up.\n",
   "$mcname$ slices $hname$ up.\n",
     }),
11, ({
   "You hack $hname$ up.\n",
   "$mcname$ hacks you up.\n",
   "$mcname$ hacks up $hname$.\n",
     }),
0,  ({
   "You scratch $hname$'s eyes out.\n",
   "$mcname$ cuts you into small pieces.\n",
   "$mcname$ cuts $hname$ into small pieces.\n",
    }),
}),
"sharp-bite" : ({
1, ({
   "You nip $hname$.\n",
   "$mcname$ nips you.\n",
   "$mcname$ nips $hname$.\n",
    }),
3, ({
   "You chew on $hname$.\n",
   "$mcname$ chews on you.\n",
   "$mcname$ chews on $hname$.\n"
    }),
5, ({
   "You bite $hname$.\n",
   "$mcname$ bites you.\n",
   "$mcname$ bites $hname$.\n",
    }),
7, ({
   "You gash $hname$ with your teeth.\n",
   "$mcname$ gashes you with $mposs$ teeth.\n",
   "$mcname$ gashes $hname$ with $mposs$ teeth.\n",
     }),
9, ({
   "You rip flesh off $hname$.\n",
   "$mcname$ rips flesh off of you.\n",
   "$mcname$ rips flesh off of $hname$.\n",
     }),
11, ({
   "You bite deep into $hname$'s muscle and sinew.\n",
   "$mcname$ bites deep into your muscle and sinew.\n",
   "$mcname$ bites deep into $hname$'s muscle and sinew.\n",
     }),
0,  ({
   "You crunch $hname$'s bones, and rend huge chunks of flesh.\n",
   "$mcname$ crunches your bones, and rends huge chunks of flesh.\n",
   "$mcname$ crunches $hname$'s bones, and rends huge chunks of flesh.\n",
    }),
}),
"pierce": ({
1, ({
    "You jab $hname$.\n",
    "$mcname$ jabs you.\n",
    "$mcname$ jabs $hname$.\n"
    }),
3, ({
    "You stab $hname$.\n",
    "$mcname$ stab you.\n",
    "$mcname$ stab $hname$.\n"
    }),
5, ({
    "You pierce $hname$.\n",
    "$mcname$ pierce you.\n",
    "$mcname$ pierce $hname$.\n"
    }),
7, ({
     "You impale $hname$.\n",
     "$mcname$ impales you.\n",
     "$mcname$ impales $hname$.\n"
     }),
9, ({
     "You skewer $hname$.\n",
     "$mcname$ skewers you.\n",
     "$mcname$ skewers $hname$.\n"
     }),
11, ({
     "You run $hname$ through.\n",
     "$mcname$ runs you through.\n",
     "$mcname$ runs $hname$ through.\n"
     }),
0, ({
   "You make a $hname$-kebab.\n",
   "$mcname$ makes you into a $hname$-kebab.\n",
   "$mcname$ makes $hname$ into a kebab.\n",
   })
}),
"pierce-beak" : ({
1, ({
   "You snick $hcname$.\n",
   "$mcname$ snicks you.\n",
   "$mcname$ snicks $hcname$.\n",
    }),
3, ({
   "You scratch $hcname$ with your beak.\n",
   "$mcname$ scratchs you with $mposs$ beak.\n",
   "You scratch $hcname$ with your beak.\n",
    }),
5, ({
   "You peck $hcname$.\n",
   "$mcname$ pecks you.\n",
   "$mcname$ pecks $hcname$.\n",
    }),
7, ({
   "You visciously peck $hcname$.\n",
   "$mcname$ visciously pecks you.\n",
   "$mcname$ visciously pecks $hcname$.\n",
    }),
9, ({
   "You gouge a hole in $hcname$ with your beak.\n",
   "$mcname$ gouges a hole in you with $mposs$ beak.\n",
   "$mcname$ gouges a hole in $hcname$ with $mposs$ beak.\n",
    }),
11, ({
   "You slice $hcname$ up with your beak.\n",
   "$mcname$ slices you up with $mposs$ beak.\n",
   "$mcname$ slices $hcname$ up with $mposs$ beak.\n",
    }),
0, ({
   "You slice $hcname$ up into small bits with your beak.\n",
   "$mcname$ slices you up into small bits with $mposs$ beak.\n",
   "$mcname$ slices $hcname$ up into small bits with $mposs$ beak.\n",
   }),
}),
"burn" : ({ 
1, ({
    "You singe $hcname$ with the smoke.\n",
    "$mcname$ singes you with the smoke.\n",
    "$mcname$ singes $hcname$ with the smoke.\n",
    }),
3, ({
    "You singe $hcname$.\n",
    "$mcname$ singes you.\n",
    "$mcname$ singes $hcname$.\n",
    }),
5, ({
    "You burn $hcname$.\n",
    "$mcname$ burns you.\n",
    "$mcname$ burns $hcname$.\n",
    }),
7, ({
    "You burn $hcname$ in a new and improved way.\n",
    "$mcname$ burns you in a new and improved way.\n",
    "$mcname$ burns $hcname$ in a new and improved way.\n",
    }),
9, ({
    "You fry $hcname$.\n",
    "$mcname$ frys you.\n",
    "$mcname$ frys $hcname$.\n",
    }),
11, ({
    "You crisp $hcname$.\n",
    "$mcname$ crisps $hcname$.\n",
    "$mcname$ crisps $hcname$.\n",
    }),
0,  ({
    "You cremate $hcname$.\n",
    "$mcname$ cremates you.\n",
    "$mcname$ cremates $hcname$.\n",
    }),
}),
"cold" : ({
1, ({
    "You discomfort $hcname$ with a chill.\n",
    "$mcname$ discomforts you with a chill.\n",
    "$mcname$ discomforts $hcname$ with a chill.\n",
    }),
3, ({
    "You chill $hcname$.\n",
    "$mcname$ chills you.\n",
    "$mcname$ chills $hcname$.\n",
    }),
5, ({
    "You make $hcname$ freeze.\n",
    "$mcname$ makes you freeze.\n",
    "$mcname$ makes $hcname$ freeze.\n",
    }),
7, ({
    "You make $hcname$'s teeth rattle with cold.\n",
    "$mcname$ makes your teeth rattle with cold.\n",
    "$mcname$ makes $hcname$'s teeth rattle with cold.\n",
    }),
9, ({
    "You spray $hcname$ with ice shards.\n",
    "$mcname$ sprays you with ice shards.\n",
    "$mcname$ sprays $hcname$ with ice shards.\n",
    }),
11, ({
    "You wither $hcname$ with freezing cold ice.\n",
    "$mcname$ withers $hcname$ with freezing cold ice.\n",
    "$mcname$ withers $hcname$ with freezing cold ice.\n",
    }),
0,  ({
    "You release a north-pole storm on $hcname$.\n",
    "$mcname$ releases a northpole storm on you.\n",
    "$mcname$ releases a northpole storm on $hcname$.\n",
    }),
}),
"acid" : ({
1, ({
    "You touch $hcname$ with a corrosive substance.\n",
    "$mcname$ touches you with a corrosive substance.\n",
    "$mcname$ touches $hcname$ with a corrosive substance.\n",
    }),
3, ({
    "You singe $hcname$ with a corrosive substance.\n",
    "$mcname$ singes you with a corrosive substance.\n",
    "$mcname$ singes $hcname$ with a corrosive substance.\n",
    }),
5, ({
    "You burn $hcname$ with a corrosive substance.\n",
    "$mcname$ burns you with a corrosive substance.\n",
    "$mcname$ burns $hcname$ with a corrosive substance.\n", 
    }),
7, ({
    "You dissolve $hcname$ with a corrosive substance.\n",
    "$mcname$ dissolves you with a corrosive substance.\n",
    "$mcname$ dissolves $hcname$ with a corrosive substance.\n",
    }),
9, ({
    "You spray $hcname$ with acid.\n",
    "$mcname$ sprays you with acid.\n",
    "$mcname$ sprays $hcname$ with acid.\n",
    }),
11, ({
    "You melt $hcname$ in acid.\n",
    "$mcname$ melts $hcname$ in acid..\n",
    "$mcname$ melts $hcname$ in acid.\n",
    }),
0,  ({
    "You turn $hcname$ into a pool of slush.\n",
    "$mcname$ turns you into a pool of slush.\n",
    "$mcname$ turns $hcname$ into a pool of slush.\n",
    }),
}),
"magic" : ({
1, ({
    "Your Magic Missile barely singe $hcname$.\n",
    "$mcname$ barely singe you with a Magic Missile.\n",
    "$mcname$ barely singes $hcname$ with a Magic Missile.\n",
    }),
3, ({
    "You singe $hcname$ with your Magic Missile.\n",
    "$mcname$ singes you with a Magic Missile.\n",
    "$mcname$ singes $hcname$ with a Magic Missile.\n",
    }),
5, ({
    "Your Magic Missile crashes into $hcname$.\n",
    "$mcname$'s Magic Missile crashes into you.\n",
    "$mcname$'s Magic Missile crashes into $hcname$.\n",
    }),
10, ({
    "You burn $hcname$ with your Fireball.\n",
    "$mcname$ burns you with a Fireball.\n",
    "$mcname$ burns $hcname$ with a Fireball.\n",
    }),
15, ({
    "You shock $hcname$ with your Lightning Bolt.\n",
    "$mcname$ shock you with a Lightning Bolt.\n",
    "$mcname$ shock $hcname$ with a Lightning Bolt.\n",
    }),
20, ({
    "You crisp $hcname$ with your Fire Ball.\n",
    "$mcname$ crisps $hcname$ with a Fire Ball.\n",
    "$mcname$ crisps $hcname$ with a Fire Ball.\n",
    }),
30, ({
    "You fry $hcname$ with Hellfire.\n",
    "$mcname$ fries $hcname$ with Hellfire.\n",
    "$mcname$ fries $hcname$ with Hellfire.\n",
    }),
50, ({
    "You bury $hcname$ in Hellpyre Flames.\n",
    "$mcname$ buries $hcname$ in Hellpyre Flames.\n",
    "$mcname$ buries $hcname$ in Hellpyre Flames.\n",
    }),
0,  ({
    "You cremate $hcname$ in a shower of Fiery Meteors.\n",
    "$mcname$ cremates you in a shower of Fiery Meteors.\n",
    "$mcname$ cremates $hcname$ in a shower of Fiery Meteors.\n",
    }),
}),
]);
}

string parse_string(string mess, object him, object me) {
  string s1, s2, s3, rest;

  rest = "";
  while (sscanf(mess, "%s$%s$%s", s1, s2, s3)==3)
    switch (s2) {
      case "hname" :
        mess = s1+him->query_name()+s3;
        break;
      case "mname" :
        mess = s1+me->query_name()+s3;
        break;
      case "hcname" :
        mess = s1+him->query_cap_name()+s3;
        break;
      case "mcname" :
        mess = s1+me->query_cap_name()+s3;
        break;
      case "mposs" :
        mess = s1 + me->query_possessive() + s3;
        break;
      case "hposs" :
        mess = s1 + him->query_possessive() + s3;
        break;
      default :
        rest = s1+"$"+s2+"$";
        mess = s3;
        break;
    }
  return rest+mess;
}

mixed query_message(int dam, string type, object him, object me, string name) {
  int j;
  mixed *ind;

  if (!(ind = weapon_mess[type+"-"+name]))
    if (!(ind = weapon_mess[type]))
      return 0;
  while (j<sizeof(ind) && dam > ind[j])
    j += 2;
  if (j >= sizeof(ind))
    j = sizeof(ind)-2;
  return ({ parse_string(ind[j+1][0], him, me),
            parse_string(ind[j+1][1], him, me),
            parse_string(ind[j+1][2], him, me) });
}

int add_weapon_mess(string type, mixed arr) {
  weapon_mess[type] =  arr;
  return 1;
}

int remove_weapon_mess(string type) {
  weapon_mess = m_delete(weapon_mess, type);
  return 1;
}

mixed query_weapon_mess(string type) { return weapon_mess[type]; }

mapping query_all_weapon_mess() { return weapon_mess + ([ ]); }
