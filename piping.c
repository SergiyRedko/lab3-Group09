#include "piping.h"
#include "qualifyPath.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Checks whether | character has been used anywhere in input
int pipe_check(char **args, int num_args)
{

    for (int i = 0; i < num_args; i++)
    {

        if (strcmp(args[i], "|") == 0)
        {
            return 1;
        }
    }
    return 0;
}

void create_pipe(char **args, int num_args)
{

    char *command_one[100] = {NULL}; // Split our commands
    char *command_two[100] = {NULL};

    int count_one = 0;
    int count_two = 0;

    while (strcmp(args[count_one], "|") != 0)
    {
        command_one[count_one] = args[count_one]; // Anything before the | is command one
        count_one++;
    }

    count_one++; // Skip the | character

    while (args[count_one] != NULL)
    {
        command_two[count_two] = args[count_one]; // Anything after | is command two
        count_one++;
        count_two++;
    }

    if (qualifyPath(&(command_one[0])) != 1)
    {
        printf("Error in qualifypath when piping");
        exit(1);
    }
    if (qualifyPath(&(command_two[0])) != 1)
    {
        printf("Error in qualifypath when piping");
        exit(1);
    }

    int pipe_fd[2];
    pid_t child_pid1, child_pid2;

    if (pipe(pipe_fd) == -1)
    { // Create the pipe and put the file descriptors in pipe_fd
        printf("Failed to establish pipe for |");
        exit(1);
    }

    child_pid1 = fork(); // Fork to child process to do first command

    if (child_pid1 == 0)
    {
        close(pipe_fd[0]);   //Close read end of pipe

        dup2(pipe_fd[1], STDOUT_FILENO); // close first write end
        close(pipe_fd[1]); //close original write

        if(execve(command_one[0], command_one, NULL) == -1){
            printf("Error executing command");
            exit(1);
        } // execute command one
    }
    else
    
    {
        close(pipe_fd[1]); 
        //printf("%d\n", child_pid1); DIAGNOSTICS
        int status;
        waitpid(child_pid1, &status, 0);
        //printf("Wait complete %d\n", child_pid1); DIAGNOSTICS

    }
    
    child_pid2 = fork(); // fork the second child process

    if (child_pid2 == 0)
    {

        dup2(pipe_fd[0], STDIN_FILENO); // Turn write end of pipe to standard output
        close(pipe_fd[0]);

        if(execve(command_two[0], command_two, NULL) == -1){
            printf("Error executing command");
            exit(1);
        }
    }
    else
    {
        //printf("%d\n", child_pid2); DIAGNOSTICS
        int status;    
        waitpid(child_pid2, &status, 0);
        //printf("Wait complete %d\n", child_pid2); DIAGNOSTICS
        close(pipe_fd[0]);
        close(pipe_fd[1]);

    }


}
