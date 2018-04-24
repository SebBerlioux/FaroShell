#include "cat.h"

// ex:$ cat [-options] [fichier]

int fcat(int argc, char *argv[]){

  if(argc < 2){ // manque de parametre
    printf("Erreur, manque de parametre !\n");
    printf("Usage: cat [-option(s)] [fichier]\n");
    return 1; // retour erreur
  }
  else{

    /*
       *************************
       *        OPTIONS        *
       *************************
    */
    extern int optind;
    int opt;
    int indicateurFichier = 1;

    // validateurs d'option
    int caseA = 0;
    int caseE = 0;
    int caseN = 0;
    int caseT = 0;

    while((opt = getopt(argc, argv, "AbEenT")) != -1){
      switch (opt) {
        case 'A': // display $ at end of each line & display TAB characters as ^I
          caseA = 1; // l'option A est activee
          indicateurFichier++;
          break;
        case 'E': // display $ at end of each line
          caseE = 1; // l'option E ou e est activee
          indicateurFichier++;
          break;
        case 'n': // number all output lines
          caseN = 1; // l'option N est activee
          indicateurFichier++;
          break;
        case 'T': // display TAB characters as ^I
          caseT = 1; // l'option T ou t est activee
          indicateurFichier++;
          break;
        case '?':
          printf("Incorrect argument given: %s\n", argv[optind-1]);
          printf("Available arguments are: -A, -b, -E (-e), -n, -T (-t) \n");
          return 1; //retour erreur
          break;
        default: printf("bonsoir\n"); break;
      }//end switch
    }//end while

    /*
      **********************
      *   LECTURE FICHIER  *
      **********************
    */

    FILE *fp;

    fp = fopen(argv[indicateurFichier], "r");
    if (fp == NULL){ // erreur lors de l'ouverture du fichier
      printf("Erreur lors de l'ouverture du fichier !\n");
      return 1; //retour erreur
    }

    int n = 0; // compteur de ligne, sera affiché si option -n
    int c;
    char cchar;

    int affichage = 1;
    int nouvelleLigne = 1;

    while((c = fgetc(fp)) != EOF){ // lecture de chaque caractère du fichier
      affichage = 1;
      if(caseN){ // option n --------------- ok
        if(nouvelleLigne){
          n++;
          printf("\t%i  ", n);
          nouvelleLigne = 0;
        }
      }

      if(c == '\t'){ // option T ou A  ------------- ok pour T
        if(caseT || caseA){
          printf("^I");
          affichage = 0;
        }
      }
      if(c == '\n'){ // option E ou A
        if(caseE || caseA){
          printf("$\n");
          affichage = 0;
        }
        nouvelleLigne = 1;
      }

      if(affichage){
        cchar = (char) c;
        printf("%c", cchar);
      }
    } // end while

      fclose(fp);
  } // end else
  printf("\n");
  return 0;
} //end function
