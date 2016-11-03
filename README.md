# RShell



RShell is a program that emulates the interface of a terminal. The program uses a parser to handle chained commands. It also uses syscalls and execvp in order to perform the given commands and connectors. The user's system name is displayed to the screen. 

## Requirements
- RShell must run on a UNIX-based system
- Must have g++ installed
- git needs to be installed

### Accessing and running the program [from the rshell directory]
```sh
$ git clone https://github.com/mario773199/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```

 
### Valid connectors
    ;
    ||
    &&
    #

### Known Bugs
- Users cannot enter commands with quotation marks within quotation marks or the program will not give the expected output
- Arrow keys do not navigate through the text currently being typed (must use backspace to go back)
- Functionality to change directories is not implemented (will result in unknown command error)


### Todos

 - Handle parenthesis and order of operations
 - Handle user arrow keys to navigate input

License
----

GNU General Public License v3.0
