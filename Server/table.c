#include "table.h"

void tableInit(TABLE* table, int countColumns) {
    table->countColumns = countColumns;
    table->columns = calloc(countColumns, sizeof(COLUMN*));
    table->countEntries = 0;
}
