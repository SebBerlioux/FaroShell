#include "pwd.h"

int fpwd(int argc, char *argv[])
{
  char *fonction = argv[0];
  if(argc>1){
    printf("%s: Too many arguments !\n", fonction);
    return 1;
  }else{

    char tampon[100];

    if (getcwd(tampon, 100) == NULL) {
      printf("Erreur (Fonction %s) lors de la recuperation du chemin !", fonction);
    }else{
      printf("%s\n", tampon);
    }
  }
  return 0;
}
