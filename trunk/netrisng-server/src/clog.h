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

#include <fstream>
#include <iostream>
#include <string>

#include "cdate.h"

using namespace std;

class cWarnLevel
{
   public:
	short m_level; // 0 - k, 1 - warn, 2 - fatal
	inline cWarnLevel(short level): m_level(level) {} 
	cWarnLevel(){}
	inline void set(int level);
	cWarnLevel operator=(int level) {m_level=level;}
	inline char * operator()() 
	{
		if (m_level==0) return "[ + ] ";
		if (m_level==1) return "[ - ] ";
		if (m_level==2) return "[ F ] ";		
	} 
};
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
inline void cWarnLevel::set(int level)
{
	m_level=level;
} 
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
class cLog 
{
   public:
   	cLog(char* filename);
    	~cLog();
    
     cLog& operator << (const std::string& input);
    	cLog& operator << (int input);
   	cLog& operator << (char input);
   	cLog& operator << (float input);
    	cLog& operator << (bool input);
    	cLog& operator << (char* input);
    	cLog& operator << (cWarnLevel input);     
    
   private:
	char* logFile;
    	std::string tmp;
    	std::ofstream fileStream;
	cDate date;	    
	
    	void doClosing(void);
	string itoa(int n);
};


