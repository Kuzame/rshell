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
	int size;
	
	//recursive function to count whitespaces and in turn count number of words
	//assumes the current member value is in the format of
	//"word1 word2 word3" and that it is not an empty string
	void numWords(string tempValue) {
		char space = ' ';
		int index = 0;
		
		//if it found a space...
		if ((index = tempValue.find_first_of(space)) != -1) {
			this->size += 1;
		}
		else {
			//no more whitespaces, so increment one last time for the last word after (n - 1) whitespace
			this->setSize(size + 1);
			return;
		}
		//passes a substring after the first whitespace
		string substring = tempValue.substr((index + 1), tempValue.length());
		numWords(substring);

	}

	//removes any leading or ending whitespace from the value
	void removeWhiteSpace() {
		string temp = this->getValue();
		int indexStart = temp.find_first_not_of(' ');		//find first index that is not whitespace
		int indexEnd = temp.find_last_not_of(' ');			//find last index that is not whitespace
		temp = temp.substr(indexStart, indexEnd);					//make a substring between the indexStart and indexEnd
		this->setValue(temp);								//mutate the original Token->value in tokenList to the new list
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

	const char * getCharPtr() {
		return (this->value.c_str());
	}

	bool execute(){
		bool successfull = true;
		if (this->getValue().find_first_of(' ') != -1){
			removeWhiteSpace();
		}

		numWords(getValue());
		return successfull;
	}
};


#endif
