#ifndef _STACK_H
	#define _STACK_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 10

typedef struct Arguments {
	int argc;
	char **argv;
} Arguments;

typedef struct SStack SStack;

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
void push_elem(SStack *stack, Arguments args);
/*
  Pop le SStack
*/
Arguments pop_elem(SStack *stack);
/*
	Retourne la taille du SStack
*/
int get_size(SStack *stack);

#endif
