#include <stdio.h>
#include "chgrp.h"

//  Change le groupe d'utilisateur possédant un fichier ou un dossier.

int grp(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("chgrp : too few arguments\n");

    }

    else if(argc > 3)
    {
        printf("chgrp : too many arguments\n");
    }

    else
    {
        printf("%s\nGroupe : %s\nFichier : %s\n", argv[0], argv[1], argv[2]);   //Affiche les arguments
        FILE *pass;         // Fichier qui va lire le fichiergroupe dans /etc pour acceder au differents groupe present sur le systeme
        char ligne[100];    // Variable qui va stocker les lignes (donc les noms des groupes) dans le fichier group
        char *ret;          // Tampon pour le char*
        int i;
        gid_t group;        // Nouveau ID de groupe

        if(isRegularFile(argv[2]))      //Vérifie la valeur du fichier
        {
            if((pass = fopen("/etc/group", "r")) != NULL)
            {
                /* On recherche le groupe (dans etc/group) pour avoir son ID */
                while((fgets(ligne,100,pass)) != NULL)
                {
                    ret = strtok(ligne, ":");
                    for(i=0;i<2;i++)
                    {
                        //Si le nom du groupe est égale à l'argument du groupe on va dans le troisième champ de la ligne pour obtenir son ID
                        if(strcmp(ret, argv[1]) == 0)
                        {
                            ret = strtok(NULL, ":");
                            ret = strtok(NULL, ":");
                            group = atoi(ret);
                            break;
                        }
                    }
                }
                chown(argv[2], (uid_t)-1, group);
            }

            else
            {
                printf("error opening /etc/group\n");
                return -1;
            }
            fclose(pass);
        }
    }

    return 0;
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