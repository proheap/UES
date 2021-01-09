#ifndef LINKEDLIST_LINKED_LIST_H
#define LINKEDLIST_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"

typedef struct linked_list {
    ITEM* first;
    ITEM* last;
    int size;
} LINKED_LIST;

void llInit(LINKED_LIST *list);
void llDispose(LINKED_LIST *list);
void llPrint(const LINKED_LIST *list);
void llAdd(LINKED_LIST *list, const void *data, const enum type_tag type);
_Bool llTryInsert(LINKED_LIST *list, const void *data, const enum type_tag type, const int pos);
_Bool llTrySet(LINKED_LIST *list, const int pos, const void *data);
_Bool llTryGet(const LINKED_LIST *list, const int pos, void **data);
_Bool llTrySwap(LINKED_LIST *list, const int indexItem1, const int indexItem2);
bool llTryRemove(LINKED_LIST *list, const int pos);
_Bool llTryCopy(const LINKED_LIST *src, LINKED_LIST *dest);
void llReadFromTxt(LINKED_LIST *list, FILE *txtFile);
void llWriteToTxt(const LINKED_LIST *list, FILE *txtFile);

#endif //LINKEDLIST_LINKED_LIST_H
