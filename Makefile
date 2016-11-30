all: first

FLAGS = -Wall -Werror -ansi -pedantic -g
CC = g++

first:
	mkdir -p ./bin
	$(CC) $(FLAGS) src/main.cpp -o bin/rshell

clean: 
	rm -rf bin/
