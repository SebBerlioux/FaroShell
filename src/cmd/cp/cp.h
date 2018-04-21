#ifndef FAROSHELL_CP_H
    #define FAROSHELL_CP_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>



int fcp(int argc,char *argv[]);
int cp_avanced(const char *nameSource,const char *nameDestination);


struct stat sts;

extern int isFolder(char* __testedFolder);

int isRegularFile(char* testedFile);

#endif
