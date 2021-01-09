#include "item.h"

size_t getDataTypeSize(const enum type_tag type,  const void* data) {
    size_t dataSize;
    switch (type) {
        case INT_TYPE:
            dataSize = sizeof(int);
            break;
        case DOUBLE_TYPE:
            dataSize = sizeof(double);
            break;
        case STRING_TYPE:
            dataSize = strlen((char*)data) * sizeof(char);
            break;
        case BOOL_TYPE:
            dataSize = sizeof(_Bool);
            break;
    }
    return dataSize;
}

void itemAddData(ITEM *item, const void *data) {
    size_t dataSize = getDataTypeSize(item->type, data);
    item->data = (void*)malloc(dataSize);

    memcpy(item->data, data, dataSize);
}

void itemCopy(ITEM *dest, const ITEM *src, const enum type_tag type) {
    dest->type = type;
    size_t dataSize = getDataTypeSize(type, src->data);
    dest->data = malloc(dataSize);

    memcpy(dest->data, src->data, dataSize);
}

void itemSetData(ITEM* item, const void *data, const enum type_tag type) {
    item->type = type;
    size_t dataSize = getDataTypeSize(type, data);
    item->data = realloc(item->data, dataSize);

    memcpy(item->data, data, dataSize);
}

void* itemGetData(const ITEM *item, void** data) {
    size_t dataSize = getDataTypeSize(item->type, item->data);
    *data = (void*)malloc(dataSize);

    memcpy(*data, item->data, dataSize);
    return *data;
}

int itemCompareData(const void *data1, const void *data2, const enum type_tag type){
    switch (type) {
        case INT_TYPE:
            if (*((int*)data1) > *((int*)data2)) {
                return 1;
            } else if (*((int*)data1) < *((int*)data2)) {
                return -1;
            } else {
                return 0;
            }
        case DOUBLE_TYPE:
            if (*((double*)data1) > *((double*)data2)) {
                return 1;
            } else if (*((double*)data1) < *((double*)data2)) {
                return -1;
            } else {
                return 0;
            }
        case STRING_TYPE:
            return memcmp(data1, data2, strlen((char*)data1));
        case BOOL_TYPE:
            if (*((_Bool*)data1) > *((_Bool*)data2)) {
                return 1;
            } else if (*((_Bool*)data1) < *((_Bool*)data2)) {
                return -1;
            } else {
                return 0;
            }
    }
}

int itemCompare(const ITEM *item1, const ITEM *item2) {
    if (item1->type != item2->type) {
        fprintf(stderr, "Comparing items are not same types!\n");
        exit(EXIT_FAILURE);
    }
    return itemCompareData(item1->data, item2->data, item1->type);
}

void itemDeleteData(ITEM *item) {
    free(item->data);
    item->data = NULL;
}

void itemPrintData(const void *data, const enum type_tag type) {
    switch (type) {
        case INT_TYPE:
            printf("[%d] ", *((int*)data));
            break;
        case DOUBLE_TYPE:
            printf("[%lf] ", *((double*)data));
            break;
        case STRING_TYPE:
            printf("[%s] ", (char*)data);
            break;
        case BOOL_TYPE:
            printf("[%s] ", *((_Bool*)data) ? "true" : "false");
            break;
    }
}

void itemPrint(const ITEM *item) {
    itemPrintData(item->data, item->type);
}

void itemFilePrint(const ITEM *item, FILE *txtFile) {
    switch (item->type) {
        case INT_TYPE:
            fprintf(txtFile, "%d:%d\n", item->type, *(int*)item->data);
            break;
        case DOUBLE_TYPE:
            fprintf(txtFile, "%d:%lf\n", item->type, *((double*)item->data));
            break;
        case STRING_TYPE:
            fprintf(txtFile, "%d:%s\n", item->type, (char*)item->data);
            break;
        case BOOL_TYPE:
            fprintf(txtFile, "%d:%d\n", item->type, *((_Bool*)item->data));
            break;
    }
}
