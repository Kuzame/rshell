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
		this->execute(value);
	}
	~Token(){}

	//accessors and mutators
	string getValue(){
		return this->value;
	}

	virtual bool execute(string value){
		bool successfull = true;
		setValue(value);
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
