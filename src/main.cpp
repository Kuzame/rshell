#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"
#include "Tokenizer.h"
//#include "Executor.h"

using namespace std;

int main(){
	string input;
	cout << "do it\n>>";

	getline(cin, input);
    
	Tokenizer * temp = new Tokenizer(input);

	vector<Token*> tokenizervect = temp->getVector();

    
	for (unsigned i = 0; i < tokenizervect.size(); i++)
	{
		cout << i << ">> ";
		//vector<const char *> temporarydfsdfsdfsdf = tokenizervect.at(i)->getSubTokensVect();
		for (unsigned j = 0; j < tokenizervect.at(i)->getSubTokensVect().size(); j++)
		{
			cout << "." << tokenizervect.at(i)->getSubTokensVect().at(j) << "." << endl;
		}
	}
    
	system("pause");
	return 0;
}