string version()
{
  return "9.18.6-Aurora.thanks.to.chrisy";
}
/* /secure/ftpd... */
#define VERSION version()
/*
 * Originaly written by Pinkfish@Discworld.
 *
 * 93-08-22  Bannor@newmoon
 *           - Added DEBUG and LOGGING flags.
 *           - Fixed a problem with sending files larger then 1k.
 *           - Added support for events.
 *           - Added support for finger ftp.
 *           - Fixed security problems that allowed anyone to read/write
 *             to any directory.
 *           - Improved readability (well, I think so anyway)
 *
 */
#include "ftp.h"
#include "socket.h"
 
 
 
/*
-----------------------------------------------
   debugging defines.
-----------------------------------------------
*/
#define TP_CRE "baldrick"
 
#undef DEBUG
 
#ifdef DEBUG
 
#define TP(STR) if( find_player( TP_CRE ) ) \
                    tell_object( find_player( TP_CRE ), STR )
 
#undef DEBUG_SEND   /* define to debug data_write_callback() */
 
#else
 
#define TP(STR)
#undef DEBUG_SEND
 
#endif
 
 
/*
-----------------------------------------------
   log file defines.
-----------------------------------------------
*/
#define LOGGING
 
#ifdef LOGGING
 
#define LOG_CONNECT /* define to log all connections */
#define LOG_FILE    /* define to log all file xfers */
#define LOG_CD_SIZE /* define to log cd's and file size commands */
 
#else
 
#undef LOG_CONNECT
#undef LOG_FILE
#undef LOG_CD_SIZE
 
#endif
 
 
/*
-----------------------------------------------
   driver version defines.
-----------------------------------------------
*/
#define NEWDRIVER
 
#ifdef NEWDRIVER
#define mud_name() MUD_NAME
#else
#define VERSION version()
#endif
 
 
 
#define CHECK_LOGIN() if( !socket_info[ fd ][ LOGGED_IN ] ) \
                      { \
                        socket_write( fd, "530 Please login with USER and PASS.\n" ); \
                        break; \
                      }
#define UNAME   socket_info[ fd ][ USER_NAME ]
 
 
#define HOME_DIR(NAME) "/w/"+NAME
 
 
/*
-----------------------------------------------
    Variables
-----------------------------------------------
*/
 
mapping socket_info;
int     our_socket;
 
 
 
/*
-----------------------------------------------
    Prototypes
-----------------------------------------------
*/
void    setup_ftp( int port );
void    finish_lookup( string host, string number );
string  get_path( int fd, string str );
 
 
 
