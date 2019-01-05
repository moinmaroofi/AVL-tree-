
// f2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string>
using namespace std;
///////////////////////////////
class treeNode {
   friend class avlTree;
   public:
       treeNode *left ;
       int  key ;
       int bf;
       treeNode *right ;
} ;
///////////////////////////////
class avlTree {
   public:
      avlTree();
      void input();
      void avl_insert(treeNode **, int x, int *ub);
      void right_rotation(treeNode **, int *ub);
      void left_rotation(treeNode **, int *ub);
      void inorder (treeNode *s);
	  void preorder (treeNode *s);
	  void nabud();
	  void show();
	  void avl_delete(treeNode **,  treeNode **, int temp , int *ub);
	  void avl_ds();
	  treeNode *findfather(treeNode *R , treeNode *ptr);
	  void del_tow_ch(treeNode** , treeNode ** , int*wb);
      treeNode *getRoot(){return root;}
		  int *count;
   private:
      treeNode *root;
};
//***************
avlTree::avlTree()
{
  root = NULL;
}
//********************
avlTree avl;
//**********************
void avlTree::nabud()
{
	root=NULL;
}
///////////////////////////////////
void dfs(treeNode *);
void avlTree::show()
{
   treeNode *p=root;
	dfs(p);
}

//**********************

void avlTree::input()
{
  int x;
  int ub;
 system("cls");
 cout<<" enter  any character to exit !\n\n";
  while(1)
  {
      cout << "Enter a number: ";
      cin >> x;
	  if(x)
	  avl.avl_insert(&root, x, &ub);
	  else
		  break;
  }
}
//*****************
void avlTree::avl_insert(treeNode **parent, int x, int *ub)
{
   if(!(*parent))
   {     //insert element into null tree*/
      *ub = 1;
      *parent = new treeNode;
      (*parent) -> left = (*parent) -> right = NULL;
      (*parent) -> bf = 0;
      (*parent) -> key = x;
   }
   else if(x < (*parent) -> key)
   {
       avl.avl_insert(&(*parent) -> left, x, ub);
       if(*ub)  //left branch has grown higher
	  switch((*parent) -> bf)
	  {
	     case -1:
		(*parent) -> bf = 0;
		*ub = 0;
		break;
	     case 0:
		(*parent) -> bf = 1;
		break;
	     case 1:
		avl.right_rotation(parent, ub);
	  }
   }//end of else if
   else if(x > (*parent) -> key)
   {
       avl.avl_insert(&(*parent) -> right, x, ub);
       if(*ub)  //right branch has grown higer
	  switch((*parent) -> bf)
	  {
	     case 1:
		(*parent) -> bf = 0;
		*ub = 0;
		break;
	     case 0:
		(*parent) -> bf = -1;
		break;
	     case -1:
		left_rotation(parent, ub);
	  } //end of switch
   } //end of else if
   else if(x == (*parent)->key)
   {
      *ub = 0;
      cout << "\n The key is already in the tree.\n";
      getch();
   }
   else
	   cout<< "the value is not crect";
}
//*****************
void avlTree::avl_ds()
{
	int temp;
	int ob;
	system("cls");
	cout<<"choose one of the numbers for deleting \nfor exit use 0 button...";
	while(1){
		cout<<"\n\nwe have : ";
		avl.inorder(avl.getRoot());
		cout<<"in Tree..\n\n \t\t";
		cin>>temp;
		if(temp){
			treeNode* ptr = avl.getRoot();
			avl.avl_delete(&root, &ptr, temp, &ob);
		}
		else
			break;
	}
}
//*****************
void avlTree::avl_delete(treeNode **parent,treeNode **hr, int temp,int *ob)
{
	if((*parent)){
		*ob = 1;
		if (temp == (*parent)->key)
		{
			if((*parent)->left==NULL && (*parent)->right == NULL)
			{
				if((*parent) != (*hr))
				{		
					treeNode *father = findfather((*hr) , (*parent));
					if((*parent)->key > father->key)
					{
						father->right = NULL;
						delete[](*parent);
					}
					else{
						father->left = NULL;
						delete[](*parent);
					}
				}
				else
				{
					delete[] (*parent);
					(*parent) = NULL;
				}
			}
			else if((*parent)->left==NULL && (*parent)->right != NULL)
			{
				treeNode *ptr1 = (*parent)->right;
				delete[] (*parent);
				(*parent) = ptr1;
			}
			else if((*parent)->right == NULL && (*parent)->left != NULL)
			{
				treeNode* ptr1 = (*parent)->left;
				delete[] (*parent);
				(*parent)=ptr1;
			}
			else
			{
				if((*parent)->right->left == NULL)
				{
					(*parent)->key = (*parent)->right->key;
					treeNode* ptr = (*parent)->right;
					(*parent)->right = (*parent)->right->right;
					delete[] ptr;
					ptr = NULL;
					switch((*parent)->bf)
					{
					case -1:
						(*parent)->bf=0;
						break;
					case 0:
						(*parent)->bf=1;
						break;
					case 1:
						right_rotation(&(*parent) , ob);
					}
				}
				else if((*parent)->left->right == NULL)
				{
					(*parent)->key = (*parent)->left->key;
					treeNode* ptr = (*parent)->left;
					(*parent)->left = (*parent)->left->left;
					delete[] ptr;
					ptr = NULL;
					switch((*parent)->bf)
					{
					case 1:
						(*parent)->bf=0;
						break;
					case 0:
						(*parent)->bf=-1;
						break;
					case -1:
						left_rotation(&(*parent) , ob);
					}
				}
				else
				{
					treeNode* ptr = (*parent)->left;
					int wb=1;
					int tag = ptr->bf;
					avl.del_tow_ch(&(*parent), &ptr , &wb);
					*ob = wb;
					if (tag == 0)
						ob == 0;
					if(*ob)
					{
						switch ((*parent)->bf){
						case 1:
							(*parent)->bf = 0;
							break;
						case -1:
							avl.right_rotation(&(*parent), ob);
						}
					}
				}
			}
		}
		else if(temp<(*parent)->key)
		{
			avl.avl_delete(&(*parent)->left , &(*hr) , temp , &(*ob));
			if(*ob)
			{
				switch((*parent)->bf)
				{
				case 1:
					(*parent)->bf=0;
					break;
				case 0:
					(*parent)->bf=-1;
					*ob = 0;
					break;
				case -1:
					avl.left_rotation(&(*parent) , ob);
				}
			}
		}
		else if(temp > (*parent)->key)
		{
			avl.avl_delete(&(*parent)->right , &(*hr) , temp , ob);
			if(*ob)
			{
				switch((*parent)->bf)
				{
				case -1:
					(*parent)->bf = 0;
					break;
				case 0:
					(*parent)->bf = 1;
					*ob = 0;
					break;
				case 1:
					avl.right_rotation(&(*parent) ,ob);
				}
			}
		}
	}
	else{ 
		cout <<"the number is not in the three";
	}
}	

