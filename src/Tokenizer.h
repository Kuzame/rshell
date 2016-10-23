#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Tokenizer : public Base
{
	
private:
	vector<size_t> allOccurences;
	stringstream* commandStream;

	void setVal(string value){
		commandStream = new stringstream(value);
	}

	void _tokenize(string commands)
	{
		
		//makes input stream from commands
		string token; //local variable for tokens read from commandStream


		int comment;
		int semicolon;
		int or;
		int and;

		while (*commandStream >> token) //loops as long as there is still an item left inside commandStream
		{
			size_t index;
			comment = token.find("#");
			semicolon = token.find(";");
			or = token.find("||");
			and = token.find("&&");

			if (comment != -1)
			{
				index = token.find_first_of("#");
				//push to vector the string to the left of the index
				//truncate string to only have first part of the string before that index with the # and simply get rid of code after #
			}
			else if (semicolon != -1)
			{
				index = token.find_first_of(";");
				//push to the vector anything to the left of the semicolon and renintiate tokenize for whatever is in the right; perhaps recursive calling the function
			}
			else if (semicolon != -1)
			{
				//push to the vector anything to the left of the semicolon and renintiate tokenize for whatever is in the right; perhaps recursive calling the function
			}

			
		}
	}

public:

	Tokenizer(){ setVal(""); }
	Tokenizer(string value){
		
	}

	bool execute(string value){
		setVal(value);
		bool successfull = true;
		_tokenize(value);
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
