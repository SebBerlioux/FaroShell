#ifndef _ISFILE_H
#define _ISFILE_H 1

#include <sys/stat.h>
struct stat sts;

extern int isFolder(char* __testedFolder);

extern int isRegularFile(char* __testedFile);

#endif