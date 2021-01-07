#include "column.h"

void columnInit (COLUMN* column, enum type_tag type) {
    column->entry = (LINKED_LIST*) malloc(sizeof(LINKED_LIST));
    column->type = type;
}

void columnAddEntry(COLUMN* column, void* data) {
    llAdd(column->entry, data, column->type);
}

void columnGetEntry(COLUMN* column, int indexEntry, void* data) {
    llTryGet(column->entry, indexEntry, data);
}

void columnPrintData(COLUMN* column, int indexEntry) {
    void* data;
    llTryGet(column->entry, indexEntry, data);
    itemPrintData(data, column->type);
}