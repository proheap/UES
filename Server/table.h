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

#endif //SERVER_TABLE_H
