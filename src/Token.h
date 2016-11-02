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
	int size;
	
	//recursive function to count whitespaces and in turn count number of words
	//assumes the current member value is in the format of
	//"word1 word2 word3" and that it is not an empty string

	//removes any leading or ending whitespace from the value
// 	void removeWhiteSpace() {
// 		stringstream ss(this->getValue());
// 		string subStr;
// 
// 				
// 	}

	void _setValue(string value) {
		this->subTokens.push_back(value);
	}

	void _setSize(int size) {
		this->size = size;
	}

public:
	//constructors and destructors
	Token(){
// 		this->_setValue();
// 		this->_setSize(0);
	}

	//sets values and calls execute in order to generate and format members
	Token(string value){
 		this->_setValue(value);
// 		this->_setSize(0);	//simply instantiates the  int
		execute();
	}
	~Token(){}

	//accessors and mutators
// 	string getValue(){
// 		return this->value;
// 	}

	int getSize() {
		return (int)this->subTokens.size();
	}

	vector<string> getSubTokensVect() {
		return this->subTokens;
	}

	void setValue(string value) {
		_setValue(value);
	}

	void setSize(int size) {
		_setSize(size);
	}

	bool execute(){
		bool successfull = true;
/*		removeWhiteSpace();*/

		return successfull;
	}
};


#endif
