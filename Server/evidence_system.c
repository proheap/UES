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
    *buffer = '3';
    return tableGetColumnsType(es->table, buffer);
}

bool esAddEntry(EVIDENCE_SYSTEM* es, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableAddEntry(es->table, buffer);
}

bool esGetTableEntry(const EVIDENCE_SYSTEM* es, const int indexEntry, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableGetEntry(es->table, indexEntry, buffer);
}

void esPrintTable(const EVIDENCE_SYSTEM* es) {
    tablePrint(es->table);
}

bool esGetStringTableEntry(const EVIDENCE_SYSTEM* es, const char* str, char* buffer) {
    if (es->table == NULL) {
        return false;
    }
    return tableGetStringEntry(es->table, str, buffer);
}

void esPrintStringTable(const EVIDENCE_SYSTEM* es, char* str) {
    tableStringPrint(es->table, str);
}

bool esSortTable(EVIDENCE_SYSTEM* es, const int indexColumn, const bool ascending) {
    return tableSort(es->table, indexColumn, ascending);
}