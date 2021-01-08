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
    int entryInt;
    double entryDouble;
    char* entryString;
    char* tmp;
    bool entryBool;
    switch (column->type) {
        case INT_TYPE:
            entryInt = atoi((char*)data);
            llAdd(column->entry, &entryInt, column->type);
            break;
        case DOUBLE_TYPE:
            entryDouble = strtod((char*)data, &tmp);
            llAdd(column->entry, &entryDouble, column->type);
            break;
        case STRING_TYPE:
            strncpy(entryString, (char*)data, DATA_SIZE);
            llAdd(column->entry, entryString, column->type);
            break;
        case BOOL_TYPE:
            if(*(char*)data == '0') {
                entryBool = false;
            } else {
                entryBool = true;
            }
            llAdd(column->entry, &entryBool, column->type);
            break;
    }
}

bool columnGetEntry(const COLUMN* column, const int indexEntry, void* data) {
    return llTryGet(column->entry, indexEntry, data);
}

void columnPrintData(const COLUMN* column, const int indexEntry) {
    void* data;
    llTryGet(column->entry, indexEntry, data);
    itemPrintData(data, column->type);
}

void columnPrintType(const COLUMN* column) {
    switch (column->type) {
        case INT_TYPE:
            printf("[INT] ");
            break;
        case DOUBLE_TYPE:
            printf("[DOUBLE] ");
            break;
        case STRING_TYPE:
            printf("[STRING] ");
            break;
        case BOOL_TYPE:
            printf("[BOOLEAN] ");
            break;
    }
}

bool columnSwapEntries(COLUMN* column, const int indexEntry1, const int indexEntry2) {
    return llTrySwap(column->entry, indexEntry1, indexEntry2);
}