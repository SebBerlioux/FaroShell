#include "echo.h"

int fecho(int argc, char *argv[])
{

  extern int optind;
  int opt;
  int indicateurString = 1;

  // validateurs d'option
  int caseN = 0;
  int caseE = 0;

  char *toRead = NULL;

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
        break;
    }
  }
  toRead = argv[optind];
  char *line = (char*)malloc(sizeof(toRead)); // chaine transformée

  if(toRead == NULL){ // string missing
    faroprintf("Error: argument missing\n");
    faroprintf("Usage: echo [-option][string]\n");
    return 1; // retour erreur
  }


  char c;
  int i = 0;
  int option = 0;

  int indiceLine = 0; // indice pour la ligne à remplir qui sera affichée

  // on regarde chaque caractère de la string à lire
  while (toRead[i] != '\0') {
    c = toRead[i];

    if(caseE){ // interpretation of backslash escapes -- option -e

      if(c == '\\'){option++;} // un option est à venir (il faut 2 \ pour l'activer)
      else if(c == 'a' && option == 1){line[indiceLine] = '\a'; indiceLine++;option = 0;} // déclenche un son *BEEP*
      else if(c == 'b' && option == 1){i--;option = 0;} // on revient en arrière d'un caractère
      else if(c == 'e' && option == 1){i++;option = 0;} // on saute le prochain caractère
      else if(c == 'n' && option == 1){line[indiceLine] = '\n'; indiceLine++;option = 0;} // saut de ligne
      else if(c == 'r' && option == 1){indiceLine = 0;option = 0;} // on revient au début de la ligne à écrire
      else if(c == 't' && option == 1){line[indiceLine] = '\t'; indiceLine++;option = 0;} // tabulation
      else if(c == 'c' && option == 1){break;}
      else{ // cas d'une lettre non option
        line[indiceLine] = toRead[i]; // on ajoute la lettre à la ligne à lire
        indiceLine++;
      }


    } // end caseE
    else{
      line[i] = c;
    }
    i++;
  } //  end while

  for(int j = 0; j<i; j++){
    faroprintf("%c", line[j]);
  }

  free(line);
  if(!caseN){faroprintf("\n");} // option -n

  return 0;
}
