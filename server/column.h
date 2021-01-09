#ifndef SERVER_COLUMN_H
#define SERVER_COLUMN_H

#include <stdlib.h>

#include "./structures/linked_list.h"

#define DATA_SIZE 30

typedef struct column {
    enum type_tag type;
    LINKED_LIST* entry;
} COLUMN;

void columnInit(COLUMN* column, const enum type_tag tag);
void columnDispose(COLUMN* column);
void columnAddEntry(COLUMN* column, const void* data);
bool columnRemoveEntry(COLUMN* column, const int indexEntry);
bool columnGetEntry(const COLUMN* column, const int indexEntry, void** data);
void columnGetDataString(const COLUMN* column, const void* data, char* strData);
bool columnSwapEntries(COLUMN* column, const int indexEntry1, const int indexEntry2);

#endif //SERVER_COLUMN_H
