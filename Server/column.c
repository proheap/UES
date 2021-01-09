#include "column.h"

void columnInit (COLUMN* column, const enum type_tag type) {
    column->entry = (LINKED_LIST*) malloc(sizeof(LINKED_LIST));
    llInit(column->entry);
    column->type = type;
}

void columnDispose(COLUMN* column) {
    llDispose(column->entry);
    free(column->entry);
    column->entry = NULL;
    column->type = 0;
}

void columnAddEntry(COLUMN* column, const void* data) {
    int dataInt;
    double dataDouble;
    int dataStringSize = strlen((char*)data) + 1;
    char dataString[dataStringSize];
    bool dataBool;
    switch (column->type) {
        case INT_TYPE:
            dataInt = atoi((char*)data);
            llAdd(column->entry, &dataInt, column->type);
            break;
        case DOUBLE_TYPE:
            dataDouble = strtod((char*)data, NULL);
            llAdd(column->entry, &dataDouble, column->type);
            break;
        case STRING_TYPE:
            strncpy(dataString, (char*)data, dataStringSize);
            llAdd(column->entry, dataString, column->type);
            break;
        case BOOL_TYPE:
            if(*(char*)data == '0') {
                dataBool = false;
            } else {
                dataBool = true;
            }
            llAdd(column->entry, &dataBool, column->type);
            break;
    }
}

bool columnRemoveEntry(COLUMN* column, const int indexEntry) {
    return llTryRemove(column->entry, indexEntry);
}

bool columnGetEntry(const COLUMN* column, const int indexEntry, void** data) {
    return llTryGet(column->entry, indexEntry, data);
}

static void itoa(char* str, int num) {
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void columnGetDataString(const COLUMN* column, const void* data, char* strData) {
    int* dataInt;
    double* dataDouble;
    char* dataString;
    bool* dataBool;
    switch (column->type) {
        case INT_TYPE:
            dataInt = (int*)data;
            itoa(strData, *dataInt);
            break;
        case DOUBLE_TYPE:
            dataDouble = (double*)data;
            sprintf(strData, "%.2lf", *dataDouble);
            break;
        case STRING_TYPE:
            dataString = (char*)data;
            strncpy(strData, dataString, strlen(dataString));
            break;
        case BOOL_TYPE:
            dataBool = (bool*)data;
            *strData = *dataBool + '0';
            break;
    }
}

bool columnSwapEntries(COLUMN* column, const int indexEntry1, const int indexEntry2) {
    return llTrySwap(column->entry, indexEntry1, indexEntry2);
}