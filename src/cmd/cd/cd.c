#include "cd.h"

void fcd(int argc, char const *argv[]){
  printf("hello\n");

  if(argc == 1){
    struct passwd *pw = getpwuid(getuid()); // on recupère l'ID de l'utilisateur courant
    const char *homedir = pw->pw_dir; // On recupere ensuite le mot de passe qui contient le dossier personnel "HOME" de l'utilisateur
    chdir(homedir);
  }else{
    chdir(argv[1]);
  }
}
