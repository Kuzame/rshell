#!/bin/bash

echo "
##### BEGIN EXIT.H TEST ##### 
----- Test commented_codes.h 1 ------"
echo -e 'ls #asdf' | ../bin/rshell
echo "
----- Test commented_codes.h 2 ------"
echo -e "echo hi #asdf asdf" | ../bin/rshell
echo "
----- Test commented_codes.h 3 ------"
echo -e ' echo \" sup \" #asdf asdf '| ../bin/rshell
echo "###### END  EXIT.H TEST #####
"