#ifndef _PARSE_H
	#define _PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "../cmd/echo/echo.h"

#define NOMBRE_ARGUMENT 10

void parseParamsList(SList *liste, char* commande);
void executeCommand(SList *liste);

#endif
