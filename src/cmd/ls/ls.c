#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "ls.h"


int main(int argc, char *argv[]){

    printf("C'est un test d'affichage pour fls\n");
    //fls(argc, argv)        //pour lancer la fonction ls

    return 0;
}



/**
 * kls
 *
 * ls avec option -l et -a ou non (dépand de aFlag)
 *
 * @param  {int}       argc   Le nombre d'arguments
 * @param  {char[] *}  argv   Les arguments d'entrée
 * @param  {int}       aFlag  Option -a
*/
int kls(int argc, char *argv[]) {
    char c;

    optind = 1;
    int options = 0;

    while((c = getopt(argc, argv, "al")) != -1) {
        switch(c) {
            case 'a':
                options |= LS_FLAG_a;
                break;
            case 'l':
                options |= LS_FLAG_l;
                break;
            case '?':
                printf("kls: invalid option -- '%c'\n",c);
                break;
        }
    }

    if (optind == argc) {
        return kls_full(".", options);
    }

    for (int i = optind; i < argc; i++) {
        //On affiche le répertoire analysé si il y en a plusieurs
        if (optind != argc -1) {
            printf("%s:\n", argv[i]);
        }

        DEBUG("ls %s", argv[i]);
        kls_full(argv[i], options);
    }

    return 0;
}