#include "parse.h"

void parseParamsList(SList *liste, char* commandLine)
{
	int nbArguments = NOMBRE_ARGUMENT;	// nombre d'argument max initial
	int cmpt = 0;	// cmpt de position dans la liste
	char* argument;	// un parametre

	argument = strtok(commandLine, " "); // recupere le premier "token" avant un espace
	while (argument != NULL)	// tant que pas fin de chaine
	{
		AddElementEnd(liste, argument);	// ajout du parametre lu a la liste
		argument = strtok(NULL, " ");	// recupere le "token" suivant
	}
}

void executeCommand(SList *liste)
{
	char *cmd = GetData(GetFirstElement(liste));
	char* args;
	int nbArgs;



	if (strcmp(cmd, "echo") == 0)
	{
		executeEcho(liste);
	}
	return result;
}
