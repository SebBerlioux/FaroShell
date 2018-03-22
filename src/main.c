#include <stdio.h>
#include <string.h>

#include "liste.h"
#include "lecture.h"
#include "parse.h"

int main(void)
{
	printf("\033[H\033[2J");	// efface la console

	char *commande;	// commande rentree
	SList *parametresList;	// liste des parametres (dont nom de commande)

	do
	{
		parametresList = CreateList();	// init liste
		printf("> ");	// pour le bo-jeu
		commande = lireCommande();	// lecture d'une commande entiere
		parseParamsList(parametresList, commande);	// separation de chaque parametre dans une liste doublement chainee
		printf("> Commande rentrée : ");	// affichage de la commande rentree
		PrintList(parametresList);	// affichage de la commande rentree
		DeleteList(parametresList);	// suppression des donnees de la commande rentree
	}
	while(strcmp(commande, "exit"));	// fin de la boucle lorsque "exit" rentree

	return 0;
}
