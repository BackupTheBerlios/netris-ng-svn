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
#include "RBTree.h"


//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node::RB_Node(int _key, RB_Node * nullnode, cUser *_data)
			: 	key(_key), 
				parent(nullnode), 
				left(nullnode),
				right(nullnode),				
				color(RED), 
				data(_data)
{
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node::RB_Node()
{	
	parent	= this;
	left		= this;
	right	= this;	
	color	= BLACK;
	data 	= NULL;
	key		= -1;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node* RB_Node::successor()
{
	RB_Node* tmp = this;
	
	if (right != right->right)
	{
		tmp = right;

		while (tmp->left != tmp->left->left)
			tmp = tmp->left;
		return tmp;
	}

	RB_Node* s = tmp->parent;
	while (s != s->left && tmp == s->right)
	{
		tmp = s;
		s = s->parent;
	}

	return s;	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Tree::RB_Tree()
{
	NULLNODE = new RB_Node();
	root = NULLNODE;
	size=0;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Tree::~RB_Tree()
{
	RB_Node* node = root;
	RB_Node* tmp;

	if (root && (root->left || root->right))
	{
		do
		{			
			while (node->left != NULLNODE || node->right != NULLNODE)	
			{
				if (node->left != NULLNODE)
				{
					node = node->left;					
				}
				else	
				{
					node = node->right;
				}
			}

			tmp = node->parent;
			if (node->parent->left == node)
				tmp->left = NULLNODE;
			else							
				tmp->right = NULLNODE;

			delete node;
			node = tmp;
		}
		while (root->left != NULLNODE || root->right != NULLNODE);		
	}

	delete root;
	root = NULL;


	delete NULLNODE;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node * RB_Tree::_find(int key)
{
	RB_Node* node = root;
	
	while (node != NULLNODE && node->key != key)
	{
		if (key < node->key)
			node = node->left;
		else 
			node = node->right;
	}

	return node;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
cUser * RB_Tree::find(int key)
{
	RB_Node* node = root;
	
	while (node != NULLNODE && node->key != key)
	{
		if (key < node->key)
			node = node->left;
		else 
			node = node->right;
	}

	return node->data;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::insert(int key, cUser * data)
{
	RB_Node* node = new RB_Node(key, NULLNODE, data);
	size++;

	RB_Node* p = NULLNODE;
	RB_Node* tmp = root;

	while (tmp != NULLNODE)		
	{
		p = tmp;
		if (node->key < tmp->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	
	node->parent = p;

	if (p == NULLNODE)
	{
		root = node;
	}
	else if (node->key < p->key)	
		p->left = node;
	else
		p->right = node;

	insertRepair(node);	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::insertRepair(RB_Node * node)
{
	RB_Node* uncle;

	while (node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;

			if (uncle->color == RED)				
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else 
			{
				if (node == node->parent->right)	
				{
					node = node->parent;
					leftRotate(node);
				}
					
				node->parent->color = BLACK;		
				node->parent->parent->color = RED;

				rightRotate(node->parent->parent);
			}
		}
		else
		{
			uncle = node->parent->parent->left;	

			if (uncle->color == RED)		
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else 
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rightRotate(node);
				}
					
				node->parent->color = BLACK;	
				node->parent->parent->color = RED;

				leftRotate(node->parent->parent);
			}

		}
	}

	root->color = BLACK;		
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node* RB_Tree::leftRotate(RB_Node * p)
{
	RB_Node* c = p->right;		

	p->right = c->left;			

	if (c->left != NULLNODE)
		c->left->parent = p;

	c->parent = p->parent;			

	if (p->parent == NULLNODE)			
		root = c;
	else if (p == p->parent->left)	
		p->parent->left = c;
	else								
		p->parent->right = c;

	c->left = p;					
	p->parent = c;

	return c;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RB_Node* RB_Tree::rightRotate(RB_Node * p)
{
	RB_Node* c = p->left;	

	p->left = c->right;	

	if (c->right != NULLNODE)
		c->right->parent = p;

	c->parent = p->parent;			

	if (p->parent == NULLNODE)			
		root = c;
	else if (p == p->parent->left)	
		p->parent->left = c;
	else								
		p->parent->right = c;

	c->right = p;					
	p->parent = c;

	return c;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::erase(int key)
{
	RB_Node* node = _find(key);	
	RB_Node* y = NULLNODE;
	RB_Node* x = NULLNODE;

	if (node == NULLNODE)
		return;
		
	size--;
	
	if (node->left == NULLNODE || node->right == NULLNODE) 
		y = node;
	else
		y = node->successor();

	if (y->left != NULLNODE)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;

	if (y->parent == NULLNODE)		
		root = x;
	else if ( y == y->parent->left )	
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != node)
		node->key = y->key;

	if (y->color == BLACK)
		deleteRepair(x);

	
	if ( y == root)
		root = NULLNODE;

	y->left = NULL;
	y->right = NULL;
	delete y;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::deleteRepair(RB_Node * node)
{
	RB_Node* w = NULLNODE;

	while (node != root && node->color == BLACK)
	{
		if (node == node->parent->left)	
		{
			w = node->parent->right;		

			
			if (w->color == RED)				
			{										
				w->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				w = node->parent->right;
			}			
			
			if (w->left->color == BLACK && w->right->color == BLACK)
			{																
				w->color = RED;													
				node = node->parent;												
			}

			else 
			{
				if (w->right->color == BLACK)	
				{									
					w->left->color = BLACK;	
					w->color = RED;				
					rightRotate(w);					
					w = node->parent->right;	
				}

				w->color = node->parent->color;
				node->parent->color = BLACK;			
				w->right->color = BLACK;			
				leftRotate(node->parent);			
				node = root;								
			}
		}
		else
		{
			w = node->parent->left;		
			if (w->color == RED)			
			{
				w->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				w = node->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)	
			{
				w->color = RED;
				node = node->parent;
			}
			else 
			{
				if (w->left->color == BLACK)	
				{
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = node->parent->left;
				}
				w->color = node->parent->color;	
				node->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(node->parent);
				node = root;
			}
		}
	}

	node->color = BLACK;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::_dfs(RB_Node * v)
{
	// DO WHAT U WANNA eg printf data->name or sth
	// i ve been using boost::function (callback handling)	but it sux (long for compile, and slower)	 
	// so i am put result to vector
	
	result[rs]=v->data;
	rs++;
	if(v->left!=NULLNODE)
		_dfs(v->left);
	if(v->right!=NULLNODE)
		_dfs(v->right);	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void RB_Tree::dfs()
{
	rs=0;
	_dfs(root);
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


