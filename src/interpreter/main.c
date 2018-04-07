#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

#include "liste.h"
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

	char *commandLine;	// ligne de commande rentree
	SList *parametresList;	// liste des parametres (dont nom de commande)

	do
	{
		parametresList = CreateList();	// init liste
		printf(ANSI_COLOR_YELLOW "User" ANSI_COLOR_CYAN "@%s" ANSI_COLOR_RESET "\n",
			SHELLNAME);
		printf("> ");	// prompt
		commandLine = lireCommande();	// lecture d'une commande entiere
		parseParamsList(parametresList, commandLine);	// separation de chaque parametre dans une liste doublement chainee
//		printf("> Commande rentrée : ");	// affichage de la commande rentree
//		PrintList(parametresList);	// affichage de la commande rentree
		executeCommand(parametresList);
//		DeleteList(parametresList);	// suppression des donnees de la commande rentree
	}
	while(strcmp(commandLine, EXIT_CMD));	// fin de la boucle lorsque "exit" rentree
	printf("Goodbye !\n");

	return 0;
}
