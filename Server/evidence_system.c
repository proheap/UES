#include "evidence_system.h"

void esInit(EVIDENCE_SYSTEM* es) {
    es->table = NULL;
}

bool esCreateTable(EVIDENCE_SYSTEM* es, int countColumns, char* buffer) {
    if (es->table != NULL) {
        return false;
    }
    TABLE* table = (TABLE*) malloc(sizeof(TABLE));
    tableInit(table, countColumns);
    tableAddColumns(table, buffer);
    es->table = table;
    return true;
}

bool esGetColumnsType(EVIDENCE_SYSTEM* es, char* buffer) {
    if (es->table != NULL) {
        return false;
    }
    return tableGetColumnsType(es->table, buffer);
}

bool esAddEntry(EVIDENCE_SYSTEM* es, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableAddEntry(es->table, buffer);
}

bool esGetTableEntry(EVIDENCE_SYSTEM* es, int indexEntry, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableGetEntry(es->table, indexEntry, buffer);
}

void esPrintTable(EVIDENCE_SYSTEM* es) {
    tablePrint(es->table);
}