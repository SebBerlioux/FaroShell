#ifndef FAROSHELL_LS_H
    #define FAROSHELL_LS_H

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




int fls(int argc,char *argv[]);
void affichage_avance(struct dirent *dptr,int dflag);


struct stat sts;

extern int isFolder(char* __testedFolder);

#endif
