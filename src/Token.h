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
	void setValue(string value){
		this->value = value;
	}
public:
	//constructors and destructors
	Token(){
		this->setValue("");
	}
	Token(string value){
		this->setValue(value);
	}
	~Token(){}

	//accessors and mutators
	string getValue(){
		return this->value;
	}

	const char * getCharPtr() {
		return (this->value.c_str());
	}


	bool execute(){
		bool successfull = true;
		//setValue(value);
		//if ()
		//{
		//}
		//else{
		//successfull = false;
		//}


		return successfull;
	}
};


#endif
