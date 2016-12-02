#!/bin/bash

echo "
##### BEGIN PRECEDENCE_TEST.H TEST #####
----- Test precedence_test.h 1 ------"
echo -e '(ls) 
exit' | ../bin/rshell
echo "
----- Test precedence_test.h 2 ------"
echo -e '(ls -l || asdf) 
exit' | ../bin/rshell
echo "
----- Test precedence_test.h 3 ------"
echo -e ' echo "Hello World" && (test -e main.cpp || [-e rshell])
exit' | ../bin/rshell
echo "
----- Test precedence_test.h 4 ------"
echo -e ' echo " ( Sup Doggie  )  " && (asdf)
exit' | ../bin/rshell
echo "
----- Test precedence_test.h 5 ------"
echo -e '   asdf || (pwd && errorzzz) || exit 
exit' | ../bin/rshell
echo "###### END  PRECEDENCE_TEST.H TEST #####
"