mixed *query_connections()
/* returns an array of users connected to ftpd */
{
mixed  *vals;
string *list;
int    count;
 
    list = ({ });
    vals = values( socket_info );
 
    for( count = 0; count < sizeof( vals ); count++ )
    {
        list += ({ capitalize( (string)((vals[ count ])[ USER_NAME ]) ) });
    }
    return list;
 
} /* query_connections() */
 
 
void    create()
{
    seteuid( "Root" );
    socket_info = ([]);
    call_out( "setup_ftp", 2, FTP_PORT );
    call_out( "check_connections", 5 * 60 );
}			/* create() */
 
 
void    setup_ftp( int port )
{
    our_socket = socket_create( STREAM, "in_read_callback", "in_close_callback" );
	if( our_socket < 0 )
	{
	    TP( "Failed to create socket.\n" );
	    return;
	}
	if( socket_bind( our_socket, port ) < 0 )
	{
	    TP( "Failed to bind socket.\n" );
	    socket_close( our_socket );
	    return;
	}
	if( socket_listen( our_socket, "in_listen_callback" ) < 0 )
	{
	    TP( "Failed to listen to socket.\n" );
	    return;
	}
}			/* setup_gopher() */
 
 
void    in_listen_callback( int fd )
{
int     new_fd;
 
	if(( new_fd = socket_accept( fd, "in_read_callback", "in_write_callback" )) < 0 )
	{
	    return;
	}
    socket_info[ new_fd ] = ([]);
    socket_write( new_fd, sprintf( "220 %s FTP server ready.  " +
                  "please login as yourself.\n", mud_name() ) );
}			/* in_listen_callback() */
 
 
string  ls( string path, int column )
{
string *bits;
 
	if( file_size( path ) == -2 )
		if( path[ strlen( path ) - 1 ] == '/' )
		    bits = get_dir( path + "*" );
		else
		    bits = get_dir( path + "/*" );
	else
	    bits = get_dir( path );
	bits -= ({ ".", ".." });
    if( !sizeof( bits ) )
		return "";
	if( column )
	    return implode( bits, "\n" ) + "\n";
    return sprintf( "%-#70s\n", implode( bits, "\n" ) );
}			/* ls() */
 
 
void data_write_callback( int fd )
{
  int pos;
  int length;
  int ret_val;
  string tmp;
 
 
  tmp = "";
  pos = socket_info[ fd ][ POS ];
  length = ((pos + 1024) >= socket_info[ fd ][ LEN ] ) ?
                         (socket_info[ fd ][ LEN ] - pos) : 1024;
#ifdef DEBUG_SEND
  TP( "Entering dwc(), pos: " + pos + " length should be: " + length + ".\n" );
#endif
  socket_info[ socket_info[ fd ][ PARENT_FD ] ][ LAST_DATA ] = time();
  if( socket_info[ fd ][ TYPE ] == STRING )
  {
#ifdef DEBUG_SEND
    TP( "type == STRING\n" );
#endif
    while( socket_write( fd, socket_info[ fd ][ DATA ][ pos..pos + 1024 ] )
           >= 0 )
    {
      pos += 1024;
      if( pos > socket_info[ fd ][ LEN ] )
      {
        socket_write( socket_info[ fd ][ PARENT_FD ],
                      "226 Data transfer complete.\n" );
        socket_close( fd );
        map_delete( socket_info[ socket_info[ fd ][ PARENT_FD ] ], DATA_FD );
        map_delete( socket_info, fd );
#ifdef DEBUG_SEND
        TP( "dwc() compleate, exiting.\n" );
#endif
        return ;
      }
    }
  }
  else
  {
#ifdef DEBUG_SEND
    TP( "type is other then STRING\n" );
#endif
    tmp = read_bytes( socket_info[ fd ][ DATA ], pos, length );
    while( (ret_val = socket_write( fd, tmp )) >= 0 )
    {
      if( ret_val == 0 )
      {
#ifdef DEBUG_SEND
        TP( "Ret_val == 0, continuing\n" );
#endif
        continue;
      }
#ifdef DEBUG_SEND
      TP( "sent from " + pos + " to " + (pos + length) + ".\n" );
      TP( "ret_val was: " + ret_val + ".\n" );
#endif
 
      pos += length;
      if( pos >= socket_info[ fd ][ LEN ] )
      {
        socket_write( socket_info[ fd ][ PARENT_FD ],
                      "226 Data transfer complete.\n" );
        socket_close( fd );
        map_delete( socket_info[ socket_info[ fd ][ PARENT_FD ] ], DATA_FD );
        map_delete( socket_info, fd );
#ifdef DEBUG_SEND
        TP( "dwc() compleate, exiting.\n" );
#endif
        return ;
      }
      length = ((pos + 1024) >= socket_info[ fd ][ LEN ] ) ?
                             (socket_info[ fd ][ LEN ] - pos) : 1024;
      tmp = "";
      tmp = read_bytes( socket_info[ fd ][ DATA ], pos, length );
    }
  }
#ifdef DEBUG_SEND
  TP( "ret_val was: " + ret_val + ".\n" );
  TP( "leaving dwc(), pos: " + pos + ".\n" );
#endif
  socket_info[ fd ][ POS ] = pos;
  if( ret_val == EEWOULDBLOCK )
  {
      /* it would block, so it's up to us to try again */
#ifdef DEBUG_SEND
      TP( "Adding call_out\n" );
#endif
      call_out( "data_write_callback", 2, fd );
  }
  else
      if( find_call_out( "data_write_callback" ) != -1 )
      {
#ifdef DEBUG_SEND
        TP( "Killing callout.\n" );
#endif
        remove_call_out( "data_write_callback" );
      }
} /* data_write_callback() */
 
 
 
 
string  expand_path( string str )
{
}			/* expand_path() */
 
 
void    data_conn( int fd, string mess, string name, int type )
{
int     new_fd, ret;
 
    if( socket_info[ fd ][ DATA_FD ] )
	{
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    return;
	}
    new_fd = socket_create( STREAM, "data_read_callback",
                            "data_close_callback" );
	if( new_fd < 0 )
	{
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    return;
	}
    if( ( ret = socket_connect( new_fd, socket_info[ fd ][ DATA_ADDR ] + " " +
                                socket_info[ fd ][ DATA_PORT ],
                                "data_read_callback",
                                "data_write_callback" )) < 0 )
	{
        TP( "Blue " + socket_info[ fd ][ DATA_ADDR ] + " " +
            socket_info[ fd ][ DATA_PORT ] + "\n" );
	    TP( socket_error( ret ) + "\n" );
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    socket_close( new_fd );
	    return;
	}
    socket_info[ new_fd ] = ([ DATA : mess, POS : 0,
                               PARENT_FD : fd, TYPE : type ]);
	if( type == STRING )
	    socket_info[ new_fd ][ LEN ] = strlen( mess );
	else
	    socket_info[ new_fd ][ LEN ] = file_size( mess );
	socket_info[ fd ][ DATA_FD ] = new_fd;
	socket_write( fd, "150 Opening ASCII mode data connection for " + name +
                  ", " + socket_info[ new_fd ][ LEN ] + " bytes.\n" );
	data_write_callback( new_fd );
}			/* data_conn() */
 
 
void    read_connection( int fd, string path, int append )
{
int     new_fd, ret;
 
	if( socket_info[ fd ][ DATA_FD ])
	{
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    return;
	}
    new_fd = socket_create( STREAM, "data_read_callback",
			   "data_close_callback" );
	if( new_fd < 0 )
	{
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    return;
	}
    if(( ret = socket_connect( new_fd, socket_info[ fd ][ DATA_ADDR ] + " " +
			      socket_info[ fd ][ DATA_PORT ], "data_read_callback",
			      "data_write_callback" )) < 0 )
	{
	    TP( "Blue " + socket_info[ fd ][ DATA_ADDR ] + " " + socket_info[ fd ][ DATA_PORT ] + "\n" );
	    TP( socket_error( ret ) + "\n" );
	    socket_write( fd, "425 Cannot build data connection.\n" );
	    socket_close( new_fd );
	    return;
	}
    socket_info[ new_fd ] = ([ PATH : path, PARENT_FD : fd, DATA : "",
                               TYPE : DOWNLOAD, APPEND : append ]);
    socket_write( fd, "150 Opening ASCII mode data connection for " + path +
		 " " + file_size( path ) + ".\n" );
}			/* read_connection() */
 
 
void    data_read_callback( int fd, string mess )
{
	if( socket_info[ fd ][ TYPE ] != DOWNLOAD )
	    return;
    socket_info[ socket_info[ fd ][ PARENT_FD ]][ LAST_DATA ] = time();
    socket_info[ fd ][ DATA ] += replace_string( mess, "\r\n", "\n" );
}			/* data_read_callback() */
 
 
void    data_close_callback( int fd )
{
	if( socket_info[ fd ][ TYPE ] == DOWNLOAD )
	{
		if( !socket_info[ fd ][ APPEND ])
		    rm( socket_info[ fd ][ PATH ]);
	    write_file( socket_info[ fd ][ PATH ], socket_info[ fd ][ DATA ]);
	    socket_write( socket_info[ fd ][ PARENT_FD ],
			 "226 Data transfer successfuly completed.\n" );
	}
    map_delete( socket_info, fd );
}			/* data_close_callback() */
 
 
void    logout( int fd )
{
string name;
 
    name = socket_info[ fd ][ USER_NAME ];
    event( users(), "inform", name + " logged out of ftpd", "ftp" );
 
#ifdef LOG_CONNECT
    log_file( "ftpd.log", name + " logged out at " + ctime( time() ) + ".\n" );
#endif
 
    map_delete( socket_info[ fd ], USER_NAME );
    map_delete( socket_info[ fd ], LOGGED_IN );
    map_delete( socket_info[ fd ], CWD );
}			/* logout() */
 
 
void    parse_comm( int fd, string str )
{
string *bits, tmp;
int     port, i;
 
    TP( "Parseing " + str + ".\n" );
    bits = explode( str, " " );
    socket_info[ fd ][ LAST_DATA ] = time();
    switch( lower_case( bits[ 0 ] ) )
    {
        case "port":
                bits = explode( implode( bits[ 1..1000 ], " " ), "," );
                if( sizeof( bits ) < 6 )
                    socket_write( fd, "550 Failed command.\n" );
                else
                {
                    socket_info[ fd ][ DATA_ADDR ] = implode( bits[ 0..3 ], "." );
                    sscanf( bits[ 4 ], "%d", i );
                    port = i << 8;
                    sscanf( bits[ 5 ], "%d", i );
                    port += i;
                    socket_info[ fd ][ DATA_PORT ] = port;
                    socket_write( fd, "200 PORT command successful.\n" );
                }
                break;
        case "user":
                if( socket_info[ fd ][ LOGGED_IN ] )
                    logout( fd );
                if( !LOGIN_OB->test_creator( bits[ 1 ] ) )
                    socket_write( fd, "530 User " + bits[ 1 ] + " access denied.\n" );
                else
                {
                    socket_write( fd, "331 Password required for " + bits[ 1 ] + ".\n" );
                    socket_info[ fd ][ USER_NAME ] = bits[ 1 ];
                }
                break;
        case "pass":
                if( socket_info[ fd ][ LOGGED_IN ] ||
                   !socket_info[ fd ][ USER_NAME ] )
                {
                    socket_write( fd, "503 Log in with user first.\n" );
                    break;
                }
                if( !LOGIN_OB->test_password( socket_info[ fd ][ USER_NAME ],
                             bits[ 1 ]))
                {
                    socket_write( fd, "530 Login incorrect.\n" );
                    map_delete( socket_info[ fd ], USER_NAME );
                }
                else
                {
                    socket_info[ fd ][ LOGGED_IN ] = 1;
                    socket_info[ fd ][ CWD ] = HOME_DIR( socket_info[ fd ][ USER_NAME ] );
                    event( users(), "inform", socket_info[ fd ][ USER_NAME ] +
                           " connected to ftpd", "ftp" );
 
#ifdef LOG_CONNECT
                    log_file( "ftpd.log", UNAME + " connected at " +
                              ctime( time() ) + ".\n" );
#endif
 
                    if( file_size( socket_info[ fd ][ CWD ] ) != -2 )
                    {
                        socket_write( fd, "230 Cannot cd to home.  Logging in with dir=/\n" );
                        socket_info[ fd ][ CWD ] = "/";
                    }
                    else
                        socket_write( fd, "230 User " + socket_info[ fd ][ USER_NAME ] +
                             " logged in successfully.\n" );
                }
                break;
        case "allo":
                socket_write( fd, "201 ALLO command ignored.\n" );
                break;
        case "noop":
                socket_write( fd, "200 NOOP operation successful.\n" );
                break;
        case "retr":
                CHECK_LOGIN();
                tmp = get_path( fd, bits[ 1 ] );
                if( file_size( tmp ) < 0 ||
                    !MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ],
                                         "read_file" ))
                {
                    socket_write( fd, "550 Permison denied reading " +
                                  bits[ 1 ] + ".\n" );
                }
                else
                {
#ifdef LOG_FILE
                    log_file( "ftpd.log", UNAME + " retr " + tmp +
                              " at " + ctime( time() ) + ".\n" );
#endif
                    data_conn( fd, tmp, bits[ 1 ], FILE );
                }
                break;
        case "stor":
                CHECK_LOGIN();
                tmp = get_path( fd, bits[ 1 ] );
                if( MASTER->valid_write( tmp, socket_info[ fd ][ USER_NAME ],
                    "write_file" ) )
                {
#ifdef LOG_FILE
                    log_file( "ftpd.log", UNAME + " stor " + tmp +
                              " at " + ctime( time() ) + ".\n" );
#endif
                    read_connection( fd, tmp, 0 );
                }
                else
                {
                    socket_write( fd, "553 Permision denied to " + bits[ 1 ] +
                                  ".\n" );
                }
                break;
        case "appe":
                /* append... */
                CHECK_LOGIN();
                tmp = get_path( fd, bits[ 1 ] );
                if( MASTER->valid_write( tmp, socket_info[ fd ][ USER_NAME ],
                                         "write_file" ) )
                {
#ifdef LOG_FILE
                    log_file( "ftpd.log", UNAME + " appe " + tmp +
                              " at " + ctime( time() ) + ".\n" );
#endif
                    read_connection( fd, tmp, 1 );
                }
                else
                {
                    socket_write( fd, "553 Permision denied to " + bits[ 1 ] +
                                  ".\n" );
                }
                break;
 
