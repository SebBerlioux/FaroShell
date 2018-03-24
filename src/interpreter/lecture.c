#include <stdio.h>
#include <stdlib.h>

#include "lecture.h"

char* lireCommande(void)
{
	char *arguments = NULL;	// tableau qui contient les arguments rentrés
	ssize_t nbArgument = 0; // have getline allocate a buffer for us
	nbArgument = getline(&arguments, &nbArgument, stdin);	// recupere la ligne rentree
	
	// on supprime le retour à la ligne
	if(arguments[nbArgument - 1] == '\n')
		arguments[nbArgument - 1] = '\0';

	return arguments;
}