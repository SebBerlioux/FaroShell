#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "parse.h"

#define NOMBRE_ARGUMENT 10

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
