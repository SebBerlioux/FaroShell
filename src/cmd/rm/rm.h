#ifndef _RM_H
	#define _RM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct stat sts;

extern int isAFolder(char* __testedFolder);

int frm(int argc, char *argv[]);

#endif
