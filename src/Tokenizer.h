#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

using namespace std;

class Tokenizer : public Base{
	
private:
	vector<Token*> tokenList;
	stringstream commandStream;
	string regularTokenString;
	Token * regularToken;
	bool lastToken;

	void _setVal(string value){
		commandStream.str(value);
	}

	void parse()
	{
		string result;				//the value of a token to be created is stored here
		char currentChar;			//the currentChar used in traversing through characters
		char nextChar;				//the nextChar used in finding the next character
//		regularToken = new Token();

		while (this->commandStream.get(currentChar)) {
			//currentChar is the character being tested
			nextChar = commandStream.peek();

			//case: "
			//if started a quote execute this to get all values inside the quote without worrying about what is inside of it
			if (isQuote(currentChar)) {	

				do {
					if (currentChar != '"') result += currentChar;												//not include the actual quotation mark
																			//appends the next character read to the string result
					nextChar = commandStream.peek();										//gets the value of the next character to be accessed using get()
					commandStream.get(currentChar);											//gets the next character in order to check if it is a quotation mark
					if (currentChar == '"') {
						result += "\n";	//to be able to add newline in output
						this->tokenize(result);
						result = "";
					}

					//if the next character is a null terminator for the string stream, but quotation has not been found, ask for more input
					if (isNull(nextChar))
					{
						string temp = "";
						do
						{
							temp += askForInputLine(); //prompts for more input
							
						} while ( (!containsQuoteAtLastIndex(temp)) && ((temp += "\n") == temp));
						//keeps asking for more input while user doesn't enter a quotation mark as the last character
						int eraseQuote = temp.length() - 1; //we know last character in the string contains quotation mark by previous conditions
						// erase the actual quotation mark, so it's not included in the token
						temp.erase(eraseQuote);
						result += temp;
						this->tokenize(result);
						currentChar = '"';
					}

				} while (!isQuote(currentChar));
			}

			//case: #
			else if (isPound(currentChar)) {
				if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {			//if not empty and found a character which is not a space
				
					tokenize(result);														//creates a Token for result of everything before the '|' was found if there was something there
				}
				commandStream.str("");													//makes an empty string be set in stream in order to terminate after
			}

			//case: |
			else if (isOr(currentChar) && isOr(nextChar)) {
				if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {
			
					tokenize(result);															//creates a Token for result of everything before the '|' was found if there was something there
				}

				result = currentChar;
				this->commandStream.get(nextChar);
				result += nextChar;																//the result is now the two pipes
				tokenize(result);																//creates a Token for the result
																								//resets result
				result = "";
			}

			//case: &
			else if (isAnd(currentChar) && isAnd(commandStream.peek())) {
				if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {
				
					tokenize(result);															//creates a Token for result of everything before the '&' was found if there was something there
				}

				//commandStream.get(nextChar);													//get the next or
				result = currentChar;
				this->commandStream.get(nextChar);
				result += nextChar;																//the result is now the two pipes
				tokenize(result);																//creates a Token for the result
																								//resets result
				result = "";
			}
			//case: ;
			else if (isSemicolon(currentChar)) {
				if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {
	
					tokenize(result);															//creates a Token for result of everything before the '&' was found if there was something there
					result = "";
				}
				tokenize(";");
			}
			//case: space
			else if (isSpace(currentChar)) {
				//do nothing
				//do not want to tokenize an empty character so we simply tokenize what ever came before it
				if (((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {
					tokenize(result);															//creates a Token for result of everything before the '&' was found if there was something there
					result = "";
				}
			}
			//case: everything else
			else {
				/*nextChar = commandStream.peek();*/
				result += currentChar;
				if (isNull(nextChar) && ((int)result.size() > 0) && ((int)result.find_first_not_of(' ') != -1)) {		//if this is the last character in the line, proceed to tokenize everything that came before that		
					tokenize(result);
				}
			}
		}
	}

	bool isSpace(char val) {
		return val == ' ';
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

		getline(cin, line);
		return line;
	}
	
	//returns true if last index is quote
	bool containsQuoteAtLastIndex(string line) {
		int lineSize = (int)line.size();
		char lastChar;

		lastChar = line.at(lineSize - 1);
	
		return (lastChar == '"');
	}

	//creates new token and appends it the the vector tokenList
	void tokenize(string value){
		if (value == "||")
		{
			//push regularToken to the vector for all previous non special tokens
			tokenList.push_back(regularToken);
			regularToken = new Token;

			tokenList.push_back(new Token(value));

		}
		else if (value == "&&")
		{
			//push regularToken to the vector for all previous non special tokens
			tokenList.push_back(regularToken);
			regularToken = new Token;

			//push currentValue

			tokenList.push_back(new Token(value));
		}
		else if (value == ";")
		{
			//push regularToken to the vector for all previous non special tokens
			tokenList.push_back(regularToken);
			regularToken = new Token;

			//push currentValue

			tokenList.push_back(new Token(value));
		}
		else
		{
			
			regularToken->appendValue(value);
			
			char temp = commandStream.peek();
			if (isNull(temp)){
				tokenList.push_back(regularToken);
				regularToken = new Token;
			
			}
		}
			
	}


	void clear() {
		delete regularToken;

		for (unsigned i = 0; i < tokenList.size(); i++) {
			delete tokenList.at(i);
		}
	}

public:

	Tokenizer(){ 
        _setVal(""); 
        regularToken = new Token;
    }
	Tokenizer(string value){
		_setVal(value);
        regularToken = new Token;
		execute();
    }
	~Tokenizer() {

		//delete regularToken pointer
		clear();
	}

	void setVal(string value) {
		_setVal(value);
	}

	bool execute(){
		parse();	//parses and tokenizes the values into a vector
		return true;
	}

	
	vector<Token*> getVector() {
		return this->tokenList;
	}
};


#endif
