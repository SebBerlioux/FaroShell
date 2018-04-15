#ifndef FAROSHELL_LS_H
    #define FAROSHELL_LS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <time.h>
#include <grp.h>    //getgrgid
#include <pwd.h>    //Sert pour *getpwuid pour avoir l'ID
#include <stdbool.h>

//define.......

#define PURPLE   "\033[1;35m"
#define CYAN     "\033[1;36m"
#define RED      "\033[38;5;124m"
#define BLUE      "\033[38;5;124m"   //FALSE
#define YELLOW     "\033[38;5;124m"   //FALSE

int fls(int argc, char const *argv[]);

void printColorFile(mode_t mode, char * path);
void permission(mode_t mode, char* perms);
char type(mode_t mode);
bool isLink(mode_t mode);
int fls_file(char *dir, char *filename, int options);

ssize_t readlink(const char *path, char *buf, size_t bufsiz);   //pour readlink
struct passwd *getpwnam(const char *);
struct passwd *getpwuid(uid_t);

#endif
