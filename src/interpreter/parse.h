#ifndef _PARSE_H
	#define _PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cmd/echo/echo.h"
#include "../cmd/cat/cat.h"
#include "../cmd/pwd/pwd.h"
#include "../cmd/cd/cd.h"
#include "../cmd/cp/cp.h"
#include "../cmd/rm/rm.h"
#include "../cmd/mv/mv.h"
#include "../cmd/mkdir/mkdir.h"
#include "../cmd/ls/ls.h"
#include "../cmd/chmod/chmod.h"
#include "../cmd/chgrp/chgrp.h"
#include "../cmd/du/du.h"

#define NOMBRE_ARGUMENT 32
#define MAX_CMDS 10
#define DELIMITERS " \t\r\n\a"

void parseParams(char *commandLine);
void splitCommands(char* commandLine);
int executeCommand(int nbArgs, char *args[]);

#endif
