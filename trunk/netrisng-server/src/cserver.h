/***************************************************************************
 *   Copyright (C) 2005 by senu                                            *
 *   senu@o2.pl                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <set>
#include <signal.h>

#include <arpa/inet.h>
#include <sys/socket.h>
//#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
//#include <netdb.h> 
#include <sys/epoll.h>
//#include <signal.h>
#include <string.h>
#include <errno.h> 


#include "RBTree.h"
#include "cgame.h"

#include "sqlite.h"
#define dbg

using namespace std;
	

class cServer
{
   public:
   	string name;
	string version;
	string motd;
	int n_users;
	int n_games;
	int max_users;
	int n_registered_users;
	
	cServer(cLog*, cLog*);
	~cServer();
	
	bool auth(string, string);
	void accept_user(string, int);		
	void term(int);
	void reboot(int);
	void read_config();	 
	void read_messages(int);
	void read_db();
	void die();
	void create_user(string, string, int); // create new cUser and add to users
	void printf_users(); // debug
	void start();
	void main_loop();
	//should be protected
// 	set <pcUser,f_sort_users> users;
// 	set <pcUser,f_sort_users> active_users;
	
	RB_Tree users;
	RB_Tree active_users;
	RB_Tree user_fds;

   private:
   	string get_passwd(string);
	int	get_user_id(string);
	void set_motd(string);
	void reject(string, string);		
	void create_game(cUser*, bool, bool, bool, bool, int, string);
	void connect_to_game(cUser *, cGame);
	void close_game(cUser *);
	cUser * get_user_by_name(string);
	cUser * get_user_by_id(int);
	void kick(int);
	void new_user(string, string); // add new to db
	void remove_user(int);
	void ban(int);
	void say(int,string);
	void say_to(int, int, string);
	int get_next_free_game_id();
	void publicate_game(cGame *);
	void read_user(string);
	void decode(int, int, int);	
		
   
   protected:
	//static int callback(void *, int, char **, char **);  
	//static int callback(void *NotUsed, int argc, char **argv, char **azColName);   	
	
	set <cGame> games;
	list <int> free_ids;
	
	cUser * tmp_user;
  	
	int server_socket, client;
	struct sockaddr_in	server_address; 
	struct sockaddr_in 	client_address; 
	struct epoll_event ev, events[50];
	size_t client_size; 
	
	int epollfd;
	
	sqlite3 *db;		    
     char *zErrMsg;
     int rc, len;
	string query;
	string message;
	char buff[260];	
	size_t n; 		
	
	static string result[100][100];
	static int curr_row;
	static int columns;	
     static int callback(void *NotUsed, int argc, char **argv, char **azColName)
	{
       	NotUsed=0;
       	columns=argc;       	
       	for(int i=0; i<argc; i++)
		{
			result[curr_row][i].assign(argv[i]);
       	}      	
		curr_row++;
       	return 0;
     }	
	
	cWarnLevel G,W,E;
	cLog * log;
#ifdef dbg	
	cLog * debug;
#endif	 
	
	
	void remove_trailing_spaces(string&);
	void remove_leading_spaces(string&);
};
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

