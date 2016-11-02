#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Executor.h"
//#include "Executor.h"

using namespace std;

int main(){
	string input;
	bool exitState;
	Tokenizer * tokenizer = new Tokenizer();
	Executor * execute = new Executor();

	cout << "$ ";
	
	
	do {
		//gets next command
		getline(cin, input);
		
		//sets value inside toknizer class
		tokenizer->setVal(input);
		//executes the tokenizing operation
		tokenizer->execute();

		//sets value inside the execute class
		execute->setVal(tokenizer);
		//executes the command operations inside execute
		exitState = execute->execute();

	}
	while (exitState);

	delete tokenizer;
	delete execute;
	
	//execute->execute();
//	vector<Token*> tokenizervect = temp->getVector();
//	
//    
//	for (unsigned i = 0; i < tokenizervect.size(); i++)
//	{
//		cout << i << ">>";
//		for (unsigned j = 0; j < tokenizervect.at(i)->getSubTokensVect().size(); j++)
//		{
//			cout << tokenizervect.at(i)->getSubTokensVect().at(j) << endl;
//		}
//	}

	system("pause");
	return 0;
}