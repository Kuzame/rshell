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
$ git checkout hw3
$ make
$ bin/rshell
```

 
### Valid connectors and operators
    ;
    ||
    &&
    #
    []
    ()
    cd
    cd -

### Known Bugs
- Commands with incomplete parenthesis or brackets do not execute properly
- Arrow keys do not navigate through the text currently being typed (must use backspace to go back)

### Todos

 - Handle user arrow keys to navigate input

### Updates
 - Precedence and cd commands are now fully functional
License
----

GNU General Public License v3.0
