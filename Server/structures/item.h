#ifndef LINKEDLIST_ITEM_H
#define LINKEDLIST_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
//#include "../../CMemLeak.h"

enum type_tag {
    INT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    BOOL_TYPE
};

typedef struct item {
    enum type_tag type;
    void* data;
    struct item* next;
    struct item* prev;
} ITEM;

void itemAddData(ITEM *item, void *data);
void itemDeleteData(ITEM *item);
void itemCopy(const ITEM *src, ITEM *dest, const enum type_tag type);
void itemSetData(ITEM *item, const void *data, const enum type_tag type);
void* itemGetData(const ITEM *item, void *data);
int itemCompareData(const void *data1, const void *data2, const enum type_tag type);
int itemCompare(const ITEM *item1, const ITEM *item2);
void itemPrintData(const void *data, const enum type_tag type);
void itemPrint(const ITEM *item);
void itemFilePrint(const ITEM *item, FILE *txtFile);

#endif //LINKEDLIST_ITEM_H
