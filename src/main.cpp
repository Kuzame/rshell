/*	
 [This rshell is created by:]
 Adrian Harminto
 Mario Salazar
*/

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "Base.h"
#include "Token.h"
#include "Executor.h"
#include "BinaryTokenCmdTree.h"

using namespace std;
void getInfo(string *result);

int main(){
	string result;
	getInfo(&result);
	
	//Basics needed to perform rshell
	bool exitState = true;
	//BinaryTokenCmdTree *tree1 = new BinaryTokenCmdTree();	//tree objects
	string input ; // = "echo Hello World && (test -e main.cpp || [-e rshell])";
	int checkSpaces;
	char tempChar [256];
	strcpy(tempChar, getcwd(tempChar, sizeof(tempChar)));
	setenv("OLDPWD", tempChar, 1);
	
	while (exitState) {
		BinaryTokenCmdTree *tree1 = new BinaryTokenCmdTree();	//tree objects
		checkSpaces=-1;
		cout<<result;
		getline(cin, input);
		checkSpaces = (int)input.find_first_not_of(" "); // to prevent error when user inputs only space
		
		if (input != "" && checkSpaces != -1) { //and if the user inputs nothing
			tree1->parseAndGenerateCmdTree(input);
			tree1->execute();
			exitState = tree1->getContinueExecution();
			//tree1->clear();
			delete tree1;
		}
		input="";

	}
	cout<< "The program exits!\n";
	return 0;
}

void getInfo(string *result) {
	//Components needed for getting user's username and local machine's name
	string userLogin;
	int charSize=100;
	char * localhost = new char [charSize];
	int validHost = gethostname(localhost, charSize);//obtaining local machine's name
	struct passwd *pwd = getpwuid(getuid());
	
	if (validHost!= -1 && pwd!=NULL) {
		userLogin = pwd->pw_name;		//obtaining user's login name
		*result = userLogin + "@" + localhost + "$ ";
	}
	else { // in case access or permission is denied
		cerr<< "Failed to obtain user's username and local machine's name\n";
		*result = "$ ";
	}
}
