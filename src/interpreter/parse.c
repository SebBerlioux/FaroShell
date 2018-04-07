#include "parse.h"

void parseParamsList(SList *liste, char* commandLine)
{
	int nbArguments = NOMBRE_ARGUMENT;	// nombre d'argument max initial
	int cmpt = 0;	// cmpt de position dans la liste
	char* argument;	// un parametre

	printf("%s\n", commandLine);

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
	int nbArgs;

	DeleteCell(liste, GetFirstElement(liste));
	nbArgs = GetSize(liste);
	char *args[nbArgs];

	SCell *cell = GetFirstElement(liste);
	for (int i = 0; i < nbArgs; i++)
	{
		args[i] = GetData(cell);
		//strcat(args, GetData(cell));
		cell = GetNextElement(cell);
	}

	if (strcmp(cmd, "echo") == 0)
	{
		executeEcho(nbArgs, args);
	}
}
