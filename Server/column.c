#include "column.h"

void columnInit (COLUMN* column, const enum type_tag type) {
    column->entry = (LINKED_LIST*) malloc(sizeof(LINKED_LIST));
    column->type = type;
}

void columnDispose(COLUMN* column) {
    llDispose(column->entry);
    column->entry = NULL;
    column->type = 0;
}

void columnAddEntry(COLUMN* column, void* data) {
    llAdd(column->entry, data, column->type);
}

bool columnGetEntry(const COLUMN* column, const int indexEntry, void* data) {
    return llTryGet(column->entry, indexEntry, data);
}

void columnPrintData(const COLUMN* column, const int indexEntry) {
    void* data;
    llTryGet(column->entry, indexEntry, data);
    itemPrintData(data, column->type);
}

bool columnSwapEntries(COLUMN* column, const int indexEntry1, const int indexEntry2) {
    return llTrySwap(column->entry, indexEntry1, indexEntry2);
}