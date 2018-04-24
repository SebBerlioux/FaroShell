#include "du.h"

int fdu(int argc, char *argv[]){

  struct stat s;
  DIR *dir;
  struct dirent *subdir = NULL;


  if(argc == 1){ // dossier courant

    char cwd[100];
    getcwd(cwd, 100);

    dir = opendir(cwd);
    /*
      // on recupere le directoire HOME
      struct passwd *pw = getpwuid(getuid());
      const char *homedir = pw->pw_dir;
      stat(homedir,&s); // on stocke dans s les données du dossier homedir
      printf("%li\t\t%s\n", s.st_size, homedir);
    */
  }else{

    dir = opendir(argv[1]);
    if(dir == NULL){
      printf("Le dossier %s n'existe pas !", argv[1]);
      return 1; // retour erreur
    }
  } // end else

  // ici, le dossier existe et on le connait
  while((subdir = readdir(dir)) != NULL){ // on parcours les sous dossiers subdir du dossier dir
    stat(subdir->d_name,&s);
    printf("%ld\t\t%s\n", s.st_size, subdir->d_name);
  }
  closedir(dir);
  return 0;
}
