#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

// strucutre d'une cellule d'une liste doublement chainee
struct SCell
{
	Data value;	// valeur du parametre
	SCell *p_next;	// parametre suivant
	SCell *p_prev;	// parametre precedent
};

// structure d'une liste doublement chainee
struct SList
{
	SCell *p_head;	// tete de la liste
	SCell *p_tail;	// fin de la liste
};

// initialisation d'une nouvele liste
SList* CreateList()
{
	SList *p_newList = malloc(sizeof(*p_newList));	// allocation memoire

	p_newList->p_head = NULL;	// initialisation tete de la liste
	p_newList->p_tail = NULL;	// initialisation fin de la liste
	
	return p_newList;
}

// suppression d'une liste
void DeleteList(SList *list)
{
	SCell *p_tmp = list->p_head;	// recupere tete de liste

	while (p_tmp != NULL)	// tant que pas fin de liste (NULL)
	{
		SCell *p_del = p_tmp;	// enregistre cellule a supprimer
		p_tmp = p_tmp->p_next;	// maj cellule suivante
		free(p_del);	// supprime cellule a supprimer
	}
	free(list), list = NULL;	// supprime la liste
}

// affichage d'une liste
void PrintList(SList *list)
{
	if (list)
	{
		SCell *cell=GetFirstElement(list);
		while (cell!=NULL)
		{
			printf("[%s] ",GetData(cell));
			cell=GetNextElement(cell);
		}
		printf("\n");
	}
}

// ajout d'un parametre en debut de liste
SCell* AddElementBegin(SList *list, Data elem)
{
	SCell *p_newCell = malloc(sizeof(*p_newCell));

	// allocation valeur nouvelle cellule
	// cellule precedente a NULL (debut de liste)
	p_newCell->value = malloc(sizeof(elem));
	p_newCell->value = elem;
	p_newCell->p_prev = NULL;

	if (list->p_tail == NULL)	// liste vide
	{
		// maj tete et fin de liste car il y
		// a seulement la nouvelle valeur a ajouter
		p_newCell->p_next = NULL;
		list->p_head = p_newCell;
		list->p_tail = p_newCell;
	}
	else
	{
		// maj de la cellule precedant la tete de liste
		// cellule qui suit la nouvelle valeur devient
		// l'ancienne tete de liste
		// la tete de liste devient la nouvelle valeur
		list->p_head->p_prev = p_newCell;
		p_newCell->p_next = list->p_head;
		list->p_head = p_newCell;	
	}

	return p_newCell;
}

// ajout d'un parametre en fin de liste
SCell* AddElementEnd(SList *list, Data elem)
{
	SCell *p_newCell = malloc(sizeof(*p_newCell));

	// allocation valeur nouvelle cellule
	// cellule precedente a NULL (fin de liste)
	p_newCell->value = malloc(sizeof(elem));
	p_newCell->value = elem;
	p_newCell->p_next = NULL;

	if (list->p_head == NULL)	// liste vide
	{
		// maj tete et fin de liste car il y
		// a seulement la nouvelle valeur a ajouter
		p_newCell->p_prev = NULL;
		list->p_head = p_newCell;
		list->p_tail = p_newCell;
	}
	else
	{
		// maj de la cellule suivant la fin de liste
		// cellule qui precede la nouvelle valeur devient
		// l'ancienne fin de liste
		// la fin de liste devient la nouvelle valeur
		list->p_tail->p_next = p_newCell;
		p_newCell->p_prev = list->p_tail;
		list->p_tail = p_newCell;	
	}

	return p_newCell;
}

// ajout d'un parametre en milieu de liste
SCell* AddElementAfter(SList *list, SCell *cell, Data elem)
{
	SCell *p_tmp = list->p_head;

	while (p_tmp != NULL)
	{
		if (p_tmp == cell)	// cellule cherchee trouvee
		{
			if (p_tmp->p_next == NULL)	//fin de liste
			{
				return AddElementEnd(list, elem);
			}
			else if (p_tmp->p_prev == NULL)	//debut de liste
			{
				return AddElementBegin(list, elem);
			}
			else	//milieu de liste
			{
				SCell *p_newCell = malloc(sizeof(*p_newCell));

				p_newCell->value = malloc(sizeof(elem));
				p_newCell->value = elem;

				// maj precedent et suivant de nouvelle cellule
				p_newCell->p_prev = p_tmp;
				p_newCell->p_next = p_tmp->p_next;

				// ajout de la nouvelle cellule a la liste
				p_tmp->p_next->p_prev = p_newCell;
				p_tmp->p_next = p_newCell;

				return p_newCell;
			}
		}
		else
		{
			// cellule suivante
			p_tmp = p_tmp->p_next;
		}
	}
}

// suppression d'un parametre
void DeleteCell(SList *list, SCell *cell)
{
	SCell *p_tmp = list->p_head;
	int trouve = 0;
		
	while (p_tmp != NULL && !trouve)	// tant que pas a la fin et pas trouve
	{
		if (p_tmp == cell)	// cellule cherchee trouvee
		{
			if (p_tmp->p_next == NULL)	//fin de la liste
			{
				// maj fin de liste
				list->p_tail = p_tmp->p_prev;
				list->p_tail->p_next = NULL;
			}
			else if (p_tmp->p_prev == NULL)	//debut de la liste
			{
				// maj debut de liste
				list->p_head = p_tmp->p_next;
				list->p_head->p_prev = NULL;
			}
			else	//milieu de la liste
			{
				// maj milieu de liste
				p_tmp->p_next->p_prev = p_tmp->p_prev;
				p_tmp->p_prev->p_next = p_tmp->p_next;
			}
			// suppression cellule trouvee
			free(p_tmp);
			// trouve -> OK
			trouve = 1;
		}
		else
		{
			// cellule suivante
			p_tmp = p_tmp->p_next;
		}
	}
}

// recupere le premier parametre
SCell* GetFirstElement(SList *list)
{
	return list->p_head;
}

// recupere le dernier parametre
SCell* GetLastElement(SList *list)
{
	return list->p_tail;
}

// recupere le parametre qui precede cell
SCell* GetPrevElement(SCell *cell)
{
	return cell->p_prev;
}

// recupere le parametre qui suit cell
SCell* GetNextElement(SCell *cell)
{
	return cell->p_next;
}

// recupere la valeur du parametre
Data GetData(SCell *cell)
{
	return cell->value;
}