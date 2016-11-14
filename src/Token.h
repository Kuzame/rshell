#ifndef _TOKEN_H
#define _TOKEN_H

using namespace std;

class Token : public Base
{
private:
	vector<string> subTokens;

	void _appendValue(string value) {
		this->subTokens.push_back(value);
	}



public:
	//constructors and destructors
	Token() {}

	//sets values and calls execute in order to generate and format members
	Token(string value) {
		this->appendValue(value);
	}
	~Token() {
		subTokens.clear();
	}

	int getSize() {
		return ((int)this->subTokens.size());
	}

	vector<string> getSubTokensVect() {
		return this->subTokens;
	}

	void appendValue(string value) {
		_appendValue(value);
	}

	string at(int i) {
		string temp = subTokens.at(i);
		return temp;
	}

	bool execute() {
		return true;
	}

	bool isAnd() {
		return subTokens.at(0) == "&&";
	}

	bool isOr() {
		return subTokens.at(0) == "||";
	}

	bool isSemicolon() {
		return subTokens.at(0) == ";";
	}

	bool isExit() {
		return subTokens.at(0) == "exit";
	}

	bool isTest() {
		return subTokens.at(0) == "test";
	}
};


#endif
