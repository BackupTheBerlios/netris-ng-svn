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
#include "avltree.h"
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
AVL_Tree::AVL_Tree()
{
	size=0;
	
	root=NULL;
/*	root->left=NULL;
	root->right=NULL;	
	root->parent=NULL;*/
}
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
element AVL_Tree::find(int key)
{
	if(size==0)
		return NULL;
	tmp=root;
	while(tmp!=NULL)
	{
		if(key<tmp->key)
			tmp=tmp->left;
		else if(key>tmp->key)
			tmp=tmp->right;
		else 
			return tmp->data;
	}
	return NULL;
}
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
inline int AVL_Tree::height( AVL_Node * pos ) const
{
    	if( pos == NULL )
      	return -1;
    	else
    		return pos->factor;
}
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
inline int AVL_Tree::max( int a, int b ) const
{
  	return a > b ? a : b;
}
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
AVL_Node * AVL_Tree::singleRotateLeft(AVL_Node *K2)
{
	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	
	K2->factor = max(height(K2->left), height(K2->right))+1;
    	K1->factor = max(height(K1->left), K2->factor)+1;

           
	return K1;  // new root
}   
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
AVL_Node * AVL_Tree::singleRotateRight(AVL_Node *K1)
{
	K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1;
	
	K1->factor = max(height(K1->left), height(K1->right))+1;
    	K2->factor = max(height(K2->right), K1->factor)+1;

           
	return K2;  // new root
}   
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
AVL_Node * AVL_Tree::doubleRotateLeft(AVL_Node *K3)
{
	K3->left = singleRotateRight(K3->left);
           
	return singleRotateLeft(K3);
}   
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------- 
AVL_Node * AVL_Tree::doubleRotateRight(AVL_Node *K1)
{
	K1->right = singleRotateLeft(K1->right);
           
	return singleRotateRight(K1);
}   
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     
void AVL_Tree::insert(int key, cUser * data)
{
	size++;
	tmpdata=data;
	root=_insert(key,root);
}     
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     
AVL_Node * AVL_Tree::_insert(int key, AVL_Node * node)
{
	if (node==NULL)
	{
		node = new AVL_Node;
		node->factor=0;
		node->key=key;
		node->data=tmpdata;
		node->left=NULL;
		node->right=NULL;
// 		if(size==1)
// 			root=node;
	
	}
	else if(key < node->key)
	{
		node->left= _insert(key,node->left);
		if(height(node->left) - height(node->right) == 2)
		{
			if(key < node->left->key)
				node = singleRotateLeft(node);
			else
				node = doubleRotateLeft(node);
		}
 	}		 
	else if(key > node->key)		
	{
		node->right= _insert(key,node->right);
		if(height(node->right) - height(node->left) == 2)
		{
			if(key > node->right->key)
				node = singleRotateRight(node);
			else				
				node = doubleRotateRight(node);			
		}
 	}	 
		 
		 
		 
// 	node->factor=-1;		 
// 	if(node->left!=NULL)
// 		node->factor=node->left->factor;
// 	if(node->right!=NULL)
// 		node->factor=max(node->factor, node->right->factor);	

  	node->factor = max(height(node->left ),height(node->right))+1;
	return node;

}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     
void AVL_Tree::erase(int key)
{
	root=_erase(key,root);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
AVL_Node * AVL_Tree::_erase(int key, AVL_Node * node)
{
	bool done=false;
	if (node==NULL) 
	{   
		h=false;  
		done=true;
	}
	else
	if (key < node->key) //delee from left subtree	
	{
		newnode=_erase(key,node->left);
		node->left=newnode;
		if(h)
		{
			if(height(node->right) - height(node->left) == 2)
			{
				if(height(node->right) > height(node->left))
					node = singleRotateLeft(node);
				else				
					node = singleRotateRight(node);			
			}
			
			node->factor = max(height(node->left ),height(node->right))+1;
		
		
// 			if (node->factor >= 0)
//          		{
//          		   node->factor=root->factor-1;
//             	   if (node->factor==-1)
//             	   		h=false;
//          		}
//          		else if (node->right->factor==-1)
//          			singleRotateRight(node); 
//          		else 
//          			singleRotateLeft(node);         			
         			
         		done=true;		
         		return node;
		}
		
	
	}
	else if (key == node->key) //del node
	{
	  	if (node->left==NULL || node->right==NULL)  // one or no children 
      	{
      		if (node->left == NULL) 
      			K1=node->right;
      		else 
      			K1=node->left;
      			
      		delete node;
      		
      		h=true; done=true;
      		
      		return(K1);     		      		
      	
      	}
      	else // both of children
      	{
      	 	K2=node->right;
         		while (K2->left != NULL) 
         			K2=K2->left;
         			
         		node->key=K2->key;
         		key=node->key;
		}
	}
	
	if (!done && key >= node->key) // delete from right subtree 
	{
         	newnode=_erase(key, node->right);
         	node->right=newnode;
      	if (h)
      	{       		
         		if(height(node->right) - height(node->left) == 2)
			{
				if(height(node->right) > height(node->left))
					node = singleRotateLeft(node);
				else				
					node = singleRotateRight(node);			
			}
			node->factor = max(height(node->left ),height(node->right))+1;
         		//
/*         		if (node->factor <= 0) 
         		{
            		node->factor=node->factor+1;
            		if (node->factor ==1) 
            			h=false;
         		}	
         		else if (node->right->factor==1) 
         		 	singleRotateLeft(node);
         		else          		
         	     	singleRotateRight(node);*/
         	     return node;
         	}
	}
	
	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     
void AVL_Tree::dfs()
{
	_dfs(root);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     
void AVL_Tree::_dfs(AVL_Node * v) const
{
	// DO WHAT U WANNA eg printf data->name or sth
		
	if(v->left!=NULL)
		_dfs(v->left);
	if(v->right!=NULL)
		_dfs(v->right);	
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------     


