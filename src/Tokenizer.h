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

	void parse(string token)
	{
		
		//makes input stream from commands
		string token; //local variable for tokens read from commandStream

		int comment;
		int semicolon;
		//int or;
		//int and;

	
		//precedence level 0
		if ((comment = token.find_first_of("#")) != -1) {		//if parser finds comment, remove whatever is to the right and recursively call _tokenize() in order to pass the next string
			parse(token.substr(0, comment));
		}
		//precedence level 1
		if ((semicolon = token.find_first_of(";")) != -1)		//if parser finds semicolon, seperate the two different set of arguments into two _tokenize() calls
		{
			parse(token.substr(0, semicolon));				//if call _tokenize() for first part of string up until the ; delimeter
			parse(token.substr(semicolon, token.size()));	//if call parse() for the index from the ; to the end of the string and handle that appropriately
		}

		//at this point of recursion all of the different commands with their arguments have been separated into different function calls, but they may still include a value such as || or &&

		commandStream.setVal(token + " "); 				//commandStream may or may not contain || or && and will still have whitespaces
		
/*------10/24/16
		//precedence level 2
		if ((or = token.find_first_of("||")) != -1)
		{

		}

		//at this point of recursion all of the 

		//precedence level 2
		if ((and = token.find_first_of("&&")) != -1)
		{

		}

*/
		//create string stream for getting individual strings out of the larger string
		//setVal(commands);

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

	void tokenize(){
		string temp;
		while(commandStream >> temp){
			tokenList.pushBack(new Token(temp));	//container object will contain a list of commands and || and && in the order that they were passed
		} 
	}

public:

	Tokenizer(){ setVal(""); }
	Tokenizer(string value){
		execute(value);
	}

	bool execute(string value){
		setVal(value);
		bool successfull = true;
		parse(value);	//first parses to separate into string with only commands and || and &&
		tokenize();	//creat tokens out of the newly parsed string in stringstream member variable
		return successfull;
	}
};


#endif
