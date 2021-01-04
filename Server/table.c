#include "table.h"

void tableInit(TABLE* table, int countColumns) {
    table->countColumns = countColumns;
    table->columns = calloc(countColumns, sizeof(COLUMN*));
    table->countEntries = 0;
}

void tableAddColumns(TABLE* table, char* buffer) {
    for (int i = 0; i < table->countColumns; i++) {
        COLUMN* column;
        column = (COLUMN*) malloc(sizeof(COLUMN));
        columnInit(column, *(buffer + 2 + i) - '0');
    }
}