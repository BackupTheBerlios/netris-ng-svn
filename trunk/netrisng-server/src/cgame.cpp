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

#include "cgame.h"

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
cGame::cGame(cDate _created, cUser* _creator, int _id, int _speed, bool _is_anticounter, bool _is_gravity, bool _is_rated, bool _is_shownext, string _desc)
		  :creator(_creator), speed(_speed), created(_created), id(_id), 
		  is_anticounter(_is_anticounter), is_gravity(_is_gravity),
		  is_rated(_is_rated),is_shownext(_is_shownext), desc(_desc), player(NULL)
{


}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
cGame::cGame()
{


}
