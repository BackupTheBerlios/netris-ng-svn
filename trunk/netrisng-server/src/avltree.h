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
// change just AVL_node
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
class cUser;

typedef cUser* element;

struct AVL_Node 
{   
   	int key;
   	element data;
   	AVL_Node 		*parent,
   				*left, 
				*right;
			
   	char factor; //byte
};
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- s
class AVL_Tree 
{
   public:
   	AVL_Tree();
   	void insert(int key, cUser * data);
	void erase(int key);
	element find(int key);  
	void dfs();   
	int size;
	
   private:
   protected: 	
   	AVL_Node *root;   
	AVL_Node *tmp;   
	AVL_Node *K1, *K2, *K3, *newnode;   
	cUser * tmpdata;
	bool h;
	
	inline int height(AVL_Node * pos) const; 	
	inline int max(int a, int b) const;
	
	AVL_Node * singleRotateLeft(AVL_Node *K2);
	AVL_Node * singleRotateRight(AVL_Node *K2);
	
	AVL_Node * doubleRotateLeft(AVL_Node *K2);
	AVL_Node * doubleRotateRight(AVL_Node *K2);
	
	AVL_Node * _insert(int key, AVL_Node * node);
	AVL_Node * _erase(int key, AVL_Node * node);
	void _dfs(AVL_Node * v) const;
};
 
