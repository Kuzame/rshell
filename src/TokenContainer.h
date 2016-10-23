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
	virtual bool execute(string value){
		Tokenizer * handler = new Tokenizer(value);
	}


};


#endif
