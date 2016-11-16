/*
‐Assignment 3
‐Mario Gonzalez Salazar

*/
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
//#include <pwd.h>
#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>
#include <signal.h>

#include "Base.h"
#include "Token.h"
//#include "Executor.h"
//#include "Tokenizer.h"
#include "BinaryTokenCmdTree.h"


using namespace std;


void enableDebug(bool bvalue)
{
	if (!bvalue) return;

	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// Turn on leak-checking bit.
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	// Turn off CRT block checking bit.
	tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;

	// Set flag to the new value.
	_CrtSetDbgFlag(tmpFlag);
}

int main()
{
// 	bool valid = false; //for input validation
// 	ifstream inputFile;	//for input file
// 	int a, b, c;		//for temporary storage of read input
	enableDebug(true);
	//Token* temp = new Token;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	BinaryTokenCmdTree *tree1 = new BinaryTokenCmdTree;	//tree objects



	//tests with brackets

	//string input = "  echo Hello World||ls -a&& [ -a main.cpp ] ; ls";
	//string input = "  echo Hello World||ls -a&& [-a main.cpp] ; ls";
	//string input = "  echo Hello World || ls -a && [-a main.cpp];ls  ";
	//string input = "  echo Hello World||ls -a&& [-a main.cpp]  ";
	//string input = "  echo Hello World||ls -a&&[-a main.cpp]";
	


	//tests with parenthesis and brackets

	//string input = " [ -l dirName ] && ( test -a dirName || ls -a ) ";
	//string input = " [ -l dirName ] && (test -a dirName || ls -a) ";
	//string input = " [ -l dirName ] && ( test -a dirName || ls -a )";
	//string input = " [ -l dirName ] && (test -a dirName || ls -a)";
	

	//tests with parenthesis and embedded brackets

	//string input = " ls && ( [ -l dirName ] || [ -f main.cpp ] )  ";
	//string input = " ls && ( [ -l dirName ] || [ -f main.cpp ] )";

	//string input = " ls && ([ -l dirName ] || [ -f main.cpp ]) ";
	//string input = " ls && ([ -l dirName ] || [ -f main.cpp ])";

	//string input = " ls && ([-l dirName] || [ -f main.cpp] ) ";
	//string input = " ls && ([-l dirName] || [ -f main.cpp] )";

	//string input = " ls && ([-l dirName] || [ -f main.cpp]) ";
	string input = " ls && ([-l dirName] || [-f main.cpp])";
	
	//getline(cin, input);

	tree1->parseAndGenerateCmdTree(input);
	//tree1->execute();

// 	Token * token1 = new Token();
// 	Token * token2 = new Token();
// 	Token * token3 = new Token();
// 	Token * token4 = new Token();
// 	Token * token5 = new Token();
// 	Token * token6 = new Token();
// 	Token * token7 = new Token();
// 
// 
// 	token1->appendValue("ls");
// 	token1->appendValue("-a");
// 
// 	token2->appendValue("&&");
// 
// 	token3->appendValue("echo");
// 	token3->appendValue("Hello World");
// 
// 	token4->appendValue("||");
// 
// 	token5->appendValue("cat");
// 	token5->appendValue("main.cpp");
// 
// 	token6->appendValue(";");
// 
// 	token7->appendValue("test");
// 	token7->appendValue("-e");
// 	token7->appendValue("-f");
// 	token7->appendValue("-d");
// 
// 	tree1->insert(token1);
// 	tree1->insert(token2);
// 	tree1->insert(token3);
// 	tree1->insert(token4);
// 	tree1->insert(token5);
// 	tree1->insert(token6);
// 	tree1->insert(token7);


// 	//return heap space
 	delete tree1;
 	//delete tree2;
	
	system("pause");
	return 0;
}
