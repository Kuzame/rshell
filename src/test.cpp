//
//  main.cpp
//  Test2
//
//  Created by Adrian Harminto on 10/29/16.
//  Copyright © 2016 Adrian Harminto. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(void) {
    pid_t  child;
    int    cstatus;  /* Exit status of child. */
    pid_t  c;        /* Pid of child to be returned by wait. */
    char *args [8];   /* List of arguments for the child process. */
    char *test = "testat";
    /* Set up arguments to run an exec in the child process.  */
    /* (This example runs the "ls" program with "-l" option.) */
    args[0] = "-q";   args[1] = "-w";
    args[2] = "-e";   args[3]=NULL;   /* Indicates the end of arguments. */
    
    args[4]="echo"; args[5]= NULL; args[6]=NULL;
    if ((child = fork()) == 0) { /* Child process. */
        std::cout << "Child: PID of Child = "<<getpid() <<"\n";
        execvp(args[4], args); /* arg[0] has the command name. */
        /* If the child process reaches this point, then  */
        /* execvp must have failed.                       */
        fprintf(stderr, "Child process could not do execvp.\n");
        return 1;
    }
    else { /* Parent process. */
        if (child == (pid_t)(-1)) {
            fprintf(stderr, "Fork failed.\n"); return (1);
        }
        else {
            c = wait(&cstatus); /* Wait for child to complete. */
            printf("Parent: Child  %ld exited with status = %d\n",
                   (long) c, cstatus);
        }
    }
    
    return  0;
} /* End of main. */