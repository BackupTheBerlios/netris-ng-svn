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


#include "net.h"


#define dbg

void terminate(int sig)
{
	printf("Terminating server. Called by cServer::close()\n");
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	cWarnLevel G(0),W(1),E(2); 
	
	cLog log ("/home/senu/.netrisng-dc");
#ifdef dbg
	cLog debug ("/home/senu/.netrisng-dc-dbg");
	debug << "Entering debug mode" << G;
#endif
	log << ".:: Netris-ng Dedicated server started ::." << W;	
	
	cServer server(&log, &debug);
	
	
	server.read_config();
	server.read_db();

//	signal(SIGTERM, server.term);
	
	ClientSocket::log=&log;
#ifdef dbg	
	ClientSocket::debug=&debug;
#endif
	ClientSocket::server =&server;
	
	
	server.start();
	server.main_loop();	
	
	/*static bool quit = false;

	SocketHandler h;
	ListenSocket<ClientSocket> l(h);

	if (l.Bind(9001))
	{
		exit(-1);
	}
	h.Add(&l);
	h.Select(1,0);
	while (!quit)
	{
		h.Select(1,0);
	}

	
	*/
	log << "Exited normally" << G;
  	return 0;
}

