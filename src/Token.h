#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Token : public Base
{
private:
	vector<string> subTokens;
	
	void _appendValue(string value) {
		this->subTokens.push_back(value);
	}



public:
	//constructors and destructors
	Token(){}

	//sets values and calls execute in order to generate and format members
	Token(string value){
		this->appendValue(value);
	}
	~Token(){}

	int getSize() {
		return ((int)this->subTokens.size());
	}

	vector<string> getSubTokensVect() {
		return this->subTokens;
	}

	void appendValue(string value) {
		_appendValue(value);
	}

	string at(int i) {
		string temp = subTokens.at(i);
		return temp;
	}

	bool execute(){
		return true;
	}
};


#endif
