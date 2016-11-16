/*	
 [This rshell is created by:]
 Adrian Harminto
 Mario Salazar
*/

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
//#include "Tokenizer.h"
#include "Executor.h"
#include "BinaryTokenCmdTree.h"

using namespace std;

int main(){
	//----- <part extra credit> -----
	//Components needed for getting user's username and local machine's name
	string userLogin, result;
	int charSize=100;
	char * localhost = new char [charSize];
	int validHost = gethostname(localhost, charSize);//obtaining local machine's name
	struct passwd *pwd = getpwuid(getuid());
	
	if (validHost!= -1 && pwd!=NULL) {
		userLogin = pwd->pw_name;		//obtaining user's login name
		result = userLogin + "@" + localhost + "$ ";
	}
	else { // in case access or permission is denied
		cerr<< "Failed to obtain user's username and local machine's name\n";
		result = "$ ";
	}
	//----- </part extra credit> -----
	
	
	//Basics needed to perform rshell
	string input;
	//bool exitState=true;
//	Executor * execute = new Executor();
	BinaryTokenCmdTree *tree1 = new BinaryTokenCmdTree();	//tree objects
	string input2 = "echo Hello World && (test -e rshell && [-e ~/Documents])      ";
	
	
	tree1->parseAndGenerateCmdTree(input2);
	tree1->execute();

	
	cout<< "The program exits!\n";
	return 0;
}
