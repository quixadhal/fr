/*
   This "handler" or "daemon", will handle changes that has
   been made. All the creator will have to do is to report
   it, and it will be logged in a nice way and this daemon
   will be able to answer the last NUM_CHANGES a creator
   have done, or a file have been abused with ;)

   Coded by High Tramser Begosh of Hepp
   
   You can reach me at the following emails :
   begosh@enter.hb.se
    jonas@admin.enter.hb.se
   begosh@unibar.anu.edu.au
   beyond@admin.enter.hb.se
   dat313@utb.shv.hb.se

  1995 Jul 04 Laggard   made multi-user.
                        allow local file names.
                        log changes (to Codechange).
*/

#define VERSION "1.1"
#include "change_d.h"

inherit "/global/more_file.c";

mapping c_fixes = ([]);
mapping f_fixes = ([]);
static mapping userpath = ([]);

/*
   Protos of all functions
*/

void change();
void coder_info( string name );
void create();
void desc_change( string change );
int exit_all();
mixed file_exist( string path );
void file_info( string path );
void full_path( string path );
void menu_choice( string str );
void save();
void show_menu();

/*
**  Function name : create
**
**  Description : This is called in every object when
**        it is created.
**  Input : Nothing
**  Output : Nothing
*/
void create()
{
  seteuid( "Root" );
  restore_object( SAVE_PATH, 1 );
}

/*
**  Function name : file_exist
**
**  Description : Returns true if the file exist
**  Input : Path of the file
**  Output : 0 = no file match; string full file name
*/
mixed file_exist( string path )
{
  string where = this_player()->query_current_path() + "/" + path;

  if ( file_size( where ) < 0 )
  {
    where = path;

    if ( file_size( where ) < 0 )
    {
      write( RED + where + " is not accessible.\n" + RESET );
      return 0;
    }
  }

  if( !(ALLOWED_DIRS[explode( where, "/" )[0]]) )
  {
    write( RED + where + " is not in an permitted directory for logging.\n" + RESET );
    return 0;
  }
  write( RED + "Found " + where + ".\n" + RESET );
  return where;
}

/*
**  Function name : save
**
**  Description : Saves the daemon
**  Input : None
**  Output : None
*/
void save()
{
  write( RED + "Saving data.\n" + RESET );
  save_object( SAVE_PATH, 1 );
}

/*
**  Function name : exit_all
**
**  Description : Exits and saves 
**  Input :
**  Output :
*/
int exit_all()
{
  save();
  NEW_LINES;
  write( GREEN + "Thank you for using the changehandler.\n    Report any bugs to " +
    "High Tramser Begosh of Hepp.\n " + BLUE + "Email: begosh@enter.hb.se\n" + RESET );
  
  return 1;
}


/*
**  Function name : full_path
**
**  Description : Countinues to search for information
**  Input : path of the file
**  Output : none
*/
void full_path( string path )
{
  mixed where = file_exist( path );
  
  if( where )
  {
    write( BLUE + "Write your change, keep it concise.\n" +
      "Changed : " + RESET );
    userpath[this_player()] = where;
    input_to( "desc_change" );
  }
  else
  {
    show_menu();
  }  
}

