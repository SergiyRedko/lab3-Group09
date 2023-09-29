#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringCleaner.h"

void cleanSpaces(char* string) {
    int i, j = 0;
    int stringLength = strlen(string);
    int spaceFlag = 0; // Flag to track if previous character was a space.

    // Remove leading spaces by finding the position of the first non-space character.
    for (i = 0; i < stringLength; i++) {
        if (!isspace((unsigned char)string[i])) {
            break;
        }
    }

    // Shift the non-space portion to the beginning of the string.
    for (; i < stringLength; i++) {
        if (isspace((unsigned char)string[i])) {
            // Skip multiple consecutive spaces.
            if (!spaceFlag) {
                string[j++] = ' '; // Replace multiple spaces with a single space.
                spaceFlag = 1; // Set the space flag.
            }
        } else {
            string[j++] = string[i];
            spaceFlag = 0; // Reset the space flag.
        }
    }

    // Remove trailing spaces.
    while (j > 0 && isspace((unsigned char)string[j - 1])) {
        j--;
    }

    // Null-terminate the new string.
    string[j] = '\0';
}

int cleanCommand(char* commandString){
    int isBackgroundTask = 0;

    cleanSpaces(commandString);

    int commandLength = strlen(commandString);
    if(commandLength > 1 && commandString[commandLength - 1] == '&'){
        isBackgroundTask = 1;
        commandString[commandLength - 1] = '\0';
        cleanSpaces(commandString);
    }

    return isBackgroundTask;
}