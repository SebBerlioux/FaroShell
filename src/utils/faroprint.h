#ifndef _FAROPRINT_H
	#define _FAROPRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define NO_SPECIAL 0
#define PIPE 1
#define REDIRECT_RIGHT 2
#define REDIRECT_LEFT 3
#define DOUBLE_REDIRECT_RIGHT 4
#define DOUBLE_REDIRECT_LEFT 5
#define OR 6
#define AND 7

char *filename;

void setSpecial(int value);
void setFileName(char *fname);
int faroprint(const char* format, ...);

#endif
