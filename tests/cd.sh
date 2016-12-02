#!/bin/bash

echo "
##### BEGIN CD TEST #####
----- Test cd 1 ------"
echo -e 'mkdir test ; pwd ; cd test/ ; pwd
exit' | ../bin/rshell
echo "
----- Test cd 2 ------"
echo -e '  cd - ; pwd ; mkdir test2 ; mv test test2/; ls
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
echo -e ' pwd ; ls -a   
exit' | ../bin/rshell
echo "###### END  EXIT.H TEST #####
"
