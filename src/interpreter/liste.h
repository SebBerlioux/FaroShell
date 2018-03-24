#ifndef _LISTE_H
	#define _LISTE_H

typedef char* Data;
typedef struct SCell SCell;
typedef struct SList SList;

SList* CreateList();
void DeleteList(SList *list);
void PrintList(SList *list);

SCell* AddElementBegin(SList *list,Data elem);	// non utilise
SCell* AddElementEnd(SList *list,Data elem);
SCell* AddElementAfter(SList *list,SCell *cell,Data elem);	// non utilise
void DeleteCell(SList *list,SCell *cell);	// non utilise

SCell* GetFirstElement(SList *list);
SCell* GetLastElement(SList *list);	// non utilise
SCell* GetPrevElement(SCell *cell);	// non utilise
SCell* GetNextElement(SCell *cell);
Data GetData(SCell *cell);

#endif
