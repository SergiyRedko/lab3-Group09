#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include "parser.h"
#include "qualifyPath.h"

#define BUFLEN 1024

void testPath(char*);

int main() {
    char* path1 = "/usr/bin/ls";
    char* path2 = "/usr1/bin/ls";
    char* path3 = "/usr/bin1/ls";
    char* path4 = "ls";
    char* path5 = "/usr/bin/lsisus";
    char* path6 = "/usr/bin/ls.out";
    char* path7 = "/usr/bin/ls.exe";

    testPath(path1);
    testPath(path2);
    testPath(path3);
    testPath(path4);
    testPath(path5);
    testPath(path6);
    testPath(path7);


    return 0;
}

void testPath(char* path){
    if(qualifyPath(&path)){
        printf("Path success: %s\n", path);
    }
    else{
        printf("Path failure: %s\n", path);
    }
}
