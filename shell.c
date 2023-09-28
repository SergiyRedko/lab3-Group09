#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"

#define BUFLEN 1024

//To Do: This base file has been provided to help you start the lab, you'll need to heavily modify it to implement all of the features

int main() {
    char buffer[BUFLEN];
    char* parsedinput;
    char* args[3];
    char newline;

    printf("Welcome to the Group09 shell! Enter commands, enter 'quit' to exit\n");
    do {
        //Print the terminal prompt and get input
        printf("$ ");
        char *input = fgets(buffer, sizeof(buffer), stdin);
        if(!input)
        {
            fprintf(stderr, "Error reading input\n");
            return -1;
        }
        
        //Clean and parse the input string
        parsedinput = (char*) malloc(BUFLEN * sizeof(char));
        size_t parselength = trimstring(parsedinput, input, BUFLEN);

        
        char* arguments[100] = {NULL};      //NOTE: The path must be the first argument of the arg array
                                            // All strings are dynamically allocated and must be freed later 
        
        int number_of_arguments = get_args(parsedinput,arguments);

        
        char* path = get_path(parsedinput);

        //Sample shell logic implementation
        if ( strcmp(parsedinput, "quit") == 0 ) {
            printf("Bye!!\n");
            return 0;
        }
        else {
            pid_t forkV = fork();
            if ( forkV == 0 ) {
                args[0] = path;
                args[1] = NULL;
                args[2] = NULL;
                
                if(execve(path, arguments, NULL) == -1)
                {
                    fprintf(stderr, "Error running command in execve\n");
                    return -100;
                }
            } else
                wait(NULL);
        }

        //Remember to free any memory you allocate!
        
        if(parsedinput != NULL)
            free(parsedinput);
        
        for(int i = 0; i < number_of_arguments;i++){
            free(arguments[i]);
        }
    
    } while ( 1 );

    return 0;
}
