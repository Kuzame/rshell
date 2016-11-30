#ifndef _BINARY_TREE
#define _BINARY_TREE
#include "BinaryNode.h"

class BinaryTree
{
protected:
	BinaryNode* rootPtr;				// ptr to root node
	int count;							// number of nodes in tree
	BinaryNode* helperRootPtr;          // helper tree node for creating a second tree in case of parenthesis
	int numberOfParenth;				//contains the number of embedded parenthesis so far
	int numberOfRightParenth;			//contains the number of right parenthesis encountered
	vector<BinaryNode*> helperRootPtrLists;	//contains all of the helperRootPtrs that have been created so far
	Token* regularToken;                // helper token for creating and appending strings to a Token before inserting to the tree	

public:
	BinaryTree() { rootPtr = 0; count = 0; regularToken = new Token; helperRootPtr = 0; }
	BinaryTree(const BinaryTree & tree) { rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator=(const BinaryTree & sourceTree);

	//functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void clear() { 
		//cout << "\nClearing old tree\n\n"; 
		destroyTree(this->rootPtr); 
		if(!helperRootPtrLists.empty()){ helperRootPtrLists.clear();}		
		this->rootPtr = 0; 
		this->helperRootPtr = 0; 
		regularToken = 0; 
		this->count = 0; 
	}

	BinaryNode* copyTree(const BinaryNode* nodePtr);

	// abstract functions to be implemented by derived class
	virtual bool insert(Token* newData) = 0;
	//virtual BinaryNode* execute(const BinaryNode& temp);

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode* nodePtr);
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

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
//  overloads the = operator to copy right's tree to left's tree
BinaryTree & BinaryTree::operator=(const BinaryTree & sourceTree)
{
	if (rootPtr != 0) // already filled tree?
		clear(); // clear old tree
	rootPtr = copyTree(sourceTree.rootPtr);
	return *this;
}
#endif
