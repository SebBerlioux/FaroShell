#include <stdio.h>
#include <string.h>

#include "../libs/liste.h"
#include "lecture.h"
#include "parse.h"

#define SHELLNAME "FaroShell"
#define EXIT_CMD "exit"

#define ANSI_COLOR_CYAN    "\x1b[96m"
#define ANSI_COLOR_YELLOW  "\x1b[93m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(void)
{
	printf("\033[H\033[2J");	// efface la console

	char *commande;	// commande rentree
	SList *parametresList;	// liste des parametres (dont nom de commande)
	char* result; // le résultat de la commande

	do
	{
		parametresList = CreateList();	// init liste
		printf(ANSI_COLOR_YELLOW "User" ANSI_COLOR_CYAN "@%s" ANSI_COLOR_RESET "\n",
			SHELLNAME);
		printf("> ");	// prompt
		commande = lireCommande();	// lecture d'une commande entiere
		parseParamsList(parametresList, commande);	// separation de chaque parametre dans une liste doublement chainee
		result = executeCommand(parametresList);
		printf("%s", result);
		printf("> Commande rentrée : ");	// affichage de la commande rentree
		PrintList(parametresList);	// affichage de la commande rentree
		DeleteList(parametresList);	// suppression des donnees de la commande rentree
	}
	while(strcmp(commande, EXIT_CMD));	// fin de la boucle lorsque "exit" rentree

	return 0;
}