#if 0
                /* Supposed to return modified time in the format: YYYYMMDDHHMMSS */
        case "mdtm":
                CHECK_LOGIN();
                tmp = get_path( fd, bits[ 1 ] );
                if( MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ], "file_size" ))
                {
                    if( file_size( tmp ) == -2 )
                        socket_write( fd, "550 " + tmp + " not a plain file.\n" );
                    else
                        if( file_size( tmp ) == -1 )
                            socket_write( fd, "550 " + tmp + " does not exist.\n" );
                        else
                        {
                        mixed  *junk;
 
                            junk = stat( tmp );
                            socket_write( fd, "215 " + file_size( tmp ) + "\n" );
                        }
                }
                else
                {
                    socket_write( fd, "550 Permision denied to " + bits[ 1 ] + ".\n" );
                }
                break;
#endif
 
        case "size":
                CHECK_LOGIN();
                tmp = get_path( fd, bits[ 1 ] ) ;
                if( MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ], "file_size" ) )
                {
                    if( file_size( tmp ) == -2 )
                        socket_write( fd, "550 " + tmp + " not a plain file.\n" );
                    else
                        if( file_size( tmp ) == -1 )
                            socket_write( fd, "550 " + tmp +
                                          " does not exist.\n" );
                        else
                        {
#ifdef LOG_CD_SIZE
                            log_file( "ftpd.log", UNAME + " size " + tmp +
                                      " at " + ctime( time() ) + ".\n" );
#endif
                            socket_write( fd, "215 " + file_size( tmp ) + "\n" );
                        }
                }
                else
                {
                    socket_write( fd, "550 Permision denied to " +
                                  bits[ 1 ] + ".\n" );
                }
                break;
        case "nlst":
                CHECK_LOGIN();
                /* Send name list. */
                if( sizeof( bits ) > 1 )
                    tmp = get_path( fd, bits[ 1 ] );
                else
                    tmp = socket_info[ fd ][ CWD ];
                if( MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ],
                    "read_file" ) )
                {
                        data_conn( fd, ls( tmp, 1 ), "ls", STRING );
                }
                else
                {
                    socket_write( fd, "550 Permision denied to " +
                                  tmp + ".\n" );
                }
                break;
        case "list":
                CHECK_LOGIN();
                /* This does an ls... aka "dir" */
                if( sizeof( bits ) > 1 )
                    tmp = get_path( fd, bits[ 1 ] );
                else
                    tmp = socket_info[ fd ][ CWD ];
                if( MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ],
                    "read_file" ) )
                {
                    data_conn( fd, ls( tmp, 0 ), "ls", STRING );
                }
                else
                {
                    socket_write( fd, "550 Permision denied to " +
                                  tmp + ".\n" );
                }
                break;
        case "pwd":
                CHECK_LOGIN();
                socket_write( fd, "257 \"" + socket_info[ fd ][ CWD ] +
                              "\" is the current directory.\n" );
                break;
        case "cdup":
                bits[ 1 ] = "..";
        case "cwd":
                CHECK_LOGIN();
                if( sizeof( bits ) > 1 )
                    tmp = get_path( fd, bits[ 1 ] );
                else
                    tmp = socket_info[ fd ][ CWD ];
                if( MASTER->valid_read( tmp, socket_info[ fd ][ USER_NAME ],
                    "cwd" ) )
                {
#ifdef LOG_CD_SIZE
                    log_file( "ftpd.log", UNAME + " cd to " + tmp +
                              " at " + ctime( time() ) + ".\n" );
#endif
                    socket_info[ fd ][ CWD ] = get_path( fd, tmp );
                    socket_write( fd, "250 CWD command successful.\n" );
                }
                else
                {
                    socket_write( fd, "550 " + tmp + ": No such file " +
                                  "or directory.\n"  );
                }
                break;
        case "quit":
                socket_write( fd, "221 Goodbye, and good luck :)\n");
                event( users(), "inform", socket_info[ fd ][ USER_NAME ] +
                       " quit ftpd", "ftp" );
