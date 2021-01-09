#ifndef SERVER_EVIDENCE_SYSTEM_H
#define SERVER_EVIDENCE_SYSTEM_H

#include "table.h"

typedef struct evidence_system {
    TABLE* table;
} EVIDENCE_SYSTEM;

void esInit(EVIDENCE_SYSTEM* es);
bool esCreateTable(EVIDENCE_SYSTEM* es, const int countColumns, char* buffer);
bool esRemoveTable(EVIDENCE_SYSTEM* es);
bool esGetColumnsType(const EVIDENCE_SYSTEM* es, char* buffer);
bool esAddEntry(EVIDENCE_SYSTEM* es, char* buffer);
bool esRemoveEntry(EVIDENCE_SYSTEM* es, const int indexEntry);
bool esGetTableEntry(const EVIDENCE_SYSTEM* es, const int indexEntry, char* buffer);
bool esGetStringTableEntry(const EVIDENCE_SYSTEM* es, const char* str, char* buffer);
bool esSortTable(EVIDENCE_SYSTEM* es, const int indexColumn, const bool ascending);

#endif //SERVER_EVIDENCE_SYSTEM_H
