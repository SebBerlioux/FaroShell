#include "echo.h"

char* executeEcho(SList* liste)
{
  char* result = "";
  SCell *cell = GetNextElement(GetFirstElement(liste));
  while (cell != NULL)
  {
  	strcat(result, GetData(cell));
    strcat(result, " ");
  	cell = GetNextElement(cell);
  }
  strcat(result, "\n");
  return result;
}
