/* This is the table where all the command are inserted,
 * /std/commands.c uses this one for finding the commands.
 * Baldrick, aug '94.
 */

mapping query_commands()
  {
  mapping list;

  list = ([
    "testarrange" : ({ "/std/commands/stats-rear","do_rerrange" }),
      "pray" : ({"/std/commands/pray", "pray" }),
    "skills" : ({ "/std/commands/skills","skill_list" }),
    "bury" : ({ "/std/commands/bury", "bury" }),
    "judge" : ({ "/std/commands/judge", "judge" }),
    "ambush" : ({ "/std/commands/ambush", "ambush" }),
    "fix" : ({ "/std/commands/fix", "fix" }),
    "consider" : ({ "/std/commands/consider", "consider" }),
/* Thief commands... */
    "hide" : ({ "/std/commands/hide_in_shad", "hide_in_shadows" }),
  "backstab" : ({ "/std/commands/backstab","backstab" }),
    "sneak" : ({ "/std/commands/sneak", "sneak" }),
    "palm" : ({ "/std/commands/palm", "palm" }),
    "slip" : ({ "/std/commands/slip", "slip" }),
    "steal" : ({ "/std/commands/steal", "steal" }),
   "peek" :({ "/std/commands/steal","peek"}),
   "mug": ({ "/std/commands/mug","mug" }),
/* Wizard commands... */
    "remember" : ({ "/std/commands/remember", "remember" }),
    "forget" : ({ "/std/commands/forget", "forget" }),
/* As yet unwritten.
    "assess" : ({ "/std/commands/assess", "assess" }),
 */
 // Fighter commands...
    "berserk" : ({ "/std/commands/go_berserk", "go_berserk" }),
 // Drow warrior
   "slice": ({"/std/commands/slice","slice"}),
   // Misc thief wiz-thief
   "peek":({"/std/commands/peek","peek"}),
   // Turn (clerics)
   "turn":({"/std/commands/turn","turn"}),
   // Disarm , anyone
   "disarm": ({"/std/commands/disarm","disarm" }),
   // Bearhug fighters
   "bearhug": ({"/std/commands/bearhug","bearhug" }),
   // Disappear, Thieves
   "disappear": ({"/std/commands/disappear","disappear" }),
    // Charge, paladins and anti-paladins
    "charge" : ({ "/std/commands/charge", "charge" }),
    // Layhands, paladins
    "layhands": ({ "/std/commands/layhands.c", "layhands" }),
    // Drain, anti-paladins
    "drain": ({ "/std/commands/drain.c", "drain" }),
   // Decapitate, Assasin trophies
   "decapitate":({ "/std/commands/decapitate.c", "decapitate" }),
    // Focus, assassins and all fighter-types
    "focus": ({ "/std/commands/focus.c", "focus" }),
  ]);

  return list;

} /* query_commands */
