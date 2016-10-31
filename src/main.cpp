#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Base.h"
#include "Token.h"
#include "TokenContainer.h"
#include "Tokenizer.h"
#include "Executor.h"

using namespace std;

int main(){
	string input;
	cout << "do it\n>>";

	getline(cin, input);

	Tokenizer* temp = new Tokenizer(input);
	
	for (unsigned i = 0; i < temp->getVector().size(); i++)
	{
		cout << "." << temp->getVector().at(i)->getValue() << ".\n";
	}
	system("pause");
	return 0;
}