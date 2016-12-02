#!/bin/bash

echo "
##### BEGIN EXIT.H TEST #####
----- Test exit.h 1 ------"
echo -e 'exit && ls && pwd
exit' | ../bin/rshell
echo "
----- Test exit.h 2 ------"
echo -e 'test -e asdfasdf || exit
exit ' | ../bin/rshell
echo "
----- Test exit.h 3 ------"
echo -e ' test exit || (ls -l && exit)
exit' | ../bin/rshell
echo "
----- Test exit.h 4 ------"
echo -e 'echo exit ; (lol && ls -l) || exit 
exit' | ../bin/rshell
echo "
----- Test exit.h 5 ------"
echo -e '   test   -e  /usr  &&  (pwd  ||  exit) 
exit' | ../bin/rshell
echo "###### END  EXIT.H TEST #####
"