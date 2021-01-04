#include "evidence_system.h"

void esInit(EVIDENCE_SYSTEM* es) {
    LINKED_LIST tables;
    llInit(&tables);
    es->tables = &tables;
    es->countTables = 0;
}

bool esAddTable(EVIDENCE_SYSTEM* es, int countColumns, char* buffer) {
    TABLE* table = (TABLE*) malloc(sizeof(TABLE));
    tableInit(table, countColumns);
    tableAddColumns(table, buffer);
    llAdd(es->tables, table, STRUCT_TYPE);
    es->countTables++;
}