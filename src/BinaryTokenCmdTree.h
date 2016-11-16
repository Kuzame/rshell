#ifndef _BINARY_TOKEN_CMD_TREE
#define _BINARY_TOKEN_CMD_TREE

#include "BinaryTree.h"


class BinaryTokenCmdTree : public BinaryTree
{
private:

	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNode);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Token & successor);

public:
	BinaryTokenCmdTree() { rootPtr = 0; count = 0; helperRootPtr = 0; }
	BinaryTokenCmdTree(const BinaryTokenCmdTree & tree) { this->rootPtr = copyTree(tree.rootPtr); this->helperRootPtr = tree.helperRootPtr; }
	~BinaryTokenCmdTree()
	{
		//BinaryTree::~BinaryTree();
	}

	// insert a node at the correct location
	bool insert(Token* newEntry);

	// assignment operator overload
	BinaryTokenCmdTree & operator=(const BinaryTokenCmdTree & sourceTree);

	//added for rshell 2.0
	void execute();
	void parseAndGenerateCmdTree(string line);

	bool isSpace(char val);
	bool isQuote(char val);
	bool isOr(char val);
	bool isAnd(char val);
	bool isSemicolon(char val);
	bool isNull(char val);
	bool isPound(char val);
	bool isLeftParenthesis(char val);
	bool isRightParenthesis(char val);
	bool isLeftBracket(char val);
	bool isRightBracket(char val);


};
///////////////////////// public function definitions ///////////////////////////

bool BinaryTokenCmdTree::insert(Token* newEntry)
{
	rootPtr = _insert(rootPtr, new BinaryNode(newEntry));
	return true;
}


BinaryTokenCmdTree & BinaryTokenCmdTree::operator=(const BinaryTokenCmdTree & sourceTree)
{
	/*compare = sourceTree.compare;*/
	this->BinaryTree::operator=(sourceTree);
	return *this;
}

//////////////////////////// private functions //////////////////////////////////
//Given pointer to BinaryNode object, the object is inserted to the BST

BinaryNode* BinaryTokenCmdTree::_insert(BinaryNode* nodePtr,
	BinaryNode* newNodePtr)
{
	//is dependent on syntax [cmd] [connector] [cmd]

	//case where there is nothing in the tree so we load a single command into it

	if (nodePtr == 0)						//case where the nodePtr has not been loaded with data yet (IF IT IS AN ARGUMENT WITH PARENTHESIS IT WILL SIMPLY REPLACE THIS TREE WITH THE OTHER)
		return newNodePtr;

	//case where the operator has been inserted to the tree and everything that came before it should be it's left child
	else if (newNodePtr->isOr() || newNodePtr->isAnd() || newNodePtr->isSemicolon()){

		//case where the newNodePtr does not have a left child already (NOT A PARENTHESIS CASE)
		if (newNodePtr->getLeftPtr() == 0)	
		{
			newNodePtr->setLeftPtr(copyTree(nodePtr));
			nodePtr = newNodePtr;
		}

		//case where the newNodePtr does have a left child (IF IT IS AN ARGUMENT WITH PARENTHESIS THIS WILL HAPPEN, BECAUSE A ROOTPTR WILL BE PASSED WITH CHILDREN)
 		else {
			nodePtr->setRightPtr(newNodePtr);
		}
	}
	
	//case where the newNodePtr is not a connector (not And, not Or, not Semicolon); it is an argument
	else {
		nodePtr->setRightPtr(newNodePtr);
	}



	return nodePtr; // must return
}

void BinaryTokenCmdTree::execute() {
	rootPtr->execute(); //when execute is called by the rootPtr, it recursively executes the commands using BinaryNode.h
}