//*****************
void avlTree::del_tow_ch(treeNode** parent , treeNode** child ,int *wb)
{
	if ((*child)->right == NULL)
	{
		(*parent)->key = (*child)->key;
		treeNode* ptr = (*child)->left;
		delete[] (*child);
		(*child) = ptr;
	}
	else{
		avl.del_tow_ch(&(*parent) , &((*child)->right) , wb);
		if(*wb){
			switch((*child)->bf){
			case -1:
				(*child)->bf = 0;
				break;
			case 0:
				(*child)->bf = 1;
				*wb = 0;
				break;
			case 1:
				avl.left_rotation(&(*child) , wb);
			}
		}
	}
}
//*****************
void avlTree::right_rotation(treeNode **parent, int *ub)
{
   treeNode *grand_child, *child=NULL;
   if((*parent)->left!=NULL)
	   child = (*parent) -> left;
   if(child->bf==1 )
   {
      //LL rotation
	   cout<<"\n  LL rotation  \n";
      (*parent) -> left = child -> right;
      child -> right = *parent;
      (*parent) -> bf = 0;
      (*parent) = child;
   }
   else
   {   //LR rotation
	   	   cout<<"\n  LR rotation  \n";
	   if(child ->right != NULL)
	   {

      grand_child = child -> right;
      child -> right = grand_child -> left;
      grand_child -> left = child;
      (*parent) -> left = grand_child -> right;

	 	  grand_child ->right= (*parent);
      switch(grand_child -> bf)
      {
	 case 1:
	     (*parent) -> bf = -1;
	     child -> bf = 0;
	     break;
	 case 0:
	     (*parent) -> bf = child -> bf = 0;
	     break;
	 case -1:
	     (*parent) -> bf = 0;
	     child -> bf = 1;
      }
	   }
	    *parent = grand_child;
   }
      
   (*parent) -> bf = 0;
   *ub = 0;
}
//*****************
void avlTree::inorder(treeNode *s)
{
    if(s)
    {
		if(s->left != NULL)
			inorder(s->left) ;
       cout << s->key << "  ";
	   if(s->right !=NULL) 
		   inorder(s->right) ;
    }
	
}
//*****************
void avlTree::left_rotation(treeNode **parent, int *ub)
{
   treeNode *grand_child, *child;
   child = (*parent) -> right;
   if(child -> bf == -1 )
   {
	   	   cout<<"\n  RR rotation  \n";	   
	   //RR rotation
      (*parent) -> right = child -> left;
      child -> left = *parent;
      (*parent) -> bf = 0;
      (*parent) = child;
   }
   else
   {   //RL rotation
	   	   	   cout<<"\n  RL rotation  \n";
	   if(child -> left !=NULL)
    { 
		grand_child = child -> left;
      child -> left = grand_child -> right;
      grand_child -> right = child;
      (*parent) -> right = grand_child -> left;
	  grand_child ->left= (*parent);
	  switch(grand_child -> bf)
      {
	 case 1:
	     (*parent) -> bf = 0;
	     child -> bf = -1;
	     break;
	 case 0:
	     (*parent) -> bf = child -> bf = 0;
	     break;
	 case -1:
	     (*parent) -> bf = 1;
	     child -> bf = 0;
      }
	
	   *parent = grand_child;
   }
   }
   (*parent) -> bf = 0;
   *ub = 0;
}
//************************************************
treeNode* avlTree::findfather(treeNode *R , treeNode *ptr)
{
	if(R == NULL || R == ptr)
		return NULL;
	if(R->left == ptr || R->right == ptr)
		return R;
	if( avl.findfather(R->left , ptr) != NULL)
		return avl.findfather(R->left ,ptr);
	 if( avl.findfather(R->right , ptr) != NULL)
		return avl.findfather(R->right , ptr);
	 return NULL;
}

