#ifndef _LISTE_H
	#define _LISTE_H

#include <stdlib.h>
#include <stdio.h>

typedef int Data;
typedef struct SCell SCell;
typedef struct SList SList;

/*
	Fonction d'initialisation d'une SList
*/
SList* CreateList();
/*
	Fonction de supression d'une SList
*/
void DeleteList(SList *list);

/*
	Ajoute un élément au début de la liste
*/
SCell* AddElementBegin(SList *list,Data elem);
/*
	Ajoute un élément à la fin de la liste
*/
SCell* AddElementEnd(SList *list,Data elem);
/*
	Ajoute un élément après un autre dans la liste
*/
SCell* AddElementAfter(SList *list,SCell *cell,Data elem);
/*
	Supprime une cellule de la liste
*/
void DeleteCell(SList *list,SCell *cell);

/*
	Retourne le premier élément de la liste
*/
SCell* GetFirstElement(SList *list);
/*
	Retourne le dernier élément de la liste
*/
SCell* GetLastElement(SList *list);
/*
	Retourne la cellule précédent celle passée en paramètre
*/
SCell* GetPrevElement(SCell *cell);
/*
	Retourne la cellule suivant celle passée en paramètre
*/
SCell* GetNextElement(SCell *cell);
/*
	Retourne les données d'une cellule
*/
Data GetData(SCell *cell);
/*
	Retourne la taille de la liste
*/
int GetSize();

#endif
