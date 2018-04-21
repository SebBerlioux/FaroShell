#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "cd.h"

void fcd(int argc, char const *argv[]){
  if(argc == 1){
    struct passwd *pw = getpwuid(getuid()); // on recupère l'ID de l'utilisateur courant
    const char *homedir = pw->pw_dir; // On recupere ensuite le mot de passe qui contient le dossier personnel "HOME" de l'utilisateur
    chdir(homedir);
  }else{
    struct stat st;	//On a besoin des infos du fichier pour savoir si on peut y entrer
    char* dossier = NULL;
    strcat(dossier,argv[1]);
    lstat(dossier,&st);
    if((st.st_mode & S_IRUSR)==S_IRUSR){ //On teste si l'on a les droit de lecture du contenu
      chdir(argv[1]);

    }
    else{
      printf("Vous n'avez pas le droit d'entrer dans ce dossier");
    }
  }
}
