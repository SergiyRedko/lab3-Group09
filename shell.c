#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include "qualifyPath.h"
#include "stringCleaner.h"
#include "piping.h"

#define BUFFER_LENGTH 1024

// To Do: This base file has been provided to help you start the lab, you'll need to heavily modify it to implement all of the features

int main()
{
    char buffer[BUFFER_LENGTH];
    char *parsedinput;
    char *args[3];
    char newline;

    // Print out applicaton's greeting.
    printf("--- Welcome to the Group09's shell! Enter commands now. Enter 'quit' to exit.\n--- Enter 'help' to get no help whatsoever.\n");

    // Start the main loop.
    do
    {

        // Check if any tasks have completed while application was completing the last one.
        int status;
        int terminatedNum;
        do
        {
            terminatedNum = waitpid(-1, &status, WNOHANG);
            if (terminatedNum != 0 && terminatedNum != -1)
                printf("Background command %d terminated. Status: %d.\n", terminatedNum, status);
            else
                break;
        } while (1);

        // Print the terminal prompt.
        char *currentWorkingDirectory = (char *)malloc(BUFFER_LENGTH);
        if (getcwd(currentWorkingDirectory, BUFFER_LENGTH) == NULL)
        {
            perror("getcwd");
        }
        printf("%s$ ", currentWorkingDirectory);
        free(currentWorkingDirectory);

        // Get user's input.
        char *input = fgets(buffer, sizeof(buffer), stdin);
        if (!input)
        {
            fprintf(stderr, "Error reading input\n");
            return -1;
        }

        // Clean the command string from leading, trailing, or double spaces and check if it's a background task.
        int taskIsBackground = cleanCommand(buffer);

        // Skip the rest if user's command is empty.
        if (strlen(buffer) == 0)
        {
            printf("Cannot execute an empty command.\n");
            continue;
        }

        // Clean and parse the input string
        parsedinput = (char *)malloc(BUFFER_LENGTH * sizeof(char));
        size_t parselength = trimstring(parsedinput, buffer, BUFFER_LENGTH);

        char *arguments[100] = {NULL}; // NOTE: The path must be the first argument of the arg array
                                       //  All strings are dynamically allocated and must be freed later

        int number_of_arguments = get_args(parsedinput, arguments);

        if (pipe_check(arguments, number_of_arguments))
        { // Enter if we need to pipe commands

            create_pipe(arguments, number_of_arguments);
        }
        else
        {
            // Sample shell logic implementation
            if (strcmp(parsedinput, "quit") == 0 || strcmp(parsedinput, "exit") == 0 || strcmp(parsedinput, "terminate") == 0)
            {
                printf("--- We wish you best fortune in all your many endevours.\n");
                return 0;
            }
            else if (strcmp(parsedinput, "help") == 0)
            {
                printf("As we said. You are on your own here.\n");
            }
            else
            {
                // Check if path leads to executable with run access.
                // If not, notify user and skip to next.
                if (qualifyPath(&(arguments[0])) == 1)
                {
                    pid_t forkV = fork();
                    if (forkV == 0)
                    {

                        if (execve(arguments[0], arguments, NULL) == -1)
                        {
                            fprintf(stderr, "Error running command in execve\n");
                            return -100;
                        }
                    }
                    else
                    {
                        // If this is not a background task, wait for this task, and no other to complete.
                        if (taskIsBackground == 0)
                        {
                            int status;
                            waitpid(forkV, &status, 0);
                        }
                    }
                }
                else
                {
                    printf("This instruction could not be found or executed.\n");
                }
            }
        }
        // Free the used memory.

        if (parsedinput != NULL)
            free(parsedinput);

        for (int i = 0; i < number_of_arguments; i++)
        {
            // free(arguments[i]);
        }

    } while (1);

    return 0;
}
