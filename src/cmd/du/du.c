#include "du.h"

int fdu(int argc, char *argv[]){

  extern int optind;
  int opt;
  int indicateurFichier = 1;

  int caseA = 0;
  int caseC = 0;
  int caseH = 0;

  /****** options *******/

  while((opt = getopt(argc, argv, "ach")) != -1){
    switch(opt){
      case 'a':
        caseA = 1;
        indicateurFichier++;
        break;
      case 'c':
        caseC = 1;
        indicateurFichier++;
      case 'h':
        caseH = 1;
        indicateurFichier++;
      default:
        break;
    }
  }

  /****** lecture dossiers *******/

  struct stat s;
  DIR *dir;
  struct dirent *subdir = NULL;
  //struct dirent *subsubdir = NULL;


  if(argc == 1 || argv[optind] == NULL){ // dossier courant
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
    dir = opendir(argv[indicateurFichier]);
    if(dir == NULL){
      printf("Le dossier %s n'existe pas !", argv[1]);
      return 1; // retour erreur
    }
  } // end else

  // ici, le dossier existe et on le connait
  int tailleTotale = 0;

  while((subdir = readdir(dir)) != NULL){ // on parcours les sous dossiers subdir du dossier dir
    stat(subdir->d_name,&s);

  /*  if((subsubdir = readdir(subdir)) != NULL){ // récurence (on regarde les dossiers du sous-dossier)
      stat(subsubdir->d_name,&s);
      char *tmpArgv[] = *argv;
      tmpArgv[argc-1] = subsubdir->d_name;
      fdu(argc,tmpArgv);
    } */

    if(caseA){ // tous les fichiers
      if(caseH){
        conversionHumanReadable(s.st_size, subdir->d_name, 1);
      }else{
        printf("%ld\t%s\n", s.st_size, subdir->d_name);
      }

      if(caseC){
        tailleTotale += s.st_size;
      }

    }else{
      if(subdir->d_type == DT_DIR){ // uniquement les dossiers (du sans option)
        if(caseH){
          conversionHumanReadable(s.st_size, subdir->d_name, 1);
        }else{
          printf("%ld\t%s\n", s.st_size, subdir->d_name);
        }

        if(caseC){
          tailleTotale += s.st_size;
        }
      }
    } // end else

  } // end while
  if(caseC){
    if(caseH){
      conversionHumanReadable(tailleTotale,"total",1);
    }else{
      printf("%i\ttotal\n", tailleTotale);
    }
  }
  closedir(dir);
  return 0;
}

void conversionHumanReadable(off_t size, char *name, int indice){
  if(size < 1000){ // inférieur à 1000 bytes
    if(indice == 1){
      printf("%ldB\t%s\n", size, name);
    }else if(indice == 2){
      printf("%ldK\t%s\n", size, name);
    }else if(indice == 3){
      printf("%ldM\t%s\n", size, name);
    }else if(indice == 2){
      printf("%ldG\t%s\n", size, name);
    }else if(indice == 2){
      printf("%ldT\t%s\n", size, name);
    }
  }else{ // superieur a 1000 bytes
    conversionHumanReadable(size/1000,name, indice+1);
  }
}
