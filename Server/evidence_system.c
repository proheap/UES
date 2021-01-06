#include "evidence_system.h"

void esInit(EVIDENCE_SYSTEM* es) {
    es->table = NULL;
    es->countTables = 0;
}

bool esAddTable(EVIDENCE_SYSTEM* es, int countColumns, char* buffer) {
    if (es->table != NULL) {
        return false;
    }
    TABLE* table = (TABLE*) malloc(sizeof(TABLE));
    tableInit(table, countColumns);
    tableAddColumns(table, buffer);
    es->table = table;
    es->countTables++;
    return true;
}