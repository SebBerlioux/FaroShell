#ifndef _PARSE_H
	#define _PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "../cmd/echo/echo.h"
#include "../cmd/cat/cat.h"
#include "../cmd/pwd/pwd.h"
#include "../cmd/cd/cd.h"
#include "../cmd/rm/rm.h"
#include "../cmd/mv/mv.h"
#include "../cmd/mkdir/mkdir.h"
#include "../cmd/ls/ls.h"

#define NOMBRE_ARGUMENT 10

void parseParamsList(SList *liste, char* commande);
void executeCommand(SList *liste);

#endif
