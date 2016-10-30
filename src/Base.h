#ifndef _BASE_H_
#define _BASE_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Base
{
protected:
    bool execute() = 0; //Adrian: either we need a string parameter here, or remove the string parameter in its children classes
};


#endif
