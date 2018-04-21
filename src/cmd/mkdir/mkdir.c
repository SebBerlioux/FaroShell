#include "mkdir.h"

// ex:$ mkdir -m 777 folderName

int fmkdir(int argc, char const *argv[]){      //enlever le const pour enlever le warnin

  if(argc<2){
    printf("Erreur manque de paramètre !\n");
  }else{
    mode_t folderMode;
    folderMode = 0777; //default
    char **endptr = NULL;

    char *folderName[20];

    for(int i=0; i<argc; i++){
      if(strcmp(argv[i], (char*)("-m")) == 0){ // -m : permissions
        // printf("%s\n", argv[i+1]);
        folderMode = strtol(argv[i+1],endptr,8);
        // printf("%i\n", folderMode);
        i++; // on saute alors les chiffres après le -m
      }else{ // nom du fichier
      // /!\ on ne gère pas les cas d'erreurs ici
        *folderName = (char*)argv[i];
      }
    }

    // La fonction semble ne pas fonctionner, peut import la valeur
    // de folderMode, le dossier créé a une permission '777'
    mkdir(*folderName, folderMode);
  }

  return 0;
}
