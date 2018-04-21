#include <stdio.h>
#include "cp.h"



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


        else{
            printf("cp : file/directory '%s' doesn't exist\n", argv[1]);
            return -1;
        }
    }
    return 0;   //Tout est pl
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