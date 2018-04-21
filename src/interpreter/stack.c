#include "stack.h"

struct SElem
{
  int argc;
  char *argv[];
};

struct SStack
{
  SElem elems[MAX_SIZE];
  int size;
};

SStack* create_stack()
{
  SStack *stack;
  stack = malloc(sizeof(SStack));
  stack->size = 0;
  return stack;
}

void delete_stack(SStack *stack)
{
  free(stack);
}

void push_elem(SStack *stack, SElem elem)
{
  if (stack->size < MAX_SIZE)
  {
    stack->elems[stack->size++] = elem;
    stack->size++;
  }
}

SElem pop_elem(SStack *stack)
{
  SElem result;
  if (stack->size > 0)
  {
    result = stack->elems[stack->size];
  }
  return result;
}

int get_size(SStack *stack)
{
  return stack->size;
}
