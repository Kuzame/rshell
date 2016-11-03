#!/bin/bash

echo "
##### BEGIN EXIT.H TEST #####
----- Test exit.h 1 ------"
echo -e 'exit' | ../bin/rshell
echo "
----- Test exit.h 2 ------"
echo -e "ls -l; exit" | ../bin/rshell
echo "
----- Test exit.h 3 ------"
echo -e ' echo " Heyyy!.. " && syntaxerror ; exit' | ../bin/rshell
echo "
----- Test exit.h 4 ------"
echo -e 'echo exit ; lol && asdfasdf' | ../bin/rshell
echo "
----- Test exit.h 5 ------"
echo -e 'asdfasdf   &&   wuuuttt  ;  exit  ||  gimme  octocatzz ' | ../bin/rshell
echo "###### END  EXIT.H TEST #####
"