#include "echo.h"

void fecho(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  printf("\n");
}
