all: first

FLAGS = -Wall -Werror -ansi -pedantic
CC = g++

first:
	mkdir -p ./bin
	$(CC) $(FLAGS) src/main.cpp -o bin/rshell