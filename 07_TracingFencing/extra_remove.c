#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef int (*real_remove_t)(const char* file);

int real_remove (const char* file)
{
	return ((real_remove_t)dlsym(RTLD_NEXT,"remove"))(file);
}


int remove(const char* file) {
    if (strstr(file, "PROTECT") != NULL) 
    {
        errno = 1024;
        return -1;
    } else
    	return real_remove(file);
 }