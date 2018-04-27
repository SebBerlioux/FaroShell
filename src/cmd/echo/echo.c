#include "echo.h"
#include "../../utils/faroprint.h"

int fecho(int argc, char *argv[])
{

  extern int optind;
  int opt;

  int nbArg = 1; // compteur d'arguments (init à 1 pour ne pas compter la commande)
  // validateurs d'option
  int caseN = 0;
  int caseE = 0;

  while((opt = getopt(argc, argv, "ne")) != -1){
    switch (opt) {
      case 'n':
        caseN = 1;
        break;
      case 'e':
        caseE = 1;
        break;
      default:
        break;
    }
  }

  nbArg = optind;
  int k = 0; // compteur pour mettre tout les strings à lire dans toRead
  int t = 0;
  // on alloue la mémoire suffisante à toRead pour toutes les string à lire
  int tmp = argc - nbArg;
  char tmpC;
  char *toRead = (char*)malloc((tmp)*sizeof(char));

  // on charge toutes les strings dans toRead
  while(nbArg != argc){
    do{
      tmpC = argv[nbArg][t];
      toRead[k] = tmpC;
      k++;
      t++;
    }while(tmpC != '\0');
    nbArg++;
    t = 0;
  }

  char *line = (char*)malloc(sizeof(toRead)); // chaine transformée avec une taille maximale égale à celle de toRead (cas sans option)

  if(toRead == NULL){ // string missing
    faroprint("Error: argument missing\n");
    faroprint("Usage: echo [-option][string]\n");
    free(toRead);
    free(line);
    return 1; // retour erreur
  }


  char c;
  int i = 0;
  int option = 0;

  int indiceLine = 0; // indice pour la ligne à remplir qui sera affichée

  // on regarde chaque caractère de la string à lire
  while (k != 0) {
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
    else{ // cas sans option
      line[i] = c;
    }
    i++;
    k--;
  } //  end while

  for(int j = 0; j<i; j++){
    faroprint("%c", line[j]);
  }

  free(toRead);
  free(line);
  if(!caseN){faroprint("\n");} // option -n

  return 0;
}
