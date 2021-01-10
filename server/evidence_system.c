#include "evidence_system.h"

void esInit(EVIDENCE_SYSTEM* es) {
    es->table = NULL;
}

bool esCreateTable(EVIDENCE_SYSTEM* es, const int countColumns, char* buffer) {
    if (es->table != NULL) {
        return false;
    }
    TABLE* table = (TABLE*) malloc(sizeof(TABLE));
    tableInit(table, countColumns);
    tableAddColumns(table, buffer);
    es->table = table;
    return true;
}

bool esRemoveTable(EVIDENCE_SYSTEM* es) {
    if (es->table == NULL) {
        return false;
    }
    tableDispose(es->table);
    free(es->table);
    es->table = NULL;
    return true;
}

bool esGetColumnsType(const EVIDENCE_SYSTEM* es, char* buffer) {
    if (es->table == NULL) {
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

bool esRemoveEntry(EVIDENCE_SYSTEM* es, const int indexEntry) {
    if (es->table == NULL) {
        return false;
    }
    return tableRemoveEntry(es->table, indexEntry);
}

bool esGetTableEntry(const EVIDENCE_SYSTEM* es, const int indexEntry, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableGetEntry(es->table, indexEntry, buffer);
}

bool esGetStringTableEntry(const EVIDENCE_SYSTEM* es, const char* str, char* buffer) {
    if (es->table == NULL) {
        return false;
    }

    return tableGetStringEntry(es->table, str, buffer);
}

bool esSortTable(EVIDENCE_SYSTEM* es, const int indexColumn, const bool ascending) {
    if (es->table == NULL) {
        return false;
    }
    return tableSort(es->table, indexColumn, ascending);
}
