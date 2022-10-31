#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum condition
{
    NOTHING,
    WAS_SLASH,
    WAS_TWO_SLASH
} flag;

char* deleteSlach(char * src)
{
    char * ptr = src;
    char *resultStr;
    int cur = 0;
    char currentC;
    flag = NOTHING;
    while ((currentC = *ptr++) != '\0') 
    {
        if (currentC == '\\')
        {
            if (flag == NOTHING)
            {
                flag = WAS_SLASH;
                cur++;
            }
            else
            {
                flag = NOTHING;
                continue;
            }

        } else if (flag == WAS_SLASH)
        {
            flag = NOTHING;
            cur++;
        } else {
            cur++;
        }
        
    }
    resultStr = (char *)malloc((cur + 1) * sizeof(*resultStr));
    ptr = src;
    cur = 0;
    while ((currentC = *ptr++) != '\0') 
    {
        if (currentC == '\\')
        {
            if (flag == NOTHING)
            {
                flag = WAS_SLASH;
                resultStr[cur] = currentC;
                cur++;
            }
            else
            {
                flag = NOTHING;
            }

        } else if (flag == WAS_SLASH)
        {
            flag = NOTHING;
            resultStr[cur] = currentC;
            cur++;
        } else {
            resultStr[cur] = currentC;
            cur++;
        }
        
    }
    
    return resultStr;
}

int parseSubstitution(char* substr)
{
    char * ptr = substr;
    char currentC;
    int result = 0;
    while ((currentC = *ptr++) != '\0') 
    {
        if (currentC == '\\')
        {
            if (flag == NOTHING || flag == WAS_SLASH)
                flag = WAS_SLASH;

        } else if (isdigit(currentC))
        {
            if (flag == WAS_SLASH)
            {
                result = result >= atoi(&currentC) ? result : atoi(&currentC);
                flag = NOTHING;
            }
        } 
    }

    return result;
}


int strLen (char *str)
{
    int result = 0;
    char * ptr = str;
    while (*ptr++ != '\0') 
    {
        result++;
    }
    return result;
}

char* makeNewString(char* src, regmatch_t* pmatch, char* substr)
{
    char * ptr = substr;
    char currentC;
    
    char* resultStr;
    int size = 0, strSize, realsize = 0;
    strSize = strLen(src);
    if (!pmatch[0].rm_so)
    {
        resultStr = (char*)malloc(sizeof(*resultStr));
        resultStr[0] = '\0';
    } else {
        resultStr = (char*)malloc((pmatch[0].rm_so + 1) * sizeof(*resultStr));
        strncpy(resultStr, src, pmatch[0].rm_so);
    
    }
    size = pmatch[0].rm_so;
    realsize = size + 1;
    flag = NOTHING;
    while ((currentC = *ptr++) != '\0') 
    {
        if (currentC == '\\' && (flag == NOTHING || flag == WAS_SLASH))
        {
            if (flag == NOTHING)
                flag = WAS_SLASH;
            else 
                flag = WAS_TWO_SLASH;
        } else if (isdigit(currentC) && (flag == WAS_SLASH || WAS_TWO_SLASH))
        {
            int cnt = atoi(&currentC);
            resultStr = (char*)realloc(resultStr, (realsize + (pmatch[cnt].rm_eo - pmatch[cnt].rm_so))* sizeof(*resultStr));
            strncpy(resultStr + size, src + pmatch[cnt].rm_so, pmatch[cnt].rm_eo - pmatch[cnt].rm_so);
            size += pmatch[cnt].rm_eo - pmatch[cnt].rm_so;
            realsize = size + 1; 
            flag = NOTHING;
        } else 
        {
            if ((realsize - size) == 1)
            {
                realsize *= 2;
                resultStr = (char*)realloc(resultStr, realsize * sizeof(*resultStr));
            } 
            strcpy(resultStr + size, &currentC);
            size++;            
        }
    }
    
    resultStr = (char*)realloc(resultStr, ((size ? size : 1) + (strSize - pmatch[0].rm_eo))* sizeof(*resultStr));
    strncpy(resultStr + size, src + pmatch[0].rm_eo, strSize - pmatch[0].rm_eo);
    size += strSize - pmatch[0].rm_eo;
    if (resultStr[size] != '\0')
        resultStr[size] = '\0';

    return resultStr;
}


int main (int argc, char* argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }
    regex_t regex;
    int reti, pocketCnt;
    char bufferForError[100];

    if ((reti = regcomp(&regex, argv[1], REG_EXTENDED)) != 0) 
    {
      regerror(reti, &regex, bufferForError, 100);
      fprintf(stderr, "regcomp() failed with '%s'\n", bufferForError);
      exit(1);
    }
    
    pocketCnt = parseSubstitution(argv[2]); 
    char* src = deleteSlach(argv[3]);
    char* substr = argv[2];        
    regmatch_t pmatch[pocketCnt];
    if ((reti = regexec(&regex, argv[3], pocketCnt + 1, pmatch, 0)) == 0) {
        if (pmatch[pocketCnt].rm_so < 0)
        {
            fprintf(stderr, "Wrong pocket count\n");
            return 0;
        }
        char* resultStr = makeNewString(src, pmatch, substr);
        printf("%s\n", resultStr);
        if (resultStr != NULL)
            free(resultStr);
    }
    else
    {
        regerror(reti, &regex, bufferForError, 100);
        if (reti == REG_NOMATCH)
        {
            printf("%s\n", argv[3]);
        } else {
            fprintf(stderr, "regexec() failed with '%s'\n", bufferForError);
            exit(1);
        }
    }
    regfree(&regex);
    return 0;
}