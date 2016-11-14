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
	BinaryTokenCmdTree() { rootPtr = 0; count = 0; helperRootPtr = 0; regularToken = new Token; }
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
	void tokenize(bool isLastToken, string line);
	void tokenizeWithinParenthesis(bool isLastToken, string line);

	bool BinaryTokenCmdTree::isSpace(char val);
	bool BinaryTokenCmdTree::isQuote(char val);
	bool BinaryTokenCmdTree::isOr(char val);
	bool BinaryTokenCmdTree::isAnd(char val);
	bool BinaryTokenCmdTree::isSemicolon(char val);
	bool BinaryTokenCmdTree::isNull(char val);
	bool BinaryTokenCmdTree::isPound(char val);
	bool BinaryTokenCmdTree::isLeftParenthesis(char val);
	bool BinaryTokenCmdTree::isRightParenthesis(char val);
	bool BinaryTokenCmdTree::isLeftBracket(char val);
	bool BinaryTokenCmdTree::isRightBracket(char val);


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

	string result;				//the value of a token to be created is stored here
	string currentChar;			//the currentChar used in traversing through characters
	string nextChar;				//the nextChar used in finding the next character

	bool lastToken = false;

	for (unsigned i = 0; i < line.length() && !lastToken; i++)
	{
		currentChar = line.at(i);
		if ((i + 1) < line.length())
		{
			nextChar = line.at(i + 1);
		}
		else
		{
			lastToken = true;
			nextChar = -1;
		}

		//case: #
		if (isPound(currentChar.at(0))) {
			if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {			//if not empty and found a character which is not a space
			//if (((int)result.size() > 0)) {
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = "";
				}
			
			}
			lastToken = true;															//when it reaches the conditions check in for loop it will terminate the parseAndGenerateCmdTree stage
		}

		//case: (
		else if (isLeftParenthesis(currentChar.at(0)))
		{
			isParenth = true;
		}

		//case: )
		else if (isRightParenthesis(currentChar.at(0)))
		{
			isParenth = false;
			//when the closing parenthesis is found, it inserts the newly created tree into whichever location is available in the actual rootPtr
			//result = -1;
			tokenizeWithinParenthesis(lastToken, result);		//tokenizes the last value before the right parenthesis
			rootPtr = this->_insert(rootPtr, helperRootPtr);
		}

		//case: ||
		else if (isOr(currentChar.at(0)) && isOr(nextChar.at(0))) {
			if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {	//checks if result contains a character that is not a whitespace character
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = "";
				}

			}

			//either way, you always want to tokenize the "||"
			result = currentChar;
			result += nextChar;																//the result is now the two pipes
			//creates a Token for the result
			if (!isParenth)
			{
				tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
				result = "";
			}
			else
			{
				tokenizeWithinParenthesis(lastToken, result);
				result = "";
			}

			++i;																			//increments the iteration so it is now at the index of the second '|' since we know what it is


			result = "";
		}

		//case: &&
		else if (isAnd(currentChar.at(0)) && isAnd(nextChar.at(0))) {
			if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {	//checks if result contains a character that is not a whitespace character
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = '\0';
				}

			}

			//either way, you always want to tokenize the "&&"
			result = currentChar;
			result += nextChar;																//the result is now the two pipes
			//creates a Token for the result
			if (!isParenth)
			{
				tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
				result = "";
			}
			else
			{
				tokenizeWithinParenthesis(lastToken, result);
				result = "";
			}
			++i;																			//increments the iteration so it is now at the index of the second '&' since we know what it is


			result = "";
		}

		//case: ;
		else if (isSemicolon(currentChar.at(0))) {
			if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = "";
				}

			}
			result = currentChar;
			if (!isParenth)
			{
				tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
				result = "";
			}
			else
			{
				tokenizeWithinParenthesis(lastToken, result);
				result = "";
			}

		}

		//case: space
		else if (isSpace(currentChar.at(0))) {
			//do nothing
			//do not want to tokenize an empty character so we simply tokenize what ever came before it
			if ((((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) || lastToken) {		//ADDED FUNCTIONALITY HERE VS IN FOR LOOP MIGHT HANDLE THE SAME POSSIBLE SITUATION TWICE
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = "";
				}

			}
		}

		//case: everything else
		else {
			/*nextChar = commandStream.peek();*/
			result += currentChar;
			if (isNull(nextChar.at(0)) && ((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {		//if this is the last character in the line, proceed to tokenize everything that came before that
				if (!isParenth)
				{
					tokenize(lastToken, result);														//creates a Token for result of everything before the '|' was found if there was something there
					result = "";
				}
				else
				{
					tokenizeWithinParenthesis(lastToken, result);
					result = "";
				}

			}
		}
	}
}


void BinaryTokenCmdTree::tokenize(bool isLastToken, string line) {
	if (isOr(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		this->insert(regularToken);
		regularToken = new Token;

		this->insert(new Token(line));

	}
	else if (isAnd(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		this->insert(regularToken);
		regularToken = new Token;

		//push currentValue

		this->insert(new Token(line));
	}
	else if (isSemicolon(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		this->insert(regularToken);
		regularToken = new Token;

		//push currentValue

		this->insert(new Token(line));
	}
	else
	{
		if (!isNull(line.at(0)))
		{
			regularToken->appendValue(line);
		}
		else {
			this->insert(regularToken);
			regularToken = new Token;
		}
		
		if (isLastToken) {
 			this->insert(regularToken); 
 		}
	}
}


void BinaryTokenCmdTree::tokenizeWithinParenthesis(bool isLastToken, string line){

	if (isOr(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(regularToken));
		regularToken = new Token;

		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token(line)));

	}
	else if (isAnd(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(regularToken));
		regularToken = new Token;

		//push currentValue

		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token(line)));
	}
	else if (isSemicolon(line.at(0)))
	{
		//push regularToken to the vector for all previous non special tokens
		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(regularToken));
		regularToken = new Token;

		//push currentValue

		helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(new Token(line)));
	}
	else
	{
		if (!isNull(line.at(0)))
		{
			regularToken->appendValue(line);
		}

		//in case caller is right parenthesis, we need to make sure _insert isn't duplicated
		if(isNull(line.at(0) && !isLastToken)) {
			helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(regularToken));
			regularToken = new Token;
		}

		if (isLastToken) {
			helperRootPtr = this->_insert(helperRootPtr, new BinaryNode(regularToken));
		}
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