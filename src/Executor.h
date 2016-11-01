#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

class Executor : public Base {
private:
	//operators handlers
	bool previousState;
	int cases;
	
	pid_t child, c;
	int cstatus;
	Tokenizer * tokenizer;
	vector <const char*> commands;

	void executor (unsigned i) {
		int size = (int) tokenizer->getVector().at(i)->getSubTokensVect().size();
		char * args [size+1];
		
		for (unsigned j = 0 ; j< size; j++) {
			args[j] = new char [tokenizer->getVector().at(i)->getSubTokensVect().at(j).size()];
			strcpy(args[j], tokenizer->getVector().at(i)->getSubTokensVect().at(j).c_str());
		}
		
		args[size] = NULL; // putting NULL at the end of arguments, so execvp knows when to stop reading
		
		// Will yield ERROR if we put: lsa || echoHello && echo hi
		// Something's wrong because the child is executing its task
		// Solution: Maybe have something to do with KILL the child's process
		if ((child = fork())== 0) {					// if it's 0
			// cout<< "Parent: child "<< getpid()<< " is created"<< "[fork]="<<child<< "\n"; //for debugging
			previousState=execvp(args[0], args);
			
			//it should exit by the point above, otherwise it fails (below)
			previousState=false;
			cerr<< "Failed to do execvp\n";
		}
		else {										// if it's -1
			if (child == (pid_t)(-1)) {
				cerr << "Failed to do fork\n";
			}
			else {									// if it's positive
				
				c = wait(&cstatus);
				//cout<<"--for debugging-- Parent: child " << c << " exits with status " << cstatus<<endl; // for debugging
			}
		}
		
		delete * args; //prevent memory leak
    }
	
	void vectorSetter(unsigned i) {
//		for (unsigned j = 0 ; j<tokenizer->getVector().at(i)->getSubTokensVect().size(); j++) {
//			commands.push_back(tokenizer->getVector().at(i)->getSubTokensVect().at(j));
//		}
	}
	
	int operatorHandling (unsigned i) {
		if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "||") {
			//cout << "is ||!";
			return 0; // 0 is for OR
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "&&") {
			//cout << "is &&!";
			return 1; // 1 is for AND
		}
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == ";") {
			//cout << "is ;!";
			return 2; // 2 is for Semicolon
		}
		else return 3; // 3 is for normal operation
	}
    
public:
    Executor (Tokenizer * tokenizer) {
        this->tokenizer = tokenizer;
        this->previousState=true;
		this->execute();
    }
    
    void setTokenizer (Tokenizer * tokenizer) {
        this->tokenizer = tokenizer;
    }
    
    void print () {
        for (unsigned i = 0; i < tokenizer->getVector().size(); i++)
        {
            cout <<  tokenizer->getVector().at(i)->getValue() << "\n";
        }
    }
//    
//    void printCommands() {
//        whiteSpaceHandler(0);
//        for (unsigned i = 0; i < command.size(); i++)
//        {
//            cout << "."<< command.at(i) << ".\n";
//        }
//    }
    
	bool execute() {
		// cout<< "tokenizer's size is " << tokenizer->getVector().size()<<endl; // for debugging
		for (unsigned i = 0; i < tokenizer->getVector().size(); i++)
		{
			cases = operatorHandling(i);
		//	cout << "i="<<i<<" & "<<previousState << " < prevState\n"; //for debugging
			switch (cases) {
				case 0: { // case ||
					if (previousState) {
						i++;
					}
					else previousState=true;
				}; break;
					
				case 1: { // case &&
					if (previousState) {
						//treat this and as if it's a semicolon
					}
					else i++;
				}; break;
					
				case 2: { // case ;
					// do nothing for this token, aka move on without any condition
				}; break;
					
				case 3: { // case normal operations
					if (previousState) {
						vectorSetter(i);
						executor(i);
					}
				}; break;
				default: cout<< "Something is wrong#@!\n"; break;
			}
		}
		
		//cout<< "###########  EXIT THE EXECUTE  #############\n";	//for debugging
        return true;
    }
};

#endif