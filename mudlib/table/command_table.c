/* This is the table where all the command are inserted,
 * /std/commands.c uses this one for finding the commands.
 * Baldrick, aug '94.
 */

mapping query_commands()
{
    mapping list;

    list = ([
      "rearrange" : ({ "/std/commands/roller","intro" }),
      "pray" : ({"/std/commands/pray", "pray" }),
      "skills" : ({ "/std/commands/skills","skill_list" }),
      "bury" : ({ "/std/commands/bury", "bury" }),
      "judge" : ({ "/std/commands/judge", "judge" }),
      "ambush" : ({ "/std/commands/ambush", "ambush" }),
      "fix" : ({ "/std/commands/fix", "fix" }),
      "consider" : ({ "/std/commands/consider", "consider" }),
      // Ranger command
      "scout" : ({"/std/commands/scout","scout"}),
      "track" : ({ "/std/commands/track","track" }),
      "hunt" : ({ "/std/commands/hunt","hunt"}),
      "mend" : ({ "/std/commands/mend","mend"}),
      "herbalism" : ({ "/std/commands/herbalism","herbalism"}),
      "summon" : ({"/std/commands/summon.c","summon"}),
      /* Thief commands... */
      "hide" : ({ "/std/commands/hide_in_shad", "hide_in_shadows" }),
      "backstab" : ({ "/std/commands/backstab","backstab" }),
      "sneak" : ({ "/std/commands/sneak", "sneak" }),
      "palm" : ({ "/std/commands/palm", "palm" }),
      "slip" : ({ "/std/commands/slip", "slip" }),
      "steal" : ({ "/std/commands/steal", "steal" }),
      "peek" :({ "/std/commands/steal","peek"}),
      "mug": ({ "/std/commands/mug","mug" }),
      "detect": ({ "/std/commands/detect","detect" }),
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
      // Dark Globe, Drow Warriors
      "darkglobe": ({ "/std/commands/dark.c", "dark_globe" }),
      // Meditate, Wizards of all sorts
      "meditate": ({ "/std/commands/meditation.c", "meditate" }),
      "surge":({ "/std/commands/surge.c","surge" }),
      // Battle ranger, nasty lil kneecappers
      "bash":({ "/std/commands/bash.c","bash" }),
      // Wiz-war commands
      "retrieve":({"/std/commands/retrieve.c", "retrieve" }),
      // Thief/Ranger
      "detect":({"/std/commands/detect.c","detect"}),
      // Shapeshifter
      "shift":({"/std/commands/shifter/shift.c", "shift"}),
      "unshift":({"/std/commands/shifter/unshift.c", "unshift"}),
      // pigeon only
      "fly":({"/std/commands/shifter/fly.c", "fly"}),
      // parasite only
      "infect":({"/std/commands/shifter/infect.c", "infect"}),
      // shifter quest reward
      "study":({"/std/commands/shifter/study.c", "study"}),
   "faerie":({"/std/commands/faerie","faerie"}),
    ]);

    return list;

} /* query_commands */
