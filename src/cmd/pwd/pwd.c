#include "pwd.h"

void fpwd(){
    char tampon[100];

    if (getcwd(tampon, 100) == NULL) {
        printf("Erreur lors de la recuperation du chemin !");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", tampon);
}
