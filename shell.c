#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include "qualifyPath.h"

#define BUFLEN 1024

//To Do: This base file has been provided to help you start the lab, you'll need to heavily modify it to implement all of the features

int main() {
    char buffer[BUFLEN];
    char* parsedinput;
    char* args[3];
    char newline;

    printf("--- Welcome to the Group09 shell! Enter commands, enter 'quit' to exit.\n--- Enter 'help' to get no help whatsoever.\n");
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

        //Sample shell logic implementation
        if ( strcmp(parsedinput, "quit") == 0
             || strcmp(parsedinput, "exit") == 0
             || strcmp(parsedinput, "terminate") == 0 ) {
            printf("I wish you best fortune in all your many endevours.\n");
            return 0;
        }
        else if(strcmp(parsedinput, "help") == 0){
            printf("As I said. You are on your own here.\n");
        }
        else {
            // Check if path leads to executable with run access.
            if(qualifyPath(&(arguments[0])) == 1){
                pid_t forkV = fork();
                if ( forkV == 0 ) {
                    
                    if(execve(arguments[0], arguments, NULL) == -1)
                    {
                        fprintf(stderr, "Error running command in execve\n");
                        return -100;
                    }
                } else
                    wait(NULL);
            }
            else{
                printf("This instruction could not be found or executed.\n");
            }
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
