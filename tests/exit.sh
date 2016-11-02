#!/bin/bash

echo 'ls -l; exit' | ../bin/rshell
echo 'ls -l && exit' | ../bin/rshell