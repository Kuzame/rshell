#!/bin/bash

echo "
##### BEGIN EXIT.H TEST #####
----- Test exit.h 1 ------"
echo -e 'ls #asdf' | ../bin/rshell
echo "
----- Test exit.h 2 ------"
echo -e "echo hi #asdf asdf" | ../bin/rshell
echo "
----- Test exit.h 3 ------"
echo -e ' echo " sup " #asdf asdf | ../bin/rshell
echo -e 'asdfasdf   &&   wuuuttt  ;  exit  ||  gimme  octocatzz ' | ../bin/rshell
echo "###### END  EXIT.H TEST #####
"