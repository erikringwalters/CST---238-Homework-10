#include <iostream>
#include <iomanip>

using namespace std;

#include "BST.h"

//--- Definition of constructor
BST::BST()
	: myRoot(0)
{}

bool BST::empty() const
{
	return myRoot == 0;
}


bool BST::search(const int & item) const
{
	BinNode * locptr = myRoot;
	bool found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	return found;
}


void BST::insert(const int & item)
{
	BinNode * locptr = myRoot;   // search pointer
	BinNode * parent = 0;        // pointer to parent of current node
	bool found = false;     // indicates if item already in BST
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	if (!found)
	{                                 // construct node containing item
		locptr = new BinNode(item);
		if (parent == 0)               // empty tree
			myRoot = locptr;
		else if (item < parent->data)  // insert to left of parent
			parent->left = locptr;
		else                           // insert to right of parent
			parent->right = locptr;
	}
	else
		cout << "Item already in the tree\n";
}

//Definition of deleteNode()
void BST::deleteNode(const int & item) const
{
	BinNode *locptr = myRoot;
	BinNode * parent = myRoot;
	BinNode * twoChildrenPtr = myRoot;
	bool found = false;

	while (!found && locptr != 0)
	{
		if (item < locptr->data)  {     // descend left
			locptr = locptr->left;
			parent = locptr;
		}
		else if (locptr->data < item) {  // descend right
			locptr = locptr->right;
			parent = locptr;
		}
		else                           // item found
			found = true;
	}
	if (locptr->left == NULL && locptr->right == NULL)//no children
	{
		if (item < parent->data)//if left child
		{
			parent->left = NULL;//make left child NULL
		}
		if (item > parent->data)//if right child
		{
			parent->right = NULL;//make right child NULL
		}
		delete locptr;
		return;
	}
	else if (locptr->left != NULL && locptr->right == NULL)//item has a left child only
	{
		if (item >= parent->data)//if item is a right child
		{
			parent->right = locptr->left;//assigns 
		}
		else //if item is a left child
		{
			parent->left = locptr->left;
		}
	}
	else if (locptr->left == NULL && locptr->right != NULL)//item has a right child only
	{
		if (item >= parent->data)//if item is right child
		{
			parent->right = locptr->right;//assigns right child to item's child
		}
		else //if item is a left child
		{
			parent->left = locptr->right;
		}
	}
	else//two children
	{
		twoChildrenPtr = locptr->left;
		while (twoChildrenPtr->right != NULL)
		{
			twoChildrenPtr = twoChildrenPtr->right;
		}
		locptr->data = twoChildrenPtr->data;
		delete twoChildrenPtr;
	}

}