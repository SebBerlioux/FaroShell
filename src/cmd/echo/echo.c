#include "echo.h"

void executeEcho(int argc, char *argv[])
{
  char* result;
  for (int i = 0; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  printf("\n");
}
