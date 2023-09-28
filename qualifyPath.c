#include "qualifyPath.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "string.h"

int qualifyPath(char** pathRef){
    if(pathRef == 0)
        return 0;

    char* path = *pathRef;
    if(path == 0)
        return 0;

    if(path[0]== '/'){ // If the name starts with / treat is a a fully qualified name already.

        // Check that it exists, no neet to update the pathRef.
        if(access(path, X_OK) == 0)
            return 1;
        else
            return 0;
    }
    else if(containsSlash(path)){
        // Run from working dir + path.
        size_t size = 300;

        char* qualifiedPath = (char*)malloc(size);
        if (getcwd(qualifiedPath, size) == NULL) {
            perror("getcwd");
        }

        strcat(qualifiedPath, "/");
        strcat(qualifiedPath, path);

        // Check that it exists, if yes, update the pathRef and return.
        if(access(qualifiedPath, X_OK) == 0){
            free(*pathRef);
            *pathRef = qualifiedPath;
            return 1;
        }
        else
            return 0;

        // SRD: Implement "../"

    }
    else{
        // Since we got here, we need to look through the PATHs.

        char* pathEnv = getenv("PATH");

        // Copy pathEnv to heap so we don't mess it up with strtok()
        char* heapedPathEnv = (char*)malloc(strlen(pathEnv));
        strcpy(heapedPathEnv, pathEnv);

        char* delim = ":";
        char* token;
        char* PATHs[100];

        int numPATHs = 0;
        token = strtok(heapedPathEnv, delim);
        while(token != NULL){
            PATHs[numPATHs++] = token;
            token = strtok(NULL, delim);
        }

        for(int i = 0; i < numPATHs; i++){
            int fullPathLength = strlen(PATHs[i]) + strlen(path) + 2; // Adjust for delimenter.
            char* fullPath = (char*)malloc(fullPathLength);
            strcpy(fullPath, PATHs[i]);
            strcat(fullPath, "/");
            strcat(fullPath, path);

            if(access(fullPath, X_OK) == 0){
                free(*pathRef);
                *pathRef = fullPath; // Update fully qualified path.

                free(heapedPathEnv);

                return 1;
            }           
        }

        free(heapedPathEnv);

        return 0;
    }
}

int containsSlash(const char* string){
    while (*string != '\0') {
        if (*string == '/') {
            return 1; // Character found, return true
        }
        string++; // Move to the next character in the string
    }
    return 0; // Character not found, return false
}