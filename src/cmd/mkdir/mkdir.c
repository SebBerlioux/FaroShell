#include "mkdir.h"

// ex:$ mkdir -m 777 folderName

void fmkdir(int argc, char const *argv[]){

  char *folderMode;
  folderMode = "777"; //default

  char *folderName[20];

  for(int i=0; i<argc; i++){
    if(argv[i] == (char*)("-m")){ // -m gère les permissions du répertoire créé
      folderMode = (char*)argv[i+1]; //les elements sont separés par un espace donc les valeurs de -m sont en i+1
      i++; //on saute alors les chiffres après le -m
    }else{ // nom du fichier             /!\ on ne gère pas les cas d'erreurs ici
      *folderName = (char*)argv[i];
    }
  }
  mkdir(*folderName, *folderMode);
}
