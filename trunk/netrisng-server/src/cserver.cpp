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

#include "cserver.h"
#include <algorithm>

#define dbg

using namespace std;

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
string cServer::result[100][100];
int cServer::curr_row=0;
int cServer::columns=0;
//string cServer::test;

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::publicate_game(cGame *newgame)
{
	//games.insert(newgame);
	


}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
int cServer::get_next_free_game_id()
{
	// O(0) time, could be O(log(n)) time but i think it doesnt need to have smallest && free id

	return 1;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
bool cServer::auth(string login, string passwd)
{
	int user_id = get_user_id(login);
	if (user_id==0)
		return false;
	if(users.find(user_id)!=NULL)	
 		return false;
	if (passwd==get_passwd(login) && passwd!="-1")
		return true;
	return false;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::create_game(cUser *user, bool is_anticounter, bool is_gravity, bool is_rated,
					 bool is_shownext, int speed, string desc)
{
	cDate created;
	created.get_time();
	int id = get_next_free_game_id();
	cGame * newgame = new cGame(created, user, id, speed, is_anticounter, is_gravity, is_rated, is_shownext, desc);
	games.insert(*newgame);
	publicate_game(newgame);
	
	*log << "Created game id: " << id << " by user: " << user->name << G;
	
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::set_motd(string newmotd)
{
	motd=newmotd;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::die()
{
	*log << "Die!" << E;	
	*log  << "Saving db" << G;
	sqlite3_close(db);
	*log  << "Closing sockets" << G;
	close(server_socket);		
	
	users.dfs();
	int rs=users.rs;
	
	for(int i=0; i<rs; i++)
	{
		remove_user(users.result[i]->fd);
	}
	
	
	//save unsaved games
	exit(0);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
cServer::cServer(cLog *tmplog, cLog * tmplog2)

{
	log=tmplog;
#ifdef dbg	
	debug = tmplog2;
#endif	 	
 	G.set(0); W.set(1); E.set(2); 
	
	// WARNING
	// some things are initiated in read_config
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
cServer::~cServer()
{
	//


}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::accept_user(string login, int fd)
{
	
	cUser * user = user_fds.find(fd);
	//from db
	read_user(login);
	user->id=atoi(result[0][0].c_str());
	user->name=login;
	user->stats.division=0;
	user->stats.won=atoi(result[0][3].c_str());
	user->stats.loss=atoi(result[0][4].c_str());	
	user->authorized=true;	
	
	users.insert(user->id,user);
	active_users.insert(user->id,user);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::create_user(string login, string ip, int fd)
{
	
 	cUser *user = new cUser;
	cDate date;
	date.get_time();
	
	user->game=0;
	user->authorized=false;	
	user->ip=ip;
	user->fd=fd;	
	user->joined=date;
	
	

	

	
	//read_messages	
	
	curr_row=0;
	
	
	user_fds.insert(user->fd, user);
	
	n_users++;
	
	
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::remove_leading_spaces(string &line)
{
	while(line[0]==' ' || line[0]=='\t')
	{
		line.erase(line.begin());
	}
	

}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::remove_trailing_spaces(string &line)
{	
	int len=line.size()-1;
	while(line[len]==' ' || line[len]=='\n' || line[len]=='\t')
	{
		line.erase(len,1);
		len=line.size()-1;		
	}
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::printf_users()
{
	users.dfs();
	int rs=users.rs;
	for(int i=0; i<rs; i++)
	{
		*debug << users.result[i]->name << W;
	}
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::read_config()
{
	*log << "Reading config file" << G;
   	
	FILE * cfg = fopen("/home/senu/.netrisng-dc.rc", "r");
	string line="";
	string name, value;
	int n;
	
	const int MAXLINE = 299;
	char buff[300]	;
	
	if (cfg==NULL)	
	{	
		*log << "Could not load config file" << E;
		die();
	}
	
		
	while(!feof(cfg))
	{
		strcpy(buff, "");
		fgets(buff,MAXLINE,cfg);
		line=buff;
		remove_leading_spaces(line);
		remove_trailing_spaces(line);
		
		if(line[0]!='#')
		{
			n=line.find('=');
			
			if(n>0) // there is =
			{
				name.assign(line, 0, n);
				value.assign(line, n+1, line.size()-1);
#ifdef dbg		
				*debug << "Read key: " << name << " = " << value << W;
#endif
				//	
				// identify
				//
				if(name == "maxusers") 
					max_users=atoi(value.c_str());
				else if(name=="MOTD")
					motd=value;
				else if(name=="name")
					name=value;
				else if(name=="version")
					version=value;
			}
		
		}	


	}
	
	for(int i=1; i<=80; i++)
	{
		free_ids.push_back(i);
	}	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::term(int sig)
{
	*log << "Terminating server. Called by cServer::close()" << E;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::remove_user(int fd)
{	
	cUser * user = user_fds.find(fd);
	if(user!=NULL)
	{
		*debug << "User " << user->ip << " has left" << W;
	///send all that he has left
	
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
#ifdef dbg	
	int tmp=
#endif	
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
#ifdef dbg	
//	printf("\n%d",tmp);
//	perror("");
#endif		
	user_fds.erase(fd);
	users.erase(user->id);
	active_users.erase(user->id);
	}
	
	close(fd);
	
	delete user;
	n_users--;
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


