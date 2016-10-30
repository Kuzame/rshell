#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"

using namespace std;

class Tokenizer : public Base
{
	
private:
	vector<Token*> tokenList;
	stringstream commandStream;

	void setVal(string value){
		commandStream.str(value);
	}

	void parse()
	{
		string result;																	//the value of a token to be created is stored here
		char currentChar;																//the currentChar used in traversing through characters
		char nextChar;																	//the nextChar used in finding the next character


																						//at this point of recursion all of the comments have been removed
		while (commandStream.get(currentChar)) {
			//case: "
			if (isQuote(currentChar))														//if started a quote execute this to get all values inside the quote without worrying about what is inside of it
			{
				result += currentChar;															//adds character to the string
				while (commandStream.get(currentChar) && (!isQuote(currentChar)))			//command gets the next character and puts it in currentChar and checks if that currentChar is not a quotation mark
				{
					result += currentChar;														//appends the next character read to the string result
					nextChar = commandStream.peek();											//gets the value of the next character to be accessed using get()

																								//checks if value of the next character is a quote, if so it stores the value in result since the while loop will exit
					if (isQuote(nextChar))
					{
						commandStream.get(currentChar);
						result += currentChar;
					}

					//if the next character is a null terminator for the string stream, but quotation has not been found, ask for more input
					if (isNull(nextChar))
					{
						string temp;
						do
						{
							temp = askForInputLine(); //prompts for more input

						} while (!containsQuoteAtLastIndex(temp));								//keeps asking for more input while user doesn't enter a quotation mark as the last character
					}
				}
			}

			//case: #
			else if (isPound(currentChar)) {
				if (result.size() > 0)
				{
					tokenize(result);															//creates a Token for result of everything before the '|' was found if there was something there
					commandStream.setVal("");													//makes an empty string be set in stream in order to terminate after
				}
			}

			//case: |
			else if (isOr(currentChar) && isOr(commandStream.peek())) {
				if (result.size() > 0)
				{
					tokenize(result);															//creates a Token for result of everything before the '|' was found if there was something there
				}

				commandStream.get(nextChar);													//get the next or
				result = currentChar;
				result += nextChar;												//the result is now the two pipes
				tokenize(result);																//creates a Token for the result
																								//resets result
				result = "";
			}

			//case: &
			else if (isAnd(currentChar) && isAnd(commandStream.peek())) {
				if (result.size() > 0) {
					tokenize(result);															//creates a Token for result of everything before the '&' was found if there was something there
				}

				commandStream.get(nextChar);													//get the next or
				result = currentChar + nextChar;												//the result is now the two bars
				tokenize(result);																//creates a Token for the result
																								//resets result																	
				result = "";
			}

			//case: everything else
			else {
				nextChar = commandStream.peek();
				result += currentChar;
				if (isNull(nextChar))															//if this is the last character in the line, proceed to tokenize everything that came before that
				{
					if (result.size() > 0)
					{
						tokenize(result);
					}
					else {
						//just continue to terminate without the result being tokenized
					}
				}
				else {
					//if the nextChar is not the null terminator
					commandStream.get(currentChar);
					result += currentChar;														//simply append the character to the string
				}


			}
		}



		
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

		//create string stream for getting individual strings out of the larger string
		//setVal(commands);
		//commandStream
	*/	
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

	bool isQuote(char val) {
		return val == '"';
	}

	bool isOr(char val) {
		return val == '|';
	}

	bool isAnd(char val) {
		return val == '&';
	}

	bool isSemicolon(char val) {
		return val == ';';
	}

	bool isNull(char val) {
		return val == -1;
	}

	bool isPound(char val) {
		return val == '#';
	}

	//returns input entered
	string askForInputLine() {
		string line;
		cout << "\n>> ";
		cin.ignore();
		getline(cin, line);

		return line;
	}
	
	//returns true if last index is quote
	bool containsQuoteAtLastIndex(string line) {
		return (line.at(line.size() - 1) == '"');
	}

	void tokenize(string value){
		tokenList.push_back(new Token(value));													//creates new token and appends it the the list
	}
	
	void removeWhiteSpace(){
		tokenList.
	}

public:

	Tokenizer(){ setVal(""); }
	Tokenizer(string value){
		setVal(value);
		execute();
	}
	void
		vector<Token*> tokenList;
	stringstream commandStream;

	bool execute(){
		bool successfull = true;
		if(setVal())
		parse();	//parses and tokenizes the values into a vector
		removeWhiteSpace();
		return successfull;
	}
};


#endif
