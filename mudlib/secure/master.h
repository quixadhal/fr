// Defines for /secure objects, and possible dom and cre master.c's
// 1 june 93 Chrisy

#ifdef VERSION
#define version() VERSION
#endif


// Objects

#define MASTER "/secure/master"
#define SIMUL "/secure/simul_efun"
#define ACCESS "secure/bastards"
#define FTPACC "secure/ftp_access"

 /* Positions */
#define LORD 1
#define HIGH_LORD 2

   /* Masks */
#define READ_MASK 1
#define WRITE_MASK 2
#define GRANT_MASK 4

 // Command positions
#define CREATOR_CMD 1
#define LORD_CMD 2
#define HIGH_LORD_CMD 3
#define GOD_CMD 4
