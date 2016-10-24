#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"
#include "TokenContainer.h"

using namespace std;

class Tokenizer : public Base
{
	
private:
	//vector<size_t> allOccurences;
	TokenContainer* tokenList;
	stringstream commandStream;

	void setVal(string value){
		commandStream.str(value);
	}

	void _tokenize(string commands)
	{
		
		//makes input stream from commands
		string token = commands; //local variable for tokens read from commandStream

		int comment;
		int semicolon;
		int or;
		int and;

	
		//precedence level 0
		if ((comment = token.find_first_of("#")) != -1) {		//if tokenizer finds comment, remove whatever is to the right and recursively call _tokenize() in order to pass the next string
			_tokenize(token.substr(0, comment));
		}
		//precedence level 1
		if ((semicolon = token.find_first_of(";")) != -1)		//if tokenizer finds semicolon, seperate the two different set of arguments into two _tokenize() calls
		{
			_tokenize(token.substr(0, semicolon));				//if call _tokenize() for first part of string up until the ; delimeter
			_tokenize(token.substr(semicolon, token.size()));	//if call _tokenize() for the index from the ; to the end of the string and handle that appropriately
		}

		//at this point of recursion all of the different commands with their arguments have been separated into different function calls

		//precedence level 2
		if ((or = token.find_first_of("||")) != -1)
		{

		}

		//at this point of recursion all of the 

		//precedence level 2
		if ((and = token.find_first_of("&&")) != -1)
		{

		}

		//create string stream for getting individual strings out of the larger string
		setVal(commands);

		//commandStream
			
		



		/*
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
			*/
			
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