void BinaryTokenCmdTree::parseAndGenerateCmdTree(string line)
{
	bool isParenth = false;
	bool throwError = false;
	bool lastToken = false;
	
	string result;				//the value of a token to be created is stored here
	string currentChar;			//the currentChar used in traversing through characters
	string nextChar;				//the nextChar used in finding the next character

	
	Token* helperToken = new Token();

	for (unsigned i = 0; i < line.length() && !lastToken; i++)
	{
		//currentChar and nextChar setters

		currentChar = line.at(i);
		//gets next char only if nextChar if nextChar (i + 1) is within range of string
		//else, it sets nextChar to -1, which is considered as NULl in bool isNull(char)
		if ((i + 1) < line.length())
		{
			nextChar = line.at(i + 1);
		}
		else
		{
			lastToken = true;
			nextChar = -1;
		}


		///------------------------------------------------------------
		//condition 1) if we reach a connector, or reach end of string,
		//insert the token created in the tree

		//condition 2) also, if we reach a space and if result is greater than zero,
		//append the current value to the existing token

		//condition 3) result should NEVER contain a space

		///------------------------------------------------------------



		//case: #
		if (isPound(currentChar.at(0))) {
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{

					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

				}
				else
				{
					this->insert(helperToken);

				}
				//helperToken = new Token();				//we know this is the last Token
			}

			lastToken = true;					//case where lastToken is absolutely necessary
		}

		//case: (
		else if (isLeftParenthesis(currentChar.at(0)))
		{
			isParenth = true;
		}

		//case: )
		else if (isRightParenthesis(currentChar.at(0)))
		{
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion if there is still something left to insert
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{
					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));
				}
				else
				{
					this->insert(helperToken);

				}
				helperToken = new Token();
			}

			isParenth = false;

			if (helperRootPtr->getItem()->getSubTokensVect().size() > 0)
			{
				rootPtr = this->_insert(rootPtr, helperRootPtr);				//inserts whatever got created in helperRootPtr if there is something in it	
			}
		}
		
		//case: [
		else if(isLeftBracket(currentChar.at(0)))
		{
			if (nextChar == " ")
			{
				helperToken->appendValue("test");
			}
			else
			{
				helperToken->appendValue("test");
				
			}
		}

		//case: ]
		else if(isRightBracket(currentChar.at(0)))
		{
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{
					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));
				}
				else
				{
					this->insert(helperToken);

				}
				helperToken = new Token();
			}
		
		}

		//case: ||
		else if (isOr(currentChar.at(0)) && isOr(nextChar.at(0))) {
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{

					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

				}
				else
				{
					this->insert(helperToken);

				}
				helperToken = new Token();
			}

			//inserts OR connector
			if (isParenth)
			{

				this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token("||")));

			}
			else
			{
				this->insert(new Token("||"));

			}
			++i;		//increments index to avoid a second |
		}

		//case: &&
		else if (isAnd(currentChar.at(0)) && isAnd(nextChar.at(0))) {
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{

					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

				}
				else
				{
					this->insert(helperToken);

				}
				helperToken = new Token();
			}


			//inserts AND connector
			if (isParenth)
			{

				this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token("&&")));

			}
			else
			{
				this->insert(new Token("&&"));

			}

			++i;		//increments index to avoid a second &
		}

		//case: ;
		else if (isSemicolon(currentChar.at(0))) {
			//if there is still something in result, then append the value to the helperToken and insert
			//handles appending
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			//handles insertion
			if (helperToken->getSubTokensVect().size() > 0)
			{
				if (isParenth)
				{

					this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

				}
				else
				{
					this->insert(helperToken);

				}
				helperToken = new Token();
			}

			//inserts SEMICOLON connector
			if (isParenth)
			{

				this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token(";")));

			}
			else
			{
				this->insert(new Token(";"));

			}

		}

		//case: space
		else if (isSpace(currentChar.at(0))) {
			if (result.size() > 0)
			{
				helperToken->appendValue(result);
				result = "";
			}

			if (lastToken)
			{
				//handles insertion
				if (helperToken->getSubTokensVect().size() > 0)
				{
					if (isParenth)
					{

						this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

					}
					else
					{
						this->insert(helperToken);

					}
					//helperToken = new Token();				//we know we do not need this since it is the lastToken
				}
			}
		}
		

		//case: commands (i.e. everything else)
		else {
			result += currentChar;
			//the only time a command will tokenize and insert itself is if this is the lastToken
			//in every other situation a connector can tokenize it
			if (lastToken)
			{			
				//if there is still something in result, then append the value to the helperToken and insert
				//handles appending
				if (result.size() > 0)
				{
					helperToken->appendValue(result);
					result = "";
				}

				//handles insertion
				if (helperToken->getSubTokensVect().size() > 0)
				{
					if (isParenth)
					{

						this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));

					}
					else
					{
						this->insert(helperToken);

					}
					//helperToken = new Token();				//we know we do not need this since it is the lastToken
				}
			}
		}


	//	if (throwError)
	//	{
	//		i = line.length();			//to exit loop	
	//	}

/*
		if (goodToInsert)
		{
			goodToInsert = false;
			if (isParenth)
			{

				this->helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(helperToken));
				
			}
			else
			{
				this->insert(helperToken);
				
			}

			//create new Token only if this is not the last Token
			if (!lastToken)
			{
				helperToken = new Token();
			}
		}
*/



	}

	//if for some reason a helperToken was created without any subTokens (i.e. created in error)
	//then delete it
	if (helperToken->getSubTokensVect().size() == 0)
	{

		delete helperToken;

	}
}



bool BinaryTokenCmdTree::isSpace(char val) {
	return val == ' ';
}


bool BinaryTokenCmdTree::isQuote(char val) {
	return val == '"';
}


bool BinaryTokenCmdTree::isOr(char val) {
	return val == '|';
}


bool BinaryTokenCmdTree::isAnd(char val) {
	return val == '&';
}


bool BinaryTokenCmdTree::isSemicolon(char val) {
	return val == ';';
}


bool BinaryTokenCmdTree::isNull(char val) {
	return val == -1;
}


bool BinaryTokenCmdTree::isPound(char val) {
	return val == '#';
}


bool BinaryTokenCmdTree::isLeftParenthesis(char val){
	return val == '(';
}


bool BinaryTokenCmdTree::isRightParenthesis(char val){
	return val == ')';
}


bool BinaryTokenCmdTree::isLeftBracket(char val){
	return val == '[';
}


bool BinaryTokenCmdTree::isRightBracket(char val){
	return val == ']';
}

#endif