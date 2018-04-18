#include <stdio.h>
#include "ls.h"


//affiche les informations du fichier / répertoire actuel sur une ligne

void advancedDisplay(struct dirent *dptr,int dflag){

    struct stat st;				// Information générale contenu dans le fichier ou le reprtoire
    struct passwd *userInfo;	// Information de l'utilisateur contenu dans le fichier ou le reprtoire
    struct group *groupInfo;	// Information de groupe contenu dans le fichier ou le reprtoire
    struct tm *timeInfo;		// les informations au niveau du temps

    lstat(dptr->d_name,&st);    // On récupere le contenu du fichier ou du répertoire

    // On l'affiche
    if ((st.st_mode & S_IFSOCK)==S_IFSOCK) printf("s");
    else if ((st.st_mode & S_IFLNK)==S_IFLNK) printf("l");
    else if ((st.st_mode & S_IFREG)==S_IFREG) printf("-");
    else if ((st.st_mode & S_IFBLK)==S_IFBLK) printf("b");
    else if ((st.st_mode & S_IFDIR)==S_IFDIR) printf("d");
    else if ((st.st_mode & S_IFCHR)==S_IFCHR) printf("c");
    else if ((st.st_mode & S_IFIFO)==S_IFIFO) printf("p");

    // Les droits d'utilisateurs
    printf("%c",(st.st_mode & S_IRUSR)==S_IRUSR ? 'r' : '-');	// utilisateur R
    printf("%c",(st.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-');	// utilisateur W
    printf("%c",(st.st_mode & S_IXUSR)==S_IXUSR ? 'x' : '-');	// utilisateur X
    printf("%c",(st.st_mode & S_IRGRP)==S_IRGRP ? 'r' : '-');	// groupe R
    printf("%c",(st.st_mode & S_IWGRP)==S_IWGRP ? 'w' : '-');	// group W
    printf("%c",(st.st_mode & S_IXGRP)==S_IXGRP ? 'x' : '-');	// group X
    printf("%c",(st.st_mode & S_IROTH)==S_IROTH ? 'r' : '-');	// other R
    printf("%c",(st.st_mode & S_IWOTH)==S_IWOTH ? 'w' : '-');	// other W
    printf("%c",(st.st_mode & S_IXOTH)==S_IXOTH ? 'x' : '-');	// other X

    printf(" %d",st.st_nlink);     // Le lien

    userInfo=getpwuid(st.st_uid);     // Le proprietaire
    printf(" %s",userInfo->pw_name);

    groupInfo=getgrgid(st.st_gid);     // LE groupe
    printf(" %s",groupInfo->gr_name);

    printf(" %5d",st.st_size);     // La taille

    timeInfo=localtime(&st.st_mtime);     // Information du temps
    printf(" %4d-%02d-%02d %02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min);

    if(dflag==0 && isFolder(dptr->d_name)){ // Si l'option n'est pas d et si c'est un repertoire l'onformation sera verte (MARCHE PAS)
        printf("\033[32m");
        printf(" %s \n",dptr->d_name);
        printf("\033[0m");
    }
    else printf(" %s \n",dptr->d_name);
}


//Affiche le contenu du repertoire actuel
int fls(int argc,char *argv[]){

    DIR *dirp;						// repertoire cible
    struct dirent *dptr;			// informations sur le repertoire
    int aflag=0, dflag=0, lflag=0;	// option utilisé

    // On regarde les options requise -a / -d / -l
    char c;

    while ( (c = getopt(argc, argv, "adl")) != -1 ){
        switch(c){
            case 'a':
                aflag = 1;
                break;
            case 'd':
                dflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case '?':
                printf("ls : option %s doesn't exist for command ls\n",argv[optind-1]);
                return -1;
        }
    }

    int index = optind;

    // Si pas d'argument on prend le repertoire courant
    if(argv[index]==NULL){

        if ((dirp=opendir("."))==NULL){
            printf("ls : directory %s doesn't exist\n",".");
            return -1;
        }
        while((dptr=readdir(dirp))){
            // Si -a n'est pas neccesaire on ignore le "." et le ".."
            if(aflag==0) if(dptr->d_name[0]=='.') continue;

            // Si il y a l'option -l alors on affiche les informations avancées
            if(lflag==1){
                advancedDisplay(dptr,dflag);
            }

            else{
                // Si il n'y a pas l'option -d et si c'est un reperoire l'information sera verte
                if(dflag==0 && isFolder(dptr->d_name)){
                    printf("\033[32m");
                    printf("%s ",dptr->d_name);
                    printf("\033[0m");
                }
                else printf("%s ",dptr->d_name);
            }
        }
        printf("\n");
        closedir(dirp);
    }
        // On affiche les informations pour chaque arguments
    else{
        for (index = optind; index < argc; index++){

            // Cas du dossier
            if(isFolder(argv[index])){

                if ((dirp=opendir(argv[index]))==NULL){
                    printf("ls : directory %s doesn't exist\n",argv[index]);
                }

                else{
                    while((dptr=readdir(dirp))){
                        // On ignore le "." et ".." des repertoires
                        if(aflag==0) if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")) continue;
                        // Option -l
                        if(lflag==1){
                            advancedDisplay(dptr,dflag);
                        }
                        else{
                            // Si il n'y a pas l'option -d et si c'est un reperoire l'information sera verte
                            if(dflag==0 && isFolder(dptr->d_name)){
                                printf("\033[32m");
                                printf("%s ",dptr->d_name);
                                printf("\033[0m");
                            }
                            else printf("%s ",dptr->d_name);
                        }
                    }
                    printf("\n");
                    closedir(dirp);
                }
            }
                // Sinon ERREUR
            else{
                printf("ls : directory %s doesn't exist\n",argv[index]);
            }
        }
    }

    return 0;
}


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