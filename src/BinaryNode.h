#ifndef _BINARY_NODE
#define _BINARY_NODE

class BinaryNode
{
private:
	Token* item;                    // Data portion
	BinaryNode* leftPtr;		    // Pointer to left child
	BinaryNode* rightPtr;		    // Pointer to right child
	Executor* executionFunction;    // Execution function for node to execute if it's a child
	bool continueExecution;         // Stores whether or not it should continue executing functions or not

public:
	// constructors
	BinaryNode() { item = 0; leftPtr = 0; rightPtr = 0; continueExecution = true; executionFunction = new Executor(); }
	BinaryNode(Token* anItem) { item = anItem; leftPtr = 0; rightPtr = 0; continueExecution = true; executionFunction = new Executor(); }
	BinaryNode(Token* anItem,
		BinaryNode* left,
		BinaryNode* right) {
		item = anItem; leftPtr = left; rightPtr = right; continueExecution = true; executionFunction = new Executor();
	}
	~BinaryNode()
	{
		delete executionFunction;
		delete item;
		leftPtr = 0;
		rightPtr = 0;
		item = 0;
	}
	// accessors
	void setItem(Token* anItem) { item = anItem; }	//ensure executionfunction is created and continueexecution is set to true
	void setLeftPtr(BinaryNode* left) { leftPtr = left; }
	void setRightPtr(BinaryNode* right) { rightPtr = right; }
	// mutators
	Token* getItem() const { return item; }
	BinaryNode* getLeftPtr() const { if (leftPtr == NULL || leftPtr == 0) return NULL;return leftPtr; }
	BinaryNode* getRightPtr() const {if (rightPtr == NULL || rightPtr == 0) return NULL; return rightPtr; }
	bool getContinueExecution() const { if (this == NULL) return true; return continueExecution; }
    
    //handles execution for children of ||, && and ; connectors
    //handles exiting execution if exit command is entered
    //handles execution of leaf nodes using Executor class object
	bool execute() {
		if (this == NULL) return false;
		if (!isLeaf() && !leftPtr->getContinueExecution())
		{
			continueExecution = false;
			return false;
		}

		if (isOr())
		{
			if (!leftPtr->execute()) {
				if (!rightPtr->execute())			//only executes right if left is false
				{
					return false;					//returns false if left is false and right is false
				}
				else
				{
					return true;					//returns true if left is false and right is true
				}
			}
			else
			{
				return true;						//returns true if left is true (does not execute right)
			}
		}
		else if (isAnd())
		{
			if (leftPtr->execute()) {
				if (rightPtr->execute())	//only executes right if left is true
				{
					return true;				//only returns true if left and right are true
				}
				else
				{
					return false;			//returns false if left is true and right is false
				}
			}
			else
			{
				return false;				//returns false if left is false (does not execute right)
			}
		}
		else if (isSemicolon())
		{
			leftPtr->execute();				//executes left and right no matter if it is true or false
			rightPtr->execute();
			return true;					//semicolon will always return true so it does not affect ORs or ANDs
		}
		else if (isExit()) {
			continueExecution = false;
			return false;
		}
		else {
			executionFunction->setVector(this->getItem()->getSubTokensVect());					//need to make setVector mutator in Executor
			return executionFunction->execute();
		}
		return true;
	}

    // returns true  if the node does not have a left or right pointer
	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
    
    // returns true if the item is an or 
	bool isOr() const { return (item->isOr()); }
	
    // returns true if the item is an and
    bool isAnd() const { return (item->isAnd()); }
	
    // returns true if the item is a semicolon
    bool isSemicolon() const { return (item->isSemicolon()); }
	
    // returns true if the item is an exit command
    bool isExit() const { return (item->isExit()); }
	
    // returns true if the item is a test command 
    bool isTest() const { return (item->isTest()); }

};
#endif 
