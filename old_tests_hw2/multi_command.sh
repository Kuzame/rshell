#!/bin/bash

echo "
##### BEGIN MULTI_COMMAND.SH TEST #####
----- Test multi_command.h 1 ------"
echo -e 'ls  || pwd && echo Hi' | ../bin/rshell
echo "
----- Test multi_command.h 2 ------"
echo -e "echo \"Hey there!\" || ls ; pwd" | ../bin/rshell
echo "
----- Test multi_command.h 3 ------"
echo -e 'ls && ping google.com -c 2' | ../bin/rshell
echo "###### END  MULTI_COMMAND.SH TEST #####
"