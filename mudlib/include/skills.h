#define SKILL_NAM 0
#define SKILL_LVL 1
#define SKILL_EXP 2
#define SKILL_BIT 3
#define SKILL_ARR_SIZE 4
#define SKILL_OB "/std/skills"
#define COST_DIV 10

/*
 * These are used in /std/living/skills.c for the training/learning of skills.
 */
#define O_SKILL 0
#define O_NUM 1
#define O_LVL 2
#define O_XP 3
#define O_OTHER_PER 4
#define DEFAULT_COST 500
#define DEFAULT_XP_COST 2000
#define STD_SKILLS ({ \
  "str", 0, 0, ({ \
     "melee", 0, 0, ({ \
       "left", 0, 0, ({ \
          "sharp", 0, 0, ({ }), \
          "blunt", 0, 0, ({ }), \
          "piercing", 0, 0, ({ }), \
          "unarmed", 0, 0, ({ }), \
          "parry", 0, 0, ({ }), \
       }), \
       "right", 0, 0, ({ \
          "sharp", 0, 0, ({ }), \
          "blunt", 0, 0, ({ }), \
          "piercing", 0, 0, ({ }), \
          "unarmed", 0, 0, ({ }), \
          "parry", 0, 0, ({ }), \
       }), \
       "twohanded", 0, 0, ({ \
          "sharp", 0, 0, ({ }), \
          "blunt", 0, 0, ({ }), \
          "piercing", 0, 0, ({ }), \
          "parry", 0, 0, ({ }), \
       }), \
     }), \
     "tackle", 0, 0, ({ }), \
     "bend", 0, 0, ({ }), \
     "lift", 0, 0, ({ }), \
     "smithing", 0, 0, ({ }), \
     "swimming", 0, 0, ({ }), \
     "jumping", 0, 0, ({ }), \
  }), \
  "dex", 0, 0, ({ \
     "reaction", 0, 0, ({ }), \
     "dodging", 0, 0, ({ \
        "range", 0, 0, ({ }), \
        "melee", 0, 0, ({ }), \
     }), \
     "thief", 0, 0, ({ \
        "stealth", 0, 0, ({ }), \
        "pickpocket", 0, 0, ({ }), \
        "hide", 0, 0, ({ }), \
        "openlock", 0, 0, ({ }), \
        "findtrap", 0, 0, ({ }), \
        "removetrap", 0, 0, ({ }), \
        "backstab", 0, 0, ({ }), \
     }), \
     "climb", 0, 0, ({ }), \
     "missile", 0, 0, ({ \
        "thrown", 0, 0, ({ \
          "right", 0, 0, ({ }), \
          "left", 0, 0, ({ }), \
        }), \
        "bow", 0, 0, ({ \
          "long", 0, 0, ({ }), \
          "short", 0, 0, ({ }), \
          "cross", 0, 0, ({ }), \
        }), \
        "sling", 0, 0, ({ }), \
     }), \
     "rope", 0, 0, ({ }), \
  }), \
  "con", 0, 0, ({ \
     "hpbonus", 0, 0, ({ }), \
     "bp", 0, 0, ({ }), \
     "systemshock", 0, 0, ({ }), \
     "endurance", 0, 0, ({ }), \
     "poisonresistance", 0, 0, ({ }), \
  }), \
  "int", 0, 0, ({ \
     "perception", 0, 0, ({ }), \
     "resist_illusion", 0, 0, ({ }), \
     "spells", 0, 0, ({ \
       "protect", 0, 0, ({ }), \
       "summon", 0, 0, ({ }), \
       "enchant", 0, 0, ({ }), \
       "divine", 0, 0, ({ }), \
       "necromancy", 0, 0, ({ }), \
       "illusion", 0, 0, ({ }), \
       "alter", 0, 0, ({ }), \
       "invoke", 0, 0, ({ }), \
     }), \
     "items", 0, 0, ({ \
       "rod", 0, 0, ({ }), \
       "staff", 0, 0, ({ }), \
       "wand", 0, 0, ({ }), \
       "scroll", 0, 0, ({ }), \
       "potion", 0, 0, ({ }), \
     }), \
     "languages", 0, 0, ({ }), \
     "occult", 0, 0, ({ \
       "chant", 0, 0, ({ }), \
       "brew", 0, 0, ({ }), \
       "dance", 0, 0, ({ }), \
     }), \
     "spellcraft", 0, 0, ({ }), \
     "appraise", 0, 0, ({ \
       "art", 0, 0, ({ }), \
       "gems", 0, 0, ({ }), \
       "monster", 0, 0, ({ }), \
       "treasure", 0, 0, ({ }), \
       "weapon", 0, 0, ({ }), \
       "armour", 0, 0, ({ }), \
       "jewelry", 0, 0, ({ }), \
       "depth", 0, 0, ({ }), \
     }), \
  }), \
  "wis", 0, 0, ({ \
     "spells", 0, 0, ({ \
       "cure", 0, 0, ({ }), \
       "protect", 0, 0, ({ }), \
       "animal", 0, 0, ({ }), \
       "combat", 0, 0, ({ }), \
       "charm", 0, 0, ({ }), \
       "elemental", 0, 0, ({ }), \
       "summon", 0, 0, ({ }), \
       "weather", 0, 0, ({ }), \
       "elemental", 0, 0, ({ }), \
       "divine", 0, 0, ({ }), \
       "travel", 0, 0, ({ }), \
       "necromancy", 0, 0, ({ }),\
       "create", 0, 0, ({ }), \
     }), \
     "items", 0, 0, ({ \
       "rod", 0, 0, ({ }), \
       "staff", 0, 0, ({ }), \
       "wand", 0, 0, ({ }), \
       "scroll", 0, 0, ({ }), \
       "potion", 0, 0, ({ }), \
     }), \
     "resist_enchant", 0, 0, ({ }), \
     "firstaid", 0, 0, ({ }), \
     "spellcraft", 0, 0, ({ }), \
     "religion", 0, 0, ({ }), \
     "tracking", 0, 0, ({ }), \
     "hunting", 0, 0, ({ }), \
     "fishing", 0, 0, ({ }), \
  }), \
  "cha", 0, 0, ({ \
     "loyalty", 0, 0, ({ }), \
     "persuation", 0, 0, ({ }), \
     "artistic", 0, 0, ({ }), \
     "song", 0, 0, ({ }), \
     "disguise", 0, 0, ({ }), \
  }), \
}) 
