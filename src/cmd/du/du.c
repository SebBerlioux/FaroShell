#include "du.h"

void fdu(int argc, char *argv[]){

  struct stat s;

  if(argc == 1){ // dossier HOME
    // on recupere le directoire HOME
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    stat(homedir,&s); // on stocke dans s les données du dossier homedir
    printf("%li\t\t%s\n", s.st_size, homedir);
  }else{

    DIR *dir;
    struct dirent *subdir = NULL;

    dir = opendir(argv[1]);
    if(dir == NULL){
      printf("Le dossier %s n'existe pas !", argv[1]);
      exit(EXIT_FAILURE);
    }
    // ici, le dossier existe
    while((subdir = readdir(dir)) != NULL){ // on parcours les sous dossiers subdir du dossier dir
      stat(subdir->d_name,&s);
      printf("%ld\t\t%s\n", s.st_size, subdir->d_name);
    }
    closedir(dir);
  }

}
