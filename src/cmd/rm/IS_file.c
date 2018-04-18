#include "IS_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

struct stat sts;    // Declaration d'une struct stat

// isFolder prend en argument un char *testedFolder et retourne 1 si l'argument est un repertoire ou 0

int isFolder(char* testedFolder){
    if(testedFolder!=NULL && stat(testedFolder,&sts)==0 && S_ISDIR(sts.st_mode)) return 1;
    else return 0;
}

// isRegularFile prend en argument char *testedFile et retourrne 1 si l'argument est un fichier ou 0

int isRegularFile(char* testedFile){
    if(testedFile!=NULL && stat(testedFile,&sts)==0 && S_ISREG(sts.st_mode)) return 1;
    else return 0;
}