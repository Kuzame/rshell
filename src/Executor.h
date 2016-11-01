#ifndef EXECUTOR_H
#define EXECUTOR_H

//#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>

class Executor : public Base {
private:
    //operators handlers
    bool previousState;
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////pid_t child, c;
    int cstatus;
    Tokenizer * tokenizer;
    vector <const char*> command;
    
    //tested and worked wonderfully
    void whiteSpaceHandler (unsigned i) {
        char * temp = new char [this->tokenizer->getVector().at(i)->getValue().length()+1];
        std::strcpy(temp, this->tokenizer->getVector().at(i)->getCharPtr()); //copying the const char to modifiable char
        char * withoutSpace = std::strtok(temp, " "); // place the initial string before a whitespace
        
        while (withoutSpace != 0) {
            command.push_back(withoutSpace);
            withoutSpace = std::strtok(NULL, " "); // remove the string that has been pushed when it's still reading whitesp
        }
        
        delete[] temp; //prevent memory leak
    }
    
    void executor () {
//        char * args [] = new char * [command.size()+1];
//        std::strcpy(args, command.at(0));
//        if ((child = fork() )== 0) {
//            
//        }
    }
    
public:
    Executor (Tokenizer * tokenizer) {
        this->tokenizer = tokenizer;
        this->previousState=true;
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
    
    void printCommands() {
        whiteSpaceHandler(0);
        for (unsigned i = 0; i < command.size(); i++)
        {
            cout << "."<< command.at(i) << ".\n";
        }
    }
    
    bool execute() {
        
        return true;
    }
    
    
};



#endif