#include "pwd.h"
#include "../../utils/faroprint.h"

int fpwd(int argc, char *argv[])
{
  char *fonction = argv[0];
  if(argc>1){
    faroprint("%s: Too many arguments !\n", fonction);
    return 1;
  }else{

    char tampon[200];

    if (getcwd(tampon, 100) == NULL) {
      faroprint("Erreur (Fonction %s) lors de la recuperation du chemin !", fonction);
    }else{
      faroprint("%s\n", tampon);
    }
  }
  return 0;
}
