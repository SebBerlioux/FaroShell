#include "parse.h"

void parseParamsList(SList *liste, char* commandLine)
{
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
	if (GetData(GetFirstElement(liste)))
	{
		//printf("Debug\n");
		char *cmd = GetData(GetFirstElement(liste));
		int nbArgs;

		DeleteCell(liste, GetFirstElement(liste));
		nbArgs = GetSize(liste);
		char *args[nbArgs];

		SCell *cell = GetFirstElement(liste);
		for (int i = 0; i < nbArgs; i++)
		{
			args[i] = GetData(cell);
			cell = GetNextElement(cell);
		}

		if (strcmp(cmd, "echo") == 0)
		{
			fecho(nbArgs, args);
		}
		else if (strcmp(cmd, "cat") == 0)
		{
			//fcat(nbArgs, args);
		}
	}
}
