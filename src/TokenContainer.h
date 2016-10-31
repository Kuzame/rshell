#ifndef _TOKENCONTAINER_H_
#define _TOKENCONTAINER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Token.h"

using namespace std;

class TokenContainer
{
private:
	vector<Token*> tokenContainer;
public:
	//I dee kay..................
	virtual bool execute(string value){
		//handler = new Tokenizer(value);
	}

	//mutator
	void pushBack(Token* value) {
		tokenContainer.push_back(value);
	}

	//mutator: remove functionality
	//recieves an index to delete as a value from 0 to tokenContainer.size()
	void removeAt(int deleteTokenIndex) {
		if (deleteTokenIndex < (int)tokenContainer.size())
		{
			tokenContainer.erase(tokenContainer.begin() + deleteTokenIndex);
		}
	}

	//accessor
	//receives an index to return as a Token pointer
	Token* at(int index) {
		return tokenContainer.at(index);
	}

	

};


#endif
