#!/bin/bash

echo "
##### BEGIN CD TEST #####
----- Test cd 1 ------"
echo -e 'mkdir test w; pwd ; cd test/ ; pwd
exit' | ../bin/rshell
echo "
----- Test cd 2 ------"
echo -e ' cd test; cd - ; pwd ; mkdir test2 ; mv test test2/; ls
exit ' | ../bin/rshell
echo "
----- Test cd 3 ------"
echo -e ' cd test2 ; pwd ; cd  test ; pwd ; cd - ; pwd ; ls ; rm -r test ; ls
exit' | ../bin/rshell
echo "
----- Test cd 4 ------"
echo -e ' cd test2 ; ls ; cd .. ; rm -r test2
exit' | ../bin/rshell
echo "
----- Test cd 5 ------"
echo -e ' mkdir New\ Folder ; (cd New\ Folder && cd - ) && rm -r New\ Folder 
exit' | ../bin/rshell
echo "###### END CD TEST #####
"