#ifdef LOG_CONNECT
                log_file( "ftpd.log", UNAME + " logged out at " +
                          ctime( time() ) + ".\n" );
#endif
                socket_close( fd );
                map_delete( socket_info, fd );
                break;
        case "type":
                if( bits[ 1 ] != "A" )
                    socket_write( fd, "504 Type " + bits[ 1 ] +
                                  " not implemented.\n" );
                else
                    socket_write( fd, "200 Type set to A.\n" );
                break;
        case "stat":
                socket_write( fd, "211 FTP server status: " + mud_name() +
                              " " + VERSION + "\n" );
                socket_write( fd, "     Connected to " +
                              socket_address( fd ) + "\r\n" );
                if( socket_info[ fd ][ LOGGED_IN ] )
                    socket_write( fd, "    Logged in as " +
                                  socket_info[ fd ][ USER_NAME ] + "\r\n" );
                else
                    if( socket_info[ fd ][ USER_NAME ] )
                        socket_write( fd, "    Waiting for password.\r\n" );
                    else
                        socket_write( fd, "    Waiting for user name.\r\n" );
                socket_write( fd, "    TYPE: ASCII, FORM: Nonprint; STRUcture: " +
                              "File; transfer MODE: Stream.\r\n" );
                if( socket_info[ fd ][ DATA_FD ] )
                    socket_write( fd, "    Data connection open.\r\n" );
                else
                    if( socket_info[ fd ][ DATA_ADDR ] )
                        socket_write( fd, "    " +
                                      socket_info[ fd ][ DATA_ADDR ]
                                      + " " +
                                      socket_info[ fd ][ DATA_PORT ] +
                                      "\r\n" );
                    else
                        socket_write( fd, "    No data connection.\r\n" );
                socket_write( fd, "211 End of status.\n" );
                break;
        case "abor":
                /* Abort...  Handle this with blue stuff,
                 * stops recvs and stors. I guess thats
                 * what it is supposed to do. */
                socket_write( fd, "225 ABOR command successful.\n" );
                if( socket_info[ fd ][ DATA_FD ] )
                {
                    socket_close( socket_info[ fd ][ DATA_FD ] );
                    map_delete( socket_info, fd );
                }
                break;
        case "syst":
                socket_write( fd, "215 MUD Type: Discworld version 42.0\n" );
            break;
        default:
            socket_write( fd, "500 '" + bits[ 0 ] + "' command unrecognised.\n" );
            break;
        }
}			/* in_read_callback() */
 
 
 
