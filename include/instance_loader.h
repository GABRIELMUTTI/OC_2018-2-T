#ifndef __INSTANCE_LOADER_H__
#define __INSTANCE_LOADER_H__

#define ERR_GETLINE -1
#define ERR_NEW_INSTANCE -2;

#include "instance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int loadInstance(Instance* instance, const char* filepath);
int getLine(FILE* file, char** line, const char* delimiters);


#endif // __INSTANCE_LOADER_H__


