#ifndef _STACK_H
	#define _STACK_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 10

typedef char* Data;
typedef struct SStack SStack;
typedef struct SElem SElem;

/*
	Fonction d'initialisation d'un SStack
*/
SStack* create_stack();
/*
	Fonction de supression d'un SStack
*/
void delete_stack(SStack *stack);

/*
	Push un élément dans le SStack
*/
void push_elem(SStack *stack, SElem elem);
/*
  Pop le SStack
*/
SElem pop_elem(SStack *stack);
/*
	Retourne la taille du SStack
*/
int get_size(SStack *stack);

#endif
