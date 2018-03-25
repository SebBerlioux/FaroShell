#include "parse.h"

void parseParamsList(SList *liste, char* commande)
{
	int nbArguments = NOMBRE_ARGUMENT;	// nombre d'argument max initial
	int cmpt = 0;	// cmpt de position dans la liste
	char* argument;	// un parametre

	argument = strtok(commande, " "); // recupere le premier "token" avant un espace
	while (argument != NULL)	// tant que pas fin de chaine
	{
		AddElementEnd(liste, argument);	// ajout du parametre lu a la liste
		argument = strtok(NULL, " ");	// recupere le "token" suivant
	}
}

char* executeCommand(SList *liste)
{
	char *command = GetData(GetFirstElement(liste));
	char* result = "";

	if (strcmp(command, "echo") == 0)
	{
		result = executeEcho(liste);
	}
	return result;
}
