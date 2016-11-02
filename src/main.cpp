#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Executor.h"
#include <pwd.h>

using namespace std;

int main(){
	//extra credit part, components needed for getting user's username and local machine's name
	string userLogin, result;
	int charSize=100;
	char localhost[charSize];
	int validHost = gethostname(localhost, charSize);
	struct passwd *pwd = getpwuid(getuid());
	
	if (validHost!= -1 && pwd!=NULL) {
		userLogin = pwd->pw_name;
		result = userLogin + "@" + localhost + "$ ";
	}
	else {
		cerr<< "Failed to obtain user's username and local machine's name\n";
		result = "$ ";
	}
	
	//Basics needed to perform rshell
	string input;
	bool exitState=true;
	Executor * execute = new Executor();
	
	do {
		cout << result; //printing the extra credit here
		//gets next command
		getline(cin, input);
		
		
		Tokenizer * tokenizer = new Tokenizer(input);
//		//sets value inside toknizer class
//		tokenizer->setVal(input);
//		//executes the tokenizing operation
//		tokenizer->execute();
//		vector<Token *> temp = tokenizer->getVector();
		
		
 		//sets value inside the execute class
 		execute->setTokenizer(tokenizer);
 		//executes the command operations inside execute
 		exitState = execute->execute();
		delete tokenizer;
		input = '\0';
	}
	while (exitState);

	//delete execute;
	
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