void    in_read_callback( int fd, string str )
{
string *bits;
int     i;
 
    str = replace_string( str, "\r", "" );
    bits = explode( str, "\n" );
	for( i = 0; i < sizeof( bits ); i++ )
	    parse_comm( fd, bits[ i ]);
}			/* in_read_callback() */
 
 
 
void    in_close_callback( int fd )
{
    map_delete( socket_info, fd );
    socket_close( fd );
}			/* in_close_callback() */
 
 
 
string  get_path( int fd, string str )
{
string *array, *array1, temp, temp1;
int     i, j;
 
 
    if( !str || str == "" )
    {
        /* no change of dir */
        return socket_info[ fd ][ CWD ];
    }
 
    if( str == "~" )
	{
        /* change to home dir */
        str = HOME_DIR( socket_info[ fd ][ USER_NAME ] );
	}
	else
	{
		if( str[ 0 ] == '~' )
		{
			if( str[ 1 ] == '/' )
			{
			    sscanf( str, "~%s", temp );
                str = HOME_DIR( socket_info[ fd ][ USER_NAME ] ) + temp;
			}
			else
			{
            string  name;
 
				if( sscanf( str, "~%s/%s", name, str ) != 2 )
				{
				    name = extract( str, 1 );
				    str = HOME_DIR( name );
				}
				else
				    /* cheat at this point and just assume they are a wizard. sigh
                     * i know i know */
				    str = HOME_DIR( name ) + "/" + str;
			}
		}
		else
			if( str[ 0 ] != '/' )
			    str = socket_info[ fd ][ CWD ] + "/" + str + "/";
		if( str == "/" )
		    return "/";
		else
		    array = explode( str, "/" ) - ({ "" });
		    for( i = 0; i < sizeof( array ); i++ )
			    if( array[ i ] == ".." )
			    {
				    if( i < 1 )
                        return "/";
				    if( i == 1 )
                        array1 = ({ "." });
				    else
                        array1 = array[ 0..i - 2 ];
					if( i + 1 <= sizeof( array ) - 1 )
					    array1 += array[ i + 1..sizeof( array ) - 1 ];
                    array = array1;
                    i -= 2;
			    }
			    else
				    if( array[ i ] == "." )
					array[ i ] = 0;
		    if( array )
                str = implode( array, "/" );
		    else
                str = "";
	}
	return "/" + str;
}			/* get_path() */
 
 
void    check_connections()
{
int    *bits;
int     i;
 
    bits = keys( socket_info );
	for( i = 0; i < sizeof( bits ); i++ )
		if( socket_info[ bits[ i ]][ LAST_DATA ] > time() + 900 )
		{
		    socket_close( bits[ i ]);
		    map_delete( socket_info, bits[ i ]);
		}
}			/* check_connections() */
 
