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

// grrr i really hate std::set, too much code altering, and ... they arent work 
// err i dont know.. i try to avoid templates... wanan use this implementation ? just
// change just AVL_node... 

#define BLACK		1
#define RED		2

class cUser;
class cServer;
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
class RB_Node
{
   public:
	RB_Node();
	RB_Node(int key, RB_Node* nullnode, cUser * _data);
	RB_Node * successor();	

	RB_Node *	parent;	
	RB_Node *	left;		
	RB_Node *	right;		
	int		key;			
	int		color;  	
	cUser * data;

};
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
class RB_Tree
{
   public:
	RB_Tree();
	~RB_Tree();

	cUser * find(int key);	
	void dfs();
	void insert(int key,cUser *);	
	void erase(int key);			
	int size, rs;
	cUser* result[50]; ///maxusers
	

   protected:
	RB_Node * root;		
	RB_Node * NULLNODE;		
	void deleteRepair(RB_Node* node);	
	void insertRepair(RB_Node* node);	
	RB_Node * rightRotate(RB_Node* p);	
	RB_Node * leftRotate(RB_Node* p);	
	RB_Node * _find(int key);
	void _dfs(RB_Node * v);
	
};
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


