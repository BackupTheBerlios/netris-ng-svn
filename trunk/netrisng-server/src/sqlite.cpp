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
using namespace std;
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::read_db()
{	
	rc = sqlite3_open("/home/senu/database.db", &db);
	if( rc )
	{
     	*log << "Couldn't open database" << E;
		die();      	
	}
  	else
    	  	*log << "Opened database" << G;  
     
	curr_row=0;
     rc = sqlite3_exec(db, "select * from users", callback, 0, &zErrMsg);
     if( rc!=SQLITE_OK )
	{
         *log <<  "SQL error: "<< zErrMsg << E;
	    die();
     }
	*log << "Read " << curr_row << "users" << G;
	curr_row=0;
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
string cServer::get_passwd(string login)
{	
	curr_row=0;
	
	query="select passwd from users where login='"+login+"'";
     
	rc = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);
     if( rc!=SQLITE_OK )
	{
         *log <<  "SQL error: "<< zErrMsg << E;
	    return "-1";
     }
	if(curr_row==0)
		return "-1";
	curr_row=0;
	return result[0][0];
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::read_user(string login)
{	
	*debug << "Reading user " << login <<" from db" << G; 
	curr_row=0;
	
	query="select * from users where login='"+login+"'";
	
     rc = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);
     if( rc!=SQLITE_OK )
	{
         *log <<  "SQL error: "<< zErrMsg << E;
	    // do not allow client to connect
     }
	*log << "Read user " << login << " from db" << G;	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
int cServer::get_user_id(string login)
{	
	curr_row=0;
	
	query="select key from users where login='"+login+"'";
     
	rc = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);
     if( rc!=SQLITE_OK )
	{
         *log <<  "SQL error: "<< zErrMsg << E;
		return 0;
     }
	if(curr_row==0)
		return 0;
	curr_row=0;
	return atoi(result[0][0].c_str());
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
