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

#endif //SERVER_TABLE_H
