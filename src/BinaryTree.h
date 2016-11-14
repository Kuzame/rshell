#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

//class

class BinaryTree
{
protected:
	BinaryNode* rootPtr;				// ptr to root node
	int count;							// number of nodes in tree
										// copy from the tree rooted at nodePtr and returns a pointer to the copy
	
	BinaryNode* helperRootPtr;
	Token* regularToken;
	
	//BinaryNode* copyTree(const BinaryNode* nodePtr);

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; regularToken = new Token; helperRootPtr = 0; }
	BinaryTree(const BinaryTree & tree) { rootPtr = copyTree(tree.rootPtr); }// see assignment
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void clear() { 
		cout << "\nClearing old tree\n\n"; 
		destroyTree(this->rootPtr); 
		this->rootPtr = 0; 
		this->helperRootPtr = 0; 
		regularToken = 0; 
		this->count = 0; 
	}

	BinaryNode* copyTree(const BinaryNode* nodePtr);

	// abstract functions to be implemented by derived class
	virtual bool insert(Token* newData) = 0;
// 	virtual bool remove(const Token & data) = 0;
// 	virtual bool getEntry(const Token & anEntry, Token & returnedItem) const = 0;
	//virtual BinaryNode* execute(const BinaryNode& temp);

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode* nodePtr);
	// internal traverse
// 	void _preorder(void visit(Token &), BinaryNode* nodePtr) const;
// 	void _inorder(void visit(Token &), BinaryNode* nodePtr) const;
// 	void _postorder(void visit(Token &), BinaryNode* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////


//    If nodePtr doesn't exist (is 0) Then return 0
//	Assign a new BinaryNode to newNodePtr
//	Set the newNodePtr's data (item) to the nodePtr's item
//	Set the newNodePtr's leftPtr to 
//		a recursive call to copyTree for the nodePtr's leftPtr
//     Set the newNodePtr's rightPtr to
//		a recursive call to copyTree for the nodePtr's rightPtr
//	INCREMENT count
BinaryNode* BinaryTree::copyTree(const BinaryNode* nodePtr)
{
	BinaryNode* newNodePtr = 0;	//temp node
	if (nodePtr == 0)
		return 0;

	newNodePtr = new BinaryNode(nodePtr->getItem());	//setting passed node's data to newNodePtr

	newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));	//recursive call to traverse to next left pointer
	newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));	//recursive call to traverse to next right pointer
	++count;													//count new node objects
	return newNodePtr;											//return for recursive calls
}

//    if nodePtr doesn't exist (is 0), return
//    destroy the left subtree (recursive call to destroyTree)
//    destroy the right subtree (recursive call to destroyTree)
//    delete nodePtr
void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
	if (nodePtr == 0)
		return;
	destroyTree(nodePtr->getLeftPtr());	//recursive call to delete left branch
	destroyTree(nodePtr->getRightPtr());//recursive call to delete right branch
	delete nodePtr;						//deletes the passed ptr
}

BinaryTree & BinaryTree::operator=(const BinaryTree & sourceTree)
{
	if (rootPtr != 0) // already filled tree?
		clear(); // clear old tree
	rootPtr = copyTree(sourceTree.rootPtr);
	return *this;
}
#endif