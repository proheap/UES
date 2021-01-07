#ifndef SERVER_TABLE_H
#define SERVER_TABLE_H

#include "column.h"
#include "../CMemLeak.h"

typedef struct table {
    int countColumns;
    COLUMN** columns;
    int countEntries;
} TABLE;

void tableInit(TABLE* table, int countColumns);
void tableAddColumns(TABLE* table, char* buffer);
bool tableGetColumnsType(TABLE* table, char* buffer);
bool tableAddEntry(TABLE* table, char* buffer);
bool tableGetEntry(TABLE* table, int indexEntry, char* buffer);
void tablePrint(TABLE* table);

#endif //SERVER_TABLE_H
