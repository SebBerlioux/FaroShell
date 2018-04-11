#include <stdio.h>
#include "ls.c"

int main(int argc, char *argv[]){

    printf("Fonction ls ->!\n");
    fls(argc, argv);        //pour lancer la fonction ls

    return 0;
}