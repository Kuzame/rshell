#ifndef _BINARY_NODE
#define _BINARY_NODE


class BinaryNode
{
private:
	Token* item;         // Data portion
	BinaryNode* leftPtr;		// Pointer to left child
	BinaryNode* rightPtr;		// Pointer to right child
	Executor* executionFunction;
	bool continueExecution;


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
		//delete /*executionFunction,*/ leftPtr;
		//delete rightPtr;
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
	BinaryNode* getLeftPtr() const { return leftPtr; }
	BinaryNode* getRightPtr() const { return rightPtr; }
	bool getContinueExecution() const { return continueExecution; }

	bool execute() {
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

	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
	bool isOr() const { return (item->isOr()); }
	bool isAnd() const { return (item->isAnd()); }
	bool isSemicolon() const { return (item->isSemicolon()); }
	bool isExit() const { return (item->isExit()); }
	bool isTest() const { return (item->isTest()); }

};
#endif 
