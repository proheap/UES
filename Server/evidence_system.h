#ifndef SERVER_EVIDENCE_SYSTEM_H
#define SERVER_EVIDENCE_SYSTEM_H

#include "table.h"
#include "../CMemLeak.h"

typedef struct evidence_system {
    LINKED_LIST* tables;
    int countTables;
} EVIDENCE_SYSTEM;

bool addTable(EVIDENCE_SYSTEM* es, int countColumns);
bool removeTable(EVIDENCE_SYSTEM* es, int indexTable);
bool esAddEntry(EVIDENCE_SYSTEM* es, int indexTable);
bool esRemoveEntry(EVIDENCE_SYSTEM* es, int indexTable);
void esPrintTable(EVIDENCE_SYSTEM* es, int indexTable);
void esPrintTableString(EVIDENCE_SYSTEM* es, int indexTable);
void esSortTable(EVIDENCE_SYSTEM* es, int indexTable);

#endif //SERVER_EVIDENCE_SYSTEM_H
