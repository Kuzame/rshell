#ifndef EXECUTOR_H
#define EXECUTOR_H

class Executor : public Base {
private:
	//operator (connector) handlers
	bool previousState, firstTime; //previousState is for the connector to peek back whether the prev state is true/false
	int cases; //for the switch statement
	
	//fork handlers
	int pip[2]; // for closing cases on pipe
	pid_t child, c; //fork's value will be stored inside of the child, and c is used for waiting
	int cstatus; //cstatus is very crucial to determine the state of previousState (connector handlers)
	Tokenizer * tokenizer; //a temporary variable that points to the actual tokenizer given from class Tokenizer
	
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
		else if (tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "" || tokenizer->getVector().at(i)->getSubTokensVect().at(0) == "\0") {
			return 3; // We don't want to process a NULL..
		}
		else return 4; // 3 is for normal operation
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
	
	bool execute() {
		// cout<< "tokenizer's size is " << tokenizer->getVector().size()<<endl; // for debugging
		if (tokenizer->getVector().size()==0) return false; // such as performing Ctrl+D
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
				default: cout<< "Something is wrong#@!\n"; break; //we shouldn't ever get here unless someone hacks the memory..
			}
		}
		
		//cout<< "###########  EXIT THE EXECUTE  #############\n";	//for debugging
		return true;
	}
};

#endif