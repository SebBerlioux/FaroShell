#include <stdio.h>
#include "cp.h"

//Copie d'un dossier dans un autre dossier
int cp_avanced(const char *Source_ID,const char *Destination_ID){

    DIR *source;           	            // le dossier (et son contenu) à deplacer
    DIR *destination;           	    // sa destination
    struct dirent *sourceEntry;     	// information du dossier source
    struct stat file_stat;    	        // nformation du fichier source
    char buffer[246] = {0};	        // chemin du fichier contenu dans le dossier source

    //Cas avec erreur
    if ((source=opendir(Source_ID))==NULL){
        printf("Impossible d'ouvrir le repertoire %s\n",Source_ID);
        return -1;
    }

    if ((destination=opendir(Destination_ID))==NULL){
        printf("Le repertoire existe pas %s\n",Destination_ID);
        return -1;
    }

    // FDéplacement du fichier contenu dans le repertoire
    while ((sourceEntry=readdir(source))!=NULL) {

        // On ignore si c'est "." ou ".."
        if (strcmp(sourceEntry->d_name,".")==0 || strcmp(sourceEntry->d_name,"..")==0) {
            continue;
        }

        // Création du chemin
        snprintf(buffer, 246, "%s/%s", Source_ID, sourceEntry->d_name);
        char path_Src[246], path_Dest[246];
        strcpy(path_Src,buffer);
        strcpy(path_Dest,Destination_ID);

        if(path_Src[strlen(path_Src)-1]!='/') strcat(path_Dest, "/");
        strcat(path_Dest, sourceEntry->d_name);

        // On prends les informations du fichier
        stat(path_Src, &file_stat);

        // Si c'est une cible sans répertoire c'est bon
        if (S_ISREG(file_stat.st_mode)){

            FILE *f_Src;
            FILE *f_Dest;
            char tmp[1024];
            int i=0;

            if((f_Src = fopen(path_Src, "r")) == NULL){
                // Si le fichier s'ouvre pas
                printf("Le fichier source %s semble introuvable dans le dossier\n", path_Src);
                return 1;
            }

            if((f_Dest = fopen(path_Dest, "w")) == NULL){
                // Si le dossier de destination n'existe pas
                printf("Le fichier de destination : %s semble introuvable dans le dossier\n", path_Dest);
                fclose(f_Src);
                return 2;
            }

            while((i = fread(tmp, 1, 4096, f_Src)) != 0){
                fwrite(tmp, 1, i, f_Dest);
            }

            fclose(f_Dest); //On ferme tout
            fclose(f_Src);
        }

            //Si c'est encore un dossier on relancela fonction qui est RECURSIVE
        else if ( S_ISDIR(file_stat.st_mode) ){
            cp_avanced(path_Src,path_Dest); //On relance la fonction
        }
    }

    return 0;
}

// Fonction qui sert  à  copier  des  fichiers  et eventuellement des répertoires.
int fcp(int argc, char *argv[]){

    if(argc<2){
        printf("cp : too few argument\n");
        return -1;
    }
    if(argc==2){
        printf("cp : missing destination file after '%s'\n",argv[1]);
        return -1;
    }
    else if(argc>3){
        printf("cp : too many arguments\n");
        return -1;
    }

    else{
        if(isRegularFile(argv[1])){     //Test du fichier

            FILE *f_Src;
            FILE *f_Dest;
            char *path_Dest = argv[2], *path_Src = argv[1];
            char tmp[4096];
            int i;
            char* ret;

            // Chemin pour la création0d' un nouveau fichier dans le dossier cible
            if(argv[1][0] != '.')
            {
                strcat(path_Dest, "/");
                strcat(path_Dest, argv[1]);
                //printf("Destination du fichier : %s\n", path_Dest);
            }

            else    //cas ou l'on reste dans le meme dossier
            {
                ret = strchr(argv[1], '/');
                ret = strchr(ret, ret[1]);
                strcat(path_Dest, ret);
            }

            if((f_Src = fopen(path_Src, "r")) == NULL)
            {
                // Si on a pas la permission pour deplacer le fichier
                printf("Le fichier source semble introuvable\n");
                return 1;
            }

            if((f_Dest = fopen(path_Dest, "w+")) == NULL)
            {
                // Si le dossier de destination n'existe pas
                printf("Le dossier de destination est introuvable\n");
                fclose(f_Src);
                return 2;
            }

            while((i = fread(tmp, 1, 4096, f_Src)) != 0)
            {
                fwrite(tmp, 1, i, f_Dest);
            }

            fclose(f_Dest); //fermeture de tout
            fclose(f_Src);
        }

        else if(isFolder(argv[1])){
            cp_avanced(argv[1],argv[2]);    //le cas d'un dossier qu'on copie d'un autre autre dossier
        }

        else{
            printf("cp : file/directory '%s' doesn't exist\n", argv[1]);
            return -1;
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

// isRegularFile prend en argument char *testedFile et retourrne 1 si l'argument est un fichier ou 0
int isRegularFile(char* testedFile){
    if(testedFile!=NULL && stat(testedFile,&sts)==0 && S_ISREG(sts.st_mode)) {
        return 1;
    }
    else {
        return 0;
    }
}