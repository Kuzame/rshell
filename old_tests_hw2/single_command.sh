#!/bin/bash

echo "
##### BEGIN SINGLE_COMMAND.H TEST #####
----- Test single_command.h 1 ------"
echo -e 'pwd' | ../bin/rshell
echo "
----- Test single_command.h 2 ------"
echo -e "ls" | ../bin/rshell
echo "
----- Test single_command.h 3 ------"
echo -e 'cd' | ../bin/rshell
echo "
----- Test single_command.h 4 ------"
echo -e 'mkdir test' | ../bin/rshell
echo "
----- Test single_command.h 5 ------"
echo -e 'rmdir test' | ../bin/rshell
echo "###### END  SINGLE_COMMAND.H TEST #####
"