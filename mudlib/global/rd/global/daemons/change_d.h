#ifndef _change_d_h
#define _change_d_h

#define ALLOWED_DIRS ([ "secure":1, "global":1, "d":1, "std":1, "net":1, "obj":1, "include":1, "doc":1 ])
#define LOG_DIR "/log/changes"
#define SAVE_PATH "/global/daemons/save/change_d"
#define NUM_CHANGES 10
#define NEW_LINES write( "\n\n" )
#define BLUE "%^BLUE%^"
#define RED "%^RED%^"
#define RESET "%^RESET%^"
#define GREEN "%^GREEN%^"
#define ARR_FIX(x) x[0..1] = ({ })

#endif /* _change_d_h */
