#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <sys/stat.h>

class Executor : public Base {
private:
	//operator (connector) handlers
	bool previousState, firstTime; //previousState is for the connector to peek back whether the prev state is true/false
	int cases; //for the switch statement
	
	//fork handlers
	int pip[2]; // for closing cases on pipe
	pid_t child, c; //fork's value will be stored inside of the child, and c is used for waiting
	int cstatus; //cstatus is very crucial to determine the state of previousState (connector handlers)
//	Tokenizer * tokenizer; //a temporary variable that points to the actual tokenizer given from class Tokenizer
	vector <string> temp;
	
	void executor (unsigned i) {
		int size = (int) tokenizer->getVector().at(i)->getSubTokensVect().size();
		char ** args = new char * [size+1];
		
		for (unsigned j = 0 ; j< (unsigned)size; j++) {
			args[j] = new char [tokenizer->getVector().at(i)->getSubTokensVect().at(j).size()];
			strcpy(args[j], tokenizer->getVector().at(i)->getSubTokensVect().at(j).c_str());
		}
		
		args[size] = NULL; // putting NULL at the end of arguments, so execvp knows when to stop reading
		
		if ((isFirstTime())== 0) {				// if it's 0, this should be accessed by a newborn child!
			close(pip[0]);
			//cout<< "Child "<< getpid()<< " calls this: "; //for debugging
			previousState=execvp(args[0], args);
			
			//it should exit by the point above, otherwise it fails (below)
			previousState=false;
			cerr<< "-bash: \""<< args[0]<<"\" command not found!\n";
			kill(getpid(), SIGKILL);	//VERY IMPORTANT: kill the child that has failed to do execvp.. killing it without mercy is fine
			close(pip[1]);
		}
		else if (child == (pid_t)(-1)) {		// POSSIBLE to happen.. 
			cerr << "Failed to do fork\n";
		}
		else {									// if it's positive, this should be accessed by parent process(es)
			close(pip[1]);
			do {
				c = wait(&cstatus);
			}
			while (c== -1);
			if (cstatus!=0) previousState=false;	//determine the status of whether the child's execvp failed/not here
			else previousState=true;
			//cout<<"Parent said: child " << c << " exits. Now back to parent: " << getpid()<<endl; // for debugging
			close(pip[0]);
			
		}
		
		
		delete * args; //prevent memory leak
	}
	
	bool testExecutor(unsigned i) {
		struct stat test;
		int size = (int) tokenizer->getVector().at(i)->getSubTokensVect().size();
		string flag, path;
		
		if (size == 1) {
			cout<< "(TRUE without argument)"<<endl;
		}
		else if (size ==2) {
			flag = "-e"; //automatically assume the default -e, so we can still test
			path = tokenizer->getVector().at(i)->getSubTokensVect().at(1);
		}
		else {
			flag = tokenizer->getVector().at(i)->getSubTokensVect().at(1);
			path = tokenizer->getVector().at(i)->getSubTokensVect().at(2);
		}
		
		int status = stat(path.c_str(), &test);
		
		if (status ==-1) {
			cout<< "Path/File doesn't exist (FALSE)"<<endl;
			return false;
		}
		else if (flag =="-e") {
			cout<<"Path/File exist (TRUE)"<<endl;
			return true;
		}
		else if (flag == "-d") {
			if (S_ISDIR(test.st_mode)) {
				cout<<"It is a directory (TRUE)"<<endl;
				return true;
			}
			else {
				cout<<"It is NOT a directory (FALSE)"<<endl;
				return false;
			}
		}
		else if (flag == "-f") {
			if (S_ISREG(test.st_mode)) {
				cout<<"It is a file (TRUE)"<<endl;
				return true;
			}
			else {
				cout<<"It is NOT a file (FALSE)"<<endl;
				return false;
			}
		}
		else {
			cout<<"Flag "<<flag<<" is not recognized (FALSE)"<<endl;
			return false;
		}
//		cout<< "Flag is: " << flag <<endl;
//		
//		cout<< "Path is: " <<path<<endl;
//		cout<< "Status: "<<status<<endl;
		
//		return true;
	}
	
	int isFirstTime() { // this is just to set up a pipe
		if (firstTime) {
			pipe(pip);
			child = fork();
			firstTime=false;	//will never access this IF anymore.. ever..
			return child;
		}
		else {
			child = fork();
			return child;
		}
	}
	
	int operatorHandling (unsigned i) {
		if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "||") {
			return 0; // 0 is for OR
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "&&") {
			return 1; // 1 is for AND
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == ";") {
			return 2; // 2 is for Semicolon
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "exit") {
			return 3; // 3 is for exit
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "test") {
			return 7; // 7 is for test
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "" || tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "\0") {
			return 99; // if user enter nothing, do nothing
		}
		else return 4; // 4 is for normal operation
	}
	
public:
	Executor () {}
	Executor (Tokenizer * tokenizer) {
		this->tokenizer = tokenizer;
		this->previousState=true;
		this->firstTime=true;
		this->execute();
	}
	
	void setTokenizer (Tokenizer * tokenizer) {
		this->tokenizer = tokenizer;
		this->previousState=true;
		this->firstTime=true;
	}
	
	void setVector (vector <string> temp) {
		this->temp = temp;
		this->previousState=true;
		this->firstTime=true;
	}
	
	bool execute() {
		// cout<< "tokenizer's size is " << tokenizer->getVector().size()<<endl; // for debugging
//		if (tokenizer->getVector().size()==0) return false; // such as performing Ctrl+D
//		cout<<"not even here yet";
		for (unsigned i = 0; i < tokenizer->getVector().size(); i++)
		{
			cases = operatorHandling(i);
		//	cout << "-----i="<<i<<" & "<<previousState << " < prevState-----"<< getpid()<<"\n"; //for debugging
			switch (cases) {
				case 0: { // case ||
					if (previousState) {
						i++;		//should skip the next token if the previousState is true
					}
					else previousState=true;
				}; break;
					
				case 1: { // case &&
					if (previousState) {
									//if it's true, treat this and as if it's a semicolon
					}
					else i++;
				}; break;
					
				case 2: { // case ;
					previousState=true;
									// do nothing for this token, aka move on and assume previous state condition is true
				}; break;
					
				case 3: { // case exit
					return false;	//force exit this for loop
				}
					
				case 4: { // case normal operations
					if (previousState) {
						executor(i);//present the tokens to execvp
					}
				}; break;
				case 7: {
					testExecutor(i);
				};break;
				default: break; //do nothing
			}
		}
		
		//cout<< "###########  EXIT THE EXECUTE  #############\n";	//for debugging
		return true;
	}
};

#endif