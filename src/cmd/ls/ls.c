#include <stdio.h>
#include "ls.h"


//affiche les informations du fichier / répertoire actuel sur une ligne

void affichage_avance(struct dirent *dptr,int dflag){

    struct stat st;				// Information générale contenu dans le fichier ou le reprtoire
    struct passwd *userInfo;	// Information de l'utilisateur contenu dans le fichier ou le reprtoire
    struct group *groupInfo;	// Information de groupe contenu dans le fichier ou le reprtoire
    struct tm *timeInfo;		// les informations au niveau du temps

    lstat(dptr->d_name,&st);    // On récupere le contenu du fichier ou du répertoire

    // On l'affiche
    if ((st.st_mode & S_IFSOCK)==S_IFSOCK) faroprint("s");
    else if ((st.st_mode & S_IFLNK)==S_IFLNK) faroprint("l");
    else if ((st.st_mode & S_IFREG)==S_IFREG) faroprint("-");
    else if ((st.st_mode & S_IFBLK)==S_IFBLK) faroprint("b");
    else if ((st.st_mode & S_IFDIR)==S_IFDIR) faroprint("d");
    else if ((st.st_mode & S_IFCHR)==S_IFCHR) faroprint("c");
    else if ((st.st_mode & S_IFIFO)==S_IFIFO) faroprint("p");

    // Les droits d'utilisateurs
    faroprint("%c",(st.st_mode & S_IRUSR)==S_IRUSR ? 'r' : '-');	// utilisateur R
    faroprint("%c",(st.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-');	// utilisateur W
    faroprint("%c",(st.st_mode & S_IXUSR)==S_IXUSR ? 'x' : '-');	// utilisateur X
    faroprint("%c",(st.st_mode & S_IRGRP)==S_IRGRP ? 'r' : '-');	// groupe R
    faroprint("%c",(st.st_mode & S_IWGRP)==S_IWGRP ? 'w' : '-');	// group W
    faroprint("%c",(st.st_mode & S_IXGRP)==S_IXGRP ? 'x' : '-');	// group X
    faroprint("%c",(st.st_mode & S_IROTH)==S_IROTH ? 'r' : '-');	// other R
    faroprint("%c",(st.st_mode & S_IWOTH)==S_IWOTH ? 'w' : '-');	// other W
    faroprint("%c",(st.st_mode & S_IXOTH)==S_IXOTH ? 'x' : '-');	// other X

    faroprint(" %zu",st.st_nlink);     // Le lien

    userInfo=getpwuid(st.st_uid);     // Le proprietaire
    faroprint(" %s",userInfo->pw_name);

    groupInfo=getgrgid(st.st_gid);     // LE groupe
    faroprint(" %s",groupInfo->gr_name);

    faroprint(" %zu",st.st_size);     // La taille

    timeInfo=localtime(&st.st_mtime);     // Information du temps
    faroprint(" %4d-%02d-%02d %02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min);

    if(dflag==0 && isFolder(dptr->d_name)){ // Si l'option n'est pas d et si c'est un repertoire l'onformation sera verte (MARCHE PAS)
        faroprint("\033[32m");
        faroprint(" %s \n",dptr->d_name);
        faroprint("\033[0m");
    }
    else faroprint(" %s \n",dptr->d_name);
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
                faroprint("ls : option %s doesn't exist for command ls\n",argv[optind-1]);
                return -1;
        }
    }

    int index = optind;

    // Si pas d'argument on prend le repertoire courant
    if(argv[index]==NULL){

        if ((dirp=opendir("."))==NULL){
            faroprint("ls : directory %s doesn't exist\n",".");
            return -1;
        }
        while((dptr=readdir(dirp))){
            // Si -a n'est pas neccesaire on ignore le "." et le ".."
            if(aflag==0) if(dptr->d_name[0]=='.') continue;

            // Si il y a l'option -l alors on affiche les informations avancées
            if(lflag==1){
                affichage_avance(dptr,dflag);
            }

            else{
                // Si il n'y a pas l'option -d et si c'est un reperoire l'information sera verte
                if(dflag==0 && isFolder(dptr->d_name)){
                    faroprint("\033[32m");
                    faroprint("%s ",dptr->d_name);
                    faroprint("\033[0m");
                }
                else faroprint("%s ",dptr->d_name);
            }
        }
        faroprint("\n");
        closedir(dirp);
        //faroprint("toto");
    }
        // On affiche les informations pour chaque arguments
    else{
        for (index = optind; index < argc; index++){

            // Cas du dossier
            if(isFolder(argv[index])){

                if ((dirp=opendir(argv[index]))==NULL){
                    faroprint("ls : directory %s doesn't exist\n",argv[index]);
                }

                else{
                    while((dptr=readdir(dirp))){
                        // On ignore le "." et ".." des repertoires
                        if(aflag==0) if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")) continue;
                        // Option -l
                        if(lflag==1){
                            affichage_avance(dptr,dflag);
                        }
                        else{
                            // Si il n'y a pas l'option -d et si c'est un reperoire l'information sera verte
                            if(dflag==0 && isFolder(dptr->d_name)){
                                faroprint("\033[32m");
                                faroprint("%s ",dptr->d_name);
                                faroprint("\033[0m");
                            }
                            else faroprint("%s ",dptr->d_name);
                        }
                    }
                    faroprint("\n");
                    closedir(dirp);
                }
            }
                // Sinon ERREUR
            else{
                faroprint("ls : directory %s doesn't exist\n",argv[index]);
            }
        }
    }

    return 0;
}



struct stat sts;    // Declaration d'une struct stat

// isFolder prend en argument un char *testedFolder et retourne 1 si l'argument est un repertoire ou 0

int isFolder(char* testedFolder){
    if(testedFolder!=NULL && stat(testedFolder,&sts)==0 && S_ISDIR(sts.st_mode)) {
        return 1;
    }
    else {
        return 0;
    }
}
