#ifndef _TOKENCONTAINER_H_
#define _TOKENCONTAINER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Token.h"
#include "Tokenizer.h"

using namespace std;

class TokenContainer //Adrian: shouldn't this be : public Base ?
{
private:
	vector<Token*> tokenContainer;
public:
	virtual bool execute(string value){ //Adrian:need to recheck this if it's a child class
		Tokenizer * handler = new Tokenizer(value);
	}


};


#endif
