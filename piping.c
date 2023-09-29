#include "piping.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>




//Checks whether | character has been used anywhere in input
int pipe_check(char** args,int num_args){

    for(int i = 0; i < num_args; i++){

        if(strcmp(args[i],"|") == 0){
            return 1;
        }
    }
    return 0;
}

void create_pipe(char** args, int num_args){

    char* command_one[100] = {NULL};     // Split our commands 
    char* command_two[100] = {NULL};

    int count_one = 0;
    int count_two = 0;

    while(strcmp(args[count_one],"|") != 0){
        command_one[count_one] = args[count_one];       // Anything before the | is command one
        count_one++;

    }

    count_one++;    //Skip the | character


    while(args[count_one]!= NULL){
        command_two[count_two] = args[count_one];       // Anything after | is command two
        count_one++;
        count_two++;    
    }

    if(qualifyPath(&(command_one[0])) == 1){}
    if(qualifyPath(&(command_two[0])) == 1){}

    printf("%s",command_one[0]);
    printf("%s",command_two[0]);


    int pipe_fd[2];
    pid_t child_pid1, child_pid2;

    if(pipe(pipe_fd) == -1){                        // Create the pipe and put the file descriptors in pipe_fd
        printf("Failed to establish pipe for |");
        exit(1);
    }

    child_pid1 = fork();         // Fork to child process to do first command

    if(child_pid1 == 0){
        //close(pipe_fd[0]);   //Close read end of pipe


        dup2(pipe_fd[1], STDOUT_FILENO); // close first write end
        //close(pipe_fd[1]); //close original write

        execve(command_one[0],command_one,NULL); //execute command one
    }
    else{
        
        child_pid2 = fork();    //fork the second child process
        
        
        if(child_pid2 == 0){
        
        //close(pipe_fd[1]);

        dup2(pipe_fd[0], STDIN_FILENO); //Turn write end of pipe to standard output
        //close(pipe_fd[0]);

            char buffer[500];
            ssize_t bytes;
            bytes = read(pipe_fd[0],buffer,sizeof(buffer)); //read output of child process into buffer

            if(bytes == -1){
                printf("Failed to read input from child1 process");
                exit(1);
            }

        for(int i = 0; i < 100; i++){
            if(command_two[i] == NULL){
                command_two[i] = buffer;
                break;
            }
        }

        execve(command_two[0],command_two,NULL);
        }
    else{
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        //waitpid(child_pid1,NULL,0);
        //waitpid(child_pid2,NULL,0);

    }
    }




}
