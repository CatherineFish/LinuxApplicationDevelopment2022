#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024


int main(int argc, char* argv[])
{
    char bufferStr[BUFFERSIZE];
    char *resultStr;
    unsigned bufferStrLen;
    resultStr = (char*) malloc(BUFFERSIZE * sizeof(resultStr));
    fgets(resultStr, BUFFERSIZE, stdin);
    while (fgets(bufferStr, BUFFERSIZE, stdin))
    {
        bufferStrLen = strlen(bufferStr);
        resultStr = realloc(resultStr, strlen(resultStr) + bufferStrLen + 1);
        strcat(resultStr, bufferStr);
    }
    printf("Hello, %s!\n", resultStr);
    if (resultStr)
    {
        free(resultStr);
    }
    return 0; 
}