#ifndef _DU_H
	#define _DU_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>

int fdu(int argc, char *argv[]);
void conversionHumanReadable(off_t size, char *name, int indice);

#endif
