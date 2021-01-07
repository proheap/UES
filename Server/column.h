#ifndef SERVER_COLUMN_H
#define SERVER_COLUMN_H

#include "./structures/linked_list.h"
#include "../CMemLeak.h"

typedef struct column {
    enum type_tag type;
    LINKED_LIST* entry;
} COLUMN;

void columnInit(COLUMN* column, enum type_tag tag);
void columnAddEntry(COLUMN* column, void* data);
void columnGetEntry(COLUMN* column, int indexEntry, void* data);
void columnPrintData(COLUMN* column, int indexEntry);

#endif //SERVER_COLUMN_H
