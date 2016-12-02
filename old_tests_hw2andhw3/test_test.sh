#!/bin/bash

echo "
##### BEGIN TEST_TEST.H TEST #####
----- Test test_test.h 1 ------"
echo -e 'test hello world 
exit' | ../bin/rshell
echo "
----- Test test_test.h 2 ------"
echo -e 'mkdir HelloWorld && test -d HelloWorld && rmdir HelloWorld 
exit' | ../bin/rshell
echo "
----- Test test_test.h 3 ------"
echo -e ' touch virus.exe && test -f virus.exe && rm virus.exe 
exit' | ../bin/rshell
echo "
----- Test test_test.h 4 ------"
echo -e ' ls && ([-e asdfasdf ]|| [-e /usr]) && exit 
exit' | ../bin/rshell
echo "
----- Test test_test.h 5 ------"
echo -e '  [test test test test test] || exit 
exit' | ../bin/rshell
echo "###### END  TEST_TEST.H TEST #####
"