#!/bin/bash

echo "
##### BEGIN COMMENTED_CODES.H TEST ##### 
----- Test commented_codes.h 1 ------"
echo -e 'test -e /usr #; ls
exit' | ../bin/rshell
echo "
----- Test commented_codes.h 2 ------"
echo -e '(test -asdf bin) # && pwd
exit' | ../bin/rshell
echo "
----- Test commented_codes.h 3 ------"
echo -e 'test -e #asdf
exit' | ../bin/rshell
echo "
----- Test commented_codes.h 4 ------"
echo -e 'echo #Hello WOrld ; test -e /#
exit' | ../bin/rshell
echo "
----- Test commented_codes.h 5 ------"
echo -e ' asdf #test -e /usr/bin ###### 
exit'| ../bin/rshell
echo "###### END  COMMENTED_CODES.H TEST #####
"