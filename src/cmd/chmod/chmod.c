#include <stdio.h>
#include "chmod.h"
#include "../../utils/faroprint.h"

//  Change le mode d'un fichier ou d'un dossier

int mod(int argc, char *argv[])
{
    faroprint("%d\n", argc);
    faroprint("%s\n%s\n%s\n", argv[0], argv[1], argv[2]);

    if(argc < 3)
    {
        faroprint("chmod : Pas assez arguments!!!\n");
        return -1;
    }

    else if(argc > 3)
    {
        faroprint("chmod : Trop d'arguments\n");
        return -1;
    }

    mode_t mode = 0;

    const char* mod = argv[1];

    switch(mod[0]){    //change les droits de l'utilisateur sur le fichier

        case '1':
            mode |= S_IXUSR;
            break;
        case '2':
            mode |= S_IWUSR;
            break;
        case '3':
            mode |= S_IWUSR | S_IXUSR;
            break;
        case '4':
            mode |= S_IRUSR;
            break;
        case '5':
            mode |= S_IRUSR | S_IXUSR;
            break;
        case '6':
            mode |= S_IRUSR | S_IWUSR;
            break;
        case '7':
            mode |= S_IRUSR | S_IWUSR | S_IXUSR;
            break;
    }

    switch(mod[1]){  //change les droits du groupe sur le fichier

        case '1':
            mode |= S_IXGRP;
            break;
        case '2':
            mode |= S_IWGRP;
            break;
        case '3':
            mode |= S_IWGRP | S_IXGRP;
            break;
        case '4':
            mode |= S_IRGRP;
            break;
        case '5':
            mode |= S_IRGRP | S_IXGRP;
            break;
        case '6':
            mode |= S_IRGRP | S_IWGRP;
            break;
        case '7':
            mode |= S_IRGRP | S_IWGRP | S_IXGRP;
            break;
    }

    switch(mod[2]){   //changer les droits pour le reste des utilisateurs.

        case '1':
            mode |= S_IXOTH;
            break;
        case '2':
            mode |= S_IWOTH;
            break;
        case '3':
            mode |= S_IWOTH | S_IXOTH;
            break;
        case '4':
            mode |= S_IROTH;
            break;
        case '5':
            mode |= S_IROTH | S_IXOTH;
            break;
        case '6':
            mode |= S_IROTH | S_IWOTH;
            break;
        case '7':
            mode |= S_IROTH | S_IWOTH | S_IXOTH;
            break;
    }

    chmod(argv[2], mode);

    return 0;
}
