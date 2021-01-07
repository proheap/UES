#include "table.h"

void tableInit(TABLE* table, int countColumns) {
    table->countColumns = countColumns;
    table->columns = (COLUMN**) malloc(countColumns * sizeof(COLUMN*));
    table->countEntries = 0;
}

void tableAddColumns(TABLE* table, char* buffer) {
    for (int i = 0; i < table->countColumns; i++) {
        COLUMN* column;
        column = (COLUMN*) malloc(sizeof(COLUMN));
        columnInit(column, *(buffer + 2 + i) - '0');
        table->columns[i] = column;
    }
}

bool tableGetColumnsType(TABLE* table, char* buffer) {
    if (table->countColumns == 0) {
        return false;
    }
    *(buffer) = table->countColumns;
    for (int i = 0; i < table->countColumns; i++) {
        *(buffer + 1 + i) = table->columns[i]->type + '0';
    }
    return true;
}

bool tableAddEntry(TABLE* table, char* buffer) {
    void* data;
    char* p1 = buffer;
    for (int c = 0; c < table->countColumns; c++) {
        char* p2 = strchr(p1, ':');
        data = p2 - p1;
        columnAddEntry(table->columns[c], data);
        p1 = p2 + 1;
    }
    table->countEntries++;
    return true;
}

bool tableGetEntry(TABLE* table, int indexEntry, char* buffer) {
    if (indexEntry < 0 || indexEntry >= table->countEntries) {
        return false;
    }

    void* data;
    for (int c = 0; c < table->countColumns; c++) {
        columnGetEntry(table->columns[c], indexEntry, data);
        strcat(buffer, *((char*)data));
        strcat(buffer, ":");
    }
    return true;
}

void tablePrint(TABLE* table) {
    printf("Tabulka:\n");
    printf("--------\n");
    for (int i = 0; i < table->countEntries; i++) {
        for (int c = 0; c < table->countColumns; c++) {
            columnPrintData(table->columns, i);
        }
        printf("\n");
    }
}