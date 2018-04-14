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
#include <pwd.h>    //pourquoi ca trouve pas ???? sert pour *getpwuid pour avoir l'ID
#include <stdbool.h>

#define	S_IRUSR	0000400			/* R for owner */
#define	S_IWUSR	0000200			/* W for owner */
#define	S_IXUSR	0000100			/* X for owner */
#define	S_IRGRP	0000040			/* R for group */
#define	S_IWGRP	0000020			/* W for group */
#define	S_IXGRP	0000010			/* X for group */
#define	S_IROTH	0000004			/* R for other */
#define	S_IWOTH	0000002			/* W for other */
#define	S_IXOTH	0000001			/* X for other */
#define	S_IFIFO	 0010000		/* named pipe (fifo) */
#define	S_IFCHR	 0020000		/* character special */
#define	S_IFDIR	 0040000		/* directory */
#define	S_IFBLK	 0060000		/* block special */
#define	S_IFLNK	 0120000		/* symbolic link */
#define	S_ISSOCK(m)	((m & 0170000) == 0140000)	/* socket */
#define	S_IFSOCK 0140000		/* socket */
#define	S_ISDIR(m)	((m & 0170000) == 0040000)	/* directory */
#define	S_ISCHR(m)	((m & 0170000) == 0020000)	/* char special */
#define	S_ISBLK(m)	((m & 0170000) == 0060000)	/* block special */
#define	S_ISFIFO(m)	((m & 0170000) == 0010000)	/* fifo */
#define	S_ISLNK(m)	((m & 0170000) == 0120000)	/* symbolic link */

#define PATH_MAX 100

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
