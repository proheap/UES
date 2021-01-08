#ifndef SERVER_COLUMN_H
#define SERVER_COLUMN_H

#include "./structures/linked_list.h"
#include "../CMemLeak.h"

typedef struct column {
    enum type_tag type;
    LINKED_LIST* entry;
} COLUMN;

void columnInit(COLUMN* column, const enum type_tag tag);
void columnDispose(COLUMN* column);
void columnAddEntry(COLUMN* column, void* data);
bool columnGetEntry(const COLUMN* column, const int indexEntry, void* data);
void columnPrintData(const COLUMN* column, const int indexEntry);
bool columnSwapEntries(COLUMN* column, const int indexEntry1, const int indexEntry2);

#endif //SERVER_COLUMN_H