/*
**  Function name : desc_change
**
**  Description : here we shall describe the change 
**  Input : the change
**  Output : none
*/
void desc_change( string change )
{
  object me = this_player();
  string my_euid = geteuid( me );
  string my_path = userpath[ me ];
  
  if( !change  ||  change == "" )
    write( BLUE + "\nWell then, we return to the main menu instead.\n" + RESET );
  else {
    write( "\n" + GREEN + "Change reported.\n" + RESET );
    if( !c_fixes[my_euid] ) c_fixes[my_euid] = ({});
    if( !f_fixes[my_path] ) f_fixes[my_path] = ({});
    if( sizeof( c_fixes[my_euid] ) > 9 ) ARR_FIX( c_fixes[my_euid] );
    if( sizeof( f_fixes[my_path] ) > 9 ) ARR_FIX( f_fixes[my_path] );                     
    
    c_fixes[ my_euid ] += ({ GREEN + ctime( time() )
                    + RESET + " (" + RED + my_path + RESET + ") "
                    + BLUE + capitalize( change ) + RESET + "\n" });
    f_fixes[ my_path ] += ({ GREEN + ctime( time() )
                    + RESET + " (" + RED + capitalize( my_euid ) + RESET + ") "
                    + BLUE + capitalize( change ) + RESET + "\n" });
    write_file( my_path + ".chlog", ctime( time() )
                    + " [" + capitalize( my_euid ) + "] " + change + "\n" );
    log_file("Codechange",ctime(time())
                    + " : " + my_path
                    + " [" + capitalize( my_euid ) + "] " + change + "\n" );
    save();
  }
  
  show_menu();
}


/*
**  Function name : show_menu
**
**  Description : Shows the menu and accepts input;
**  Input :
**  Output :
*/
void show_menu()
{
  NEW_LINES;
  write( RED + "  --= Changehandler " + VERSION + " =--\n\n" );
  write( BLUE + " a) " + GREEN + "See the " + NUM_CHANGES + " last " +
    "changes a coder has done.\n" );
  write( BLUE + " b) " + GREEN + "See the " + NUM_CHANGES + " last " +
    "changes that has been done on a file.\n" );
  write( BLUE + " c) " + GREEN + "Report a change you have done.\n" );
  write( BLUE + " d) " + GREEN + "Look at a logfile of a file.\n" );
  write( BLUE + " e) " + GREEN + "Exit.\n " );
  write( GREEN + "\n   Enter your choice : " + RESET );

  input_to( "menu_choice" );
}

/*
**  Function name : menu_choice
**
**  Description : This one directs to the right function
**  Input : A choice from the show_menu
**  Output : Nothing
*/
void menu_choice( string str )
{
  if( !str || str == "" ) show_menu();
  
  switch( str ) {
  case "a" :
    write( GREEN + "Name of the coder : " + RESET );
    input_to( "coder_info" );
    break;
  case "b" :
    write( GREEN + "Name of the file : " + RESET );
    input_to( "file_info" );
    break;
  case "c" :
    NEW_LINES;
    write( GREEN + "What file have you changed?\n" +
    "File name : " + RESET );
    input_to( "full_path" );
    break;
  case "d" :
    write( GREEN + "Name of the file : " + RESET );
    input_to( "log_info" );
    break;
  case "e" :
    exit_all();
    break;
  default :
    show_menu();
  }
}

/*
**  Function name : coder_info
**
**  Description : Will show you all the available info of a coder
**  Input : the name of the coder
**  Output : his changes
*/
void coder_info( string name )
{
   
  if( c_fixes[name] )
    write( sprintf( "\n%@s\n", c_fixes[name] ) );
  else 
    write( RED + "\n" + capitalize( name ) + " hasn't done any changes lately. " +
      "Maybe he is lazy.\n" + RESET );

  show_menu();
}

/*
**  Function name : file_info
**
**  Description : Returns information about the changes of the file
**  Input : path of the file
**  Output : none
*/

void file_info( string path )
{
  if( f_fixes[path] ) 
    write( sprintf( "\n%@s\n", f_fixes[path] ) );
  else 
    write( RED + "\nThere haven't been any changes to that file lately.\n" + RESET );

  show_menu();
}


/*
**  Function name : log_info
**
**  Description : This one will more a file.
**  Input : The path
**  Output :
*/
void log_info( string str )
{
  mixed where = file_exist( str + ".chlog" );
  
  if ( where )
    more_file( (string)where );

  show_menu();
}


/*
**  Function name : change
**
**  Description : This doesn't do much ...
**  Input : Nothing really
**  Output : Nothing really
*/
void change()
{
  show_menu();
}




