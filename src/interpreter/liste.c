#include "liste.h"

struct SCell
{
  Data value;
  SCell *next;
  SCell *prev;
};

struct SList
{
  SCell *head;
  SCell *tail;
  int size;
};

SList* CreateList()
{
  SList *list;
  list = malloc(sizeof(SList));
  list->size = 0;
  return list;
}

void DeleteList(SList *list)
{
  if (list->size != 0) {
    SCell *cell = list->head;
    SCell *tmp;
    while (cell != NULL) {
      tmp = cell;
      cell = cell->next;
      free(tmp);
    }
  }
  free(list);
}

SCell* AddElementBegin(SList *list,Data elem)
{
  SCell *newCell;
  newCell = malloc(sizeof(SCell));
  newCell->value = elem;
  if (list->size == 0) {
    list->head = newCell;
    list->tail = newCell;
  } else {
    list->head->prev = newCell;
    newCell->next = list->head;
    list->head = newCell;
  }
  list->size++;
  return list->head;
}

SCell* AddElementEnd(SList *list,Data elem)
{
  SCell *newCell;
  newCell = malloc(sizeof(SCell));
  newCell->value = elem;
  if (list->size == 0) {
    list->head = newCell;
    list->tail = newCell;
  } else {
    list->tail->next = newCell;
    newCell->prev = list->tail;
    list->tail = newCell;
  }
  list->size++;
  return list->tail;
}

SCell* AddElementAfter(SList *list,SCell *cell,Data elem)
{
  SCell *newCell;
  newCell = malloc(sizeof(SCell));
  newCell->value = elem;

  newCell->next = cell->next;
  cell->next = newCell;
  newCell->prev = cell;
  newCell->next->prev = newCell;

  return newCell;
}

void DeleteCell(SList *list,SCell *cell)
{
  if(list->head->value == cell->value) {
    list->head = cell->next;
  } else if (list->tail->value == cell->value) {
    list->tail = list->tail->prev;
    list->tail->next = NULL;
  } else {
    cell->prev->next = cell->next;
  }
  free(cell);
  list->size--;
}

SCell* GetFirstElement(SList *list)
{
  return list->head;
}

SCell* GetLastElement(SList *list)
{
  return list->tail;
}

SCell* GetPrevElement(SCell *cell)
{
  return cell->prev;
}

SCell* GetNextElement(SCell *cell)
{
  return cell->next;
}

Data GetData(SCell *cell)
{
  return cell->value;
}

int GetSize()
{
  return cell->size;
}
