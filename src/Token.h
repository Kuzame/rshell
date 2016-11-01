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
	string value;
	vector<const char *> subTokens;
	int size;
	
	//recursive function to count whitespaces and in turn count number of words
	//assumes the current member value is in the format of
	//"word1 word2 word3" and that it is not an empty string
	void numWords(string tempValue) {
		this->setSize(subTokens.size());
	}

	//removes any leading or ending whitespace from the value
	void removeWhiteSpace() {
		stringstream ss(this->getValue());
		string subStr;
		while (ss >> subStr)
		{
			this->subTokens.push_back(subStr.c_str());
		}
				
	}

	void setValue(string value) {
		this->value = value;
	}

	void setSize(int size) {
		this->size = size;
	}

public:
	//constructors and destructors
	Token(){
		this->setValue("");
		this->setSize(0);
	}

	//sets values and calls execute in order to generate and format members
	Token(string value){
		this->setValue(value);
		this->setSize(0);	//simply instantiates the  int
		execute();
	}
	~Token(){}

	//accessors and mutators
	string getValue(){
		return this->value;
	}

	int getSize() {
		return this->size;
	}

	vector<const char*> getSubTokensVect() {
		return (this->subTokens);
	}

	char * getCharPtr() {
		int num = this->size;
		char * temp = new char[num];

		for (unsigned i = 0; i < subTokens.size(); i++)
		{
			
		}
	}

	bool execute(){
		bool successfull = true;
		removeWhiteSpace();

		return successfull;
	}
};


#endif
