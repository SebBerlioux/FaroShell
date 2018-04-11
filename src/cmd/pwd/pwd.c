#include "pwd.h"

void pwd(){
    char tampon[100];

    if (getcwd(tampon, 100) == NULL) {
        exit(EXIT_FAILURE);
    }
    printf("%s\n", tampon);
    exit(EXIT_SUCCESS);
}
