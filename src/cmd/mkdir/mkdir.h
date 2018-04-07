#ifndef _MKDIR_H
	#define _MKDIR_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void fmkdir(int argc, char const *argv[]);

#endif
