#ifndef SERVER_EVIDENCE_SYSTEM_H
#define SERVER_EVIDENCE_SYSTEM_H

#include "table.h"
#include "../CMemLeak.h"

typedef struct evidence_system {
    TABLE* table;
} EVIDENCE_SYSTEM;

void esInit(EVIDENCE_SYSTEM* es);
bool esCreateTable(EVIDENCE_SYSTEM* es, int countColumns, char* buffer);
bool esRemoveTable(EVIDENCE_SYSTEM* es);
bool esGetColumnsType(EVIDENCE_SYSTEM* es, char* buffer);
bool esAddEntry(EVIDENCE_SYSTEM* es, char* buffer);
bool esGetTableEntry(EVIDENCE_SYSTEM* es, int indexEntry, char* buffer);
void esPrintTable(EVIDENCE_SYSTEM* es);
void esPrintTableString(EVIDENCE_SYSTEM* es);
void esSortTable(EVIDENCE_SYSTEM* es);

#endif //SERVER_EVIDENCE_SYSTEM_H
