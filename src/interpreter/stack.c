#include "stack.h"

struct SStack
{
  Arguments arguments[MAX_SIZE];
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

void push_elem(SStack *stack, Arguments args)
{
  if (stack->size < MAX_SIZE)
  {
    stack->arguments[stack->size++] = args;
    stack->size++;
  }
}

Arguments pop_elem(SStack *stack)
{
  Arguments result;
  if (stack->size > 0)
  {
    result = stack->arguments[stack->size];
  }
  return result;
}

int get_size(SStack *stack)
{
  return stack->size;
}
