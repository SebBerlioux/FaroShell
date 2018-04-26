#include "echo.h"

int fecho(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++) // Pour tous les arguments donnés avec la fonction
  {
    printf("%s ", argv[i]); //On les affiche les uns derière les autres
  }
  printf("\n");

  return 0;

}
