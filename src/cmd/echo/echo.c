#include "echo.h"

void executeEcho(int argc, char *argv[])
{
  char* result = "";
  while (cell != NULL)
  {
  	strcat(result, GetData(cell));
    strcat(result, " ");
  	cell = GetNextElement(cell);
  }
  strcat(result, "\n");
  return result;
}
