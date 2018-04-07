#include "echo.h"

void executeEcho(int argc, char *argv[])
{
  char* result = "";
  for (int i = 0; i < argc; i++)
  {
    strcat(result, argv[i]);
  }
  strcat(result, "\n");
  printf("%s", result);
}
