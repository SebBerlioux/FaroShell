#ifndef _CHGRP_H
    #define _CHGRP_H


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int grp(int argc, char *argv[]);

struct stat sts;

extern int isRegularFile(char* __testedFile);


#endif
