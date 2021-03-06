#include "lecture.h"

#define NOMBRE_ARGUMENT 1024

/*
	Fonction qui lit la ligne de commande rentrée dans le shell
*/
char* lireCommande(void)
{
	int nbArgument = NOMBRE_ARGUMENT;
	int cmpt = 0;
	char* arguments = malloc(sizeof(char) * nbArgument);
	int caractere;
	int autorisationEspace = 0;
	int spaced = 0;

	if (!arguments)
	{
		fprintf(stderr, "FaroShell: erreur d'allocation mémoire\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		caractere = getchar();

		if (caractere == EOF || caractere == '\n')
		{
			arguments[cmpt] = '\0';
			return arguments;
		}
		else if (caractere == ' ')
		{
			if (autorisationEspace == 1)
			{
				if (spaced == 0)
				{
					arguments[cmpt] = caractere;
					cmpt++;
					spaced = 1;
				}
			}
		}
		else
		{
			arguments[cmpt] = caractere;
			cmpt++;

			if (autorisationEspace == 0)
			{
				autorisationEspace = 1;
			}

			if (spaced == 1)
			{
				spaced = 0;
			}
		}

		if (cmpt >= nbArgument)
		{
			nbArgument += NOMBRE_ARGUMENT;
			arguments = realloc(arguments, nbArgument);
			if (!arguments)
			{
				fprintf(stderr, "FaroShell: erreur d'allocation mémoire\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
