#ifndef LINKEDLIST_LINKED_LIST_H
#define LINKEDLIST_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "../../CMemLeak.h"

typedef struct linked_list {
    ITEM* first;
    ITEM* last;
    int size;
} LINKED_LIST;

void llInit(LINKED_LIST *list);
void llDispose(LINKED_LIST *list);
void llPrint(const LINKED_LIST *list);
void llAdd(LINKED_LIST *list, void *data, enum type_tag type);
_Bool llTryInsert(LINKED_LIST *list, void *data, enum type_tag type, int pos);
_Bool llTrySet(LINKED_LIST *list, int pos, void *data);
_Bool llTryGet(LINKED_LIST *list, int pos, void *data);
void* llTryRemove(LINKED_LIST *list, int pos, void **data);
_Bool llTryCopy(const LINKED_LIST *src, LINKED_LIST *dest);
void llReadFromTxt(LINKED_LIST *list, FILE *txtFile);
void llWriteToTxt(const LINKED_LIST *list, FILE *txtFile);

#endif //LINKEDLIST_LINKED_LIST_H
