#include "echo.h"

int fecho(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  printf("\n");

  return 0;

}
