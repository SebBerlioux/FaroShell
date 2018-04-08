#ifndef _CAT_H
	#define _CAT_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void fcat(int argc, char const *argv[]);
void readFile(FILE *fp, char *option[], int nbOption);

#endif
