#ifndef SERVER_TABLE_H
#define SERVER_TABLE_H

#include "column.h"

typedef struct table {
    int countColumns;
    COLUMN** columns;
    int countEntries;
} TABLE;

void tableInit(TABLE* table, const int countColumns);
void tableDispose(TABLE* table);
void tableAddColumns(TABLE* table, const char* buffer);
bool tableGetColumnsType(const TABLE* table, char* buffer);
bool tableAddEntry(TABLE* table, char* buffer);
bool tableRemoveEntry(TABLE* table, int indexEntry);
bool tableGetEntry(const TABLE* table, const int indexEntry, char* buffer);
void tablePrint(const TABLE* table);
bool tableGetStringEntry(const TABLE* table, const char* str, char* buffer);
void tableStringPrint(const TABLE* table, char* str);
bool tableSort(TABLE* table, const int indexColumn, const bool ascending);

#endif //SERVER_TABLE_H
