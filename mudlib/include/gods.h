/* Some stuff to keep track of gods so we can centralize. */
#define GOD_LIST ({"baldrick","timion","virga","taniwha","hokemj",\
                   "cyrcia","bivins","ducky","grimbrand","none"})
                   
#define GODS   ([  "baldrick" : 1 , "timion" : 1 , "virga" : 2 ,\
                   "taniwha" : 1 , "hokemj" : 1 , "cyrcia" : 2 ,\
                   "bivins" : 1 , "ducky" : 1, "grimbrand" : 1 ,\
                   "none" : 1\
               ])

/* Things that may be sacrificed to a given god. */
/* NOTE TO ME:  make corpses good/evil/neutral */
/*              same with decrapitated heads */
/*              Add FOOD as a choice          */
/* Taniwha, hokemj should include FOOD later */
#define SAC_ITEMS ([  "baldrick"  : ({ "armours", "weapons", "items", "money",\
                                       "corpses", "experience" })\
                    , "timion"    : ({ "weapons", "armours" })\
                    , "virga"     : ({ "money", "corpses" })\
                    , "taniwha"   : ({ "weapons", "items" })\
                    , "hokemj"    : ({ "items", "money" })\
                    , "cyrcia"    : ({ "corpses", "items" })\
                    , "bivins"    : ({ "items", "money" })\
                    , "ducky"     : ({ "corpses", "experience" })\
                    , "grimbrand" : ({ "corpses", "weapons" })\
                    , "none"      : ({ })\
                  ])

/* Need to have a list of races to index on in some code. */
#define RACES ({"drow","duergar","dwarf","elf","gnome","goblin","halfling",\
                "half-elf","half-orc","human","lizard-man","orc"})
                
/* gods each race is allowed to worship along with the 'sacrifice modifier'
   associated (it's a percent).
*/                  
#define ALLOWED_GODS ([  "drow"       : ({ "cyrcia", 125, "bivins", 75,    \
                                           "ducky", 75 })                  \
                       , "duergar"    : ({ "grimbrand", 125, "ducky", 90,  \
                                           "cyrcia", 75 })                 \
                       , "dwarf"      : ({ "virga", 125, "timion", 90,     \
                                           "taniwha", 90 })                \
                       , "elf"        : ({ "hokemj", 125, "taniwha", 90,   \
                                           "bivins", 90 })                 \
                       , "gnome"      : ({ "taniwha", 125, "virga", 95,    \
                                           "baldrick", 90 })               \
                       , "goblin"     : ({ "ducky", 125, "grimbrand", 90,  \
                                           "cyrcia", 75 })                 \
                       , "halfling"   : ({ "bivins", 125, "hokemj", 90,    \
                                           "baldrick", 90 })               \
                       , "half-elf"   : ({ "taniwha", 105, "hokemj", 95,   \
                                           "baldrick", 95, "virga", 85,    \
                                           "timion", 90 })                 \
                       , "half-orc"   : ({ "timion", 110, "grimbrand", 90, \
                                           "ducky", 95, "baldrick", 95 })  \
                       , "human"      : ({ "baldrick", 100, "taniwha", 100,\
                                           "ducky", 100, "timion", 100,    \
                                           "bivins", 100, "virga", 100,    \
                                           "hokemj", 100, "grimbrand", 100,\
                                           "cyrcia", 75 })                 \
                       , "lizard-man" : ({ "baldrick", 120, "timion", 90,  \
                                           "bivins", 90 })                 \
                       , "orc"        : ({ "ducky", 125, "grimbrand", 80,  \
                                           "cyrcia", 75 })                 \
                     ])

/* This is the multiplier that gets done to the sacrifice value when it's
   being sent to adjust_god_status().  Taniwha understands.
*/                     
#define STATUS_MULT 2
