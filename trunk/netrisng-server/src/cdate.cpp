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

#include "cdate.h"

string cDate::itoa(int n)
{
	string result="";
	while (n!=0)
	{
		result=char(48+n%10)+result;
		n/=10;
	}
	
	return result;
}
void cDate::get_time()
{
  	secs = time (NULL);
	is_set=true;
}

string cDate::print_timestamp()
{
	struct tm * timeinfo = localtime ( &secs );

	string s="";	

     s=itoa(timeinfo->tm_year+1900);
     if (timeinfo->tm_mon<9) 
		s+='0';
	     
	s = s+ itoa(timeinfo->tm_mon+1);
	
	if (timeinfo->tm_mday<9) 
		s+='0';	 
		
	s=s + itoa(timeinfo->tm_mday) + "::";
	
	if (timeinfo->tm_hour<9) 
		s+='0';	 
	s=s+itoa(timeinfo->tm_hour);  
	
	if (timeinfo->tm_min<9) 
		s+='0';	 
	s=s+itoa(timeinfo->tm_min);
	return s;
}
