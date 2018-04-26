#include "echo.h"

int fecho(int argc, char *argv[])
{

  extern int optind;
  int opt;
  int indicateurString = 1;

  // validateurs d'option
  int caseN = 0;
  int caseE = 0;

  char *toRead[];
  char *line[];

  while((opt = getopt(argc, argv, "ne")) != -1){
    switch (opt) {
      case 'n':
        caseN = 1;
        indicateurString++;
        break;
      case 'e':
        caseE = 1;
        indicateurString++;
        break;
      default:
        toRead = argv[optind];
        break;
    }
  }

  if(toRead == NULL){ // string missing
    printf("Error: argument missing\n");
    printf("Usage: echo [-option][string]\n");
    return 1; // retour erreur
  }

  char c;
  int option = 0;

  int indiceLine = 0; // indice pour la ligne à remplir qui sera affichée

  for (int i = 0; i < toRead; i++) // on regarde chaque caractère de la string à lire
  {
    c = toRead[i];
    if(caseE){ // interpretation of backslash escapes

      if(c == '\\'){option = 1;} // un option est aà venir
      else if(c == 'a' && option == 1){line[indiceLine] = "\a"; indiceLine++;} // déclenche un son 'BEEP'
      else if(c == 'b' && option == 1){
        if(line[indiceLine] != NULL){ // si on n'est pas au début de la string
          line[indiceLine] = NULL; // on supprime le caractère précédent
        }
      }
      else if(c == 'e' && option == 1){i++;} // on saute le prochain caractère
      else if(c == 'n' && option == 1){line[indiceLine] = "\n"; indiceLine++;} // saut de ligne
      else if(c == 'r' && option == 1){indiceLine = 0;} // on revient au début de la ligne à écrire
      else if(c == 't' && option == 1){line[indiceLine] = "\t"; indiceLine++;} // tabulation
      else{ // cas d'une lettre non option
        line[i] = toRead[i]; // on ajoute la lettre à la ligne à lire
        indiceLine++;
      }

      if(c == 'c' && option == 1){return 0;}
      option = 0;

    } // end caseE
    else{
      for(int i = 0; i<toRead; i++){
        printf("%c",toRead[i]);
      }
    }
  } // end for

  //printf("%s ", toRead[i]); //On les affiche les uns derière les autres

  if(!caseN){
    printf("\n");
  }

  return 0;
}
