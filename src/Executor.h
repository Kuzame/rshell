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
	vector <string> temp; //previously, we use tokenizer. Now we'll get simpler data, a vector string inside of token
	
	void executor (unsigned i) { // for regular execution, when we need execvp to check most cases
		int size = (int) temp.size();
		char ** args = new char * [size+1];
		
		for (unsigned j = 0 ; j< (unsigned)size; j++) {
			args[j] = new char [temp.at(j).size()];
			strcpy(args[j], temp.at(j).c_str());
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
			close(pip[0]);
			
		}
		
		
		delete * args; //prevent memory leak
	}
	
	bool testExecutor(unsigned i) { // for the special test cases
		struct stat test;
		int size = (int) temp.size();
		string flag, path;
		
		if (size == 1) {
			cout<< "(TRUE without argument)"<<endl;
		}
		else if (size ==2) {
			flag = "-e"; //automatically assume the default -e, so we can still test. Ex, it is valid to check: test /usr/
			path = temp.at(1);
		}
		else {
			flag = temp.at(1);
			path = temp.at(2);
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
		if (temp.at(0) == "test") {
			return 2; // 2 is for test
		}
		else if (temp.at(0) == "" || temp.at(0) == "\0") {
			return 99; // if user enter nothing, do nothing
		}
		else return 1; // 1 is for normal operation
	}
	
public:
	Executor () {}
	Executor (vector <string> temp) {
		this->temp = temp;
		this->previousState=true;
		this->firstTime=true;
		this->execute();
	}
	
	void setVector (vector <string> temp) {
		this->temp = temp;
		this->previousState=true;
		this->firstTime=true;
	}
	
	bool execute() {
        bool executionValidity;
        cases = operatorHandling(0);
			switch (cases) {
				case 1: { // case normal operations
					if (previousState) {
						executor(0);//present the vector of strings to execvp
                        executionValidity = previousState;
					}
				}; break;
				case 2: {
					executionValidity = testExecutor(0);
				};break;
				default: executionValidity = true; break; //do nothing
			}
		return executionValidity;
	}
};

#endif