//************************************************
struct ali{
	treeNode *e;
	ali *next;
};
///////////////  Intializing  Queue ////////////
class queue{
public:
	 queue();
	 int empty();
	 void addQ(treeNode **s);
	 treeNode * delQ();
     ali *front;
	 ali *last;
};
queue::queue()
{
	front=NULL;
	last=NULL;
}

int queue::empty()
{
	if(front==NULL) 
		return 1;
	return 0;
}
void queue::addQ(treeNode **s)
{
	if((*s) !=NULL)cout<<"\nadded  "<<(*s)->key<<" with bf= "<<(*s)->bf<<"\n";
		ali * a1=new ali;
		a1->next=NULL;
	if(empty())
	{
		a1->e=*s;
		a1->next=NULL;
		last=front=a1;
	}
	else{
		a1->e=(*s);
		a1->next=NULL;
		last->next=a1;
		last=last->next;	
	}
}
treeNode * queue::delQ()
{
	ali *u; 
	if(!empty())
	{
         u=front;
		 front=front->next;
		 if(u->e)  cout<<"\n\t\t deleted  "<<u->e->key<<"\n";
	}
		return u->e;
}
///////////////////  DFS  Traversaling ////////////////
queue Q;
void dfs(treeNode *p)
{

Q.addQ(&p);
int flag=1;
   do
	{
			p=Q.delQ();
		
		/////////////////////////////
		if(p ==NULL)
		{
			avl.nabud();
			break;
		}
		/////////////////////////////
		if(p!=NULL){
		if((p)->left !=NULL)
			Q.addQ(   &(p->left)   );
		if((p)->right !=NULL)
			Q.addQ(   &(p->right)    );
		}
	}while( ! (Q.empty())&& p!=NULL);
	
}

///////////////////////  Intializing  Menu ////////////////
int menu(){
	system("cls");
		cout<<"______________________________";
	cout<<"\n";
	cout<<"1-Add...\n2-Delete...\n3-Display tree & DFS traveling...\n4-distruct..\n5-Exit\n\n\n";
		cout<<"\n_______________________________\n";
	int number;
	cin>>number;
	switch(number)
	{
	case 1:  
		avl.input();
		break;	 
	case 2:{
		avl.avl_ds();
		   break;
		   }
	case 3:{
		system("cls");

		if(avl.getRoot()!=NULL){
		cout<<"\n ****************************** \n \t Traversed tree is: \n";
		avl.inorder(avl.getRoot());
		cout<<"\n ****************************** \n ";
		cout<<"DFS traveling results..\n";
		avl.show();
		cout<<"\n\n\n******************************\n\n";
		}
		else{
			cout<<"\n  TREE   IS   EMPTY !";
		}
		
		getch();
		break;
		   };
	case 4:avl.nabud();
		system("cls");
		cout<<"\n  all of tree is now distructed...\n prees any key ...!";
		getch();
		break;
	case 5:exit(0);break;
	default:exit(0);break;
	}

	return 1;
}
//////////////////////////////  MAIN  //////////////////
int main()
{
	int state=1;
	while(state)
	{
		state=menu();
	}
	getch();
  return 0;
}
///////////////////////////////////////////////////////