#include "item.h"

void itemAddData(ITEM *item, void *data) {
    size_t dataSize;
    switch (item->type) {
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
        case STRUCT_TYPE:
            dataSize = sizeof(void *);
            break;
    }
    item->data = calloc(1 , dataSize);

    memcpy(item->data, data, dataSize);
}

void itemCopy(const ITEM *src, ITEM *dest, const enum type_tag type) {
    dest->type = type;
    size_t dataSize;
    switch (type) {
        case INT_TYPE:
            dataSize = sizeof(int);
            break;
        case DOUBLE_TYPE:
            dataSize = sizeof(double);
            break;
        case STRING_TYPE:
            dataSize = strlen((char*) src->data) * sizeof(char);
            break;
        case BOOL_TYPE:
            dataSize = sizeof(_Bool);
            break;
        case STRUCT_TYPE:
            dataSize = sizeof(void *);
            break;
    }
    dest->data = calloc(1 , dataSize);

    memcpy(dest->data, src->data, dataSize);
}

void itemSetData(ITEM* item, const void *data, const enum type_tag type) {
    item->type = type;
    size_t dataSize;
    switch (type) {
        case INT_TYPE:
            dataSize = sizeof(int);
            break;
        case DOUBLE_TYPE:
            dataSize = sizeof(double);
            break;
        case STRING_TYPE:
            dataSize = strlen((char*) data) * sizeof(char);
            break;
        case BOOL_TYPE:
            dataSize = sizeof(_Bool);
            break;
        case STRUCT_TYPE:
            dataSize = sizeof(void *);
            break;
    }
    item->data = realloc(item->data, dataSize);

    memcpy(item->data, data, dataSize);
}

void* itemGetData(const ITEM *item, void *data) {
    size_t dataSize;
    switch (item->type) {
        case INT_TYPE:
            dataSize = sizeof(int);
            break;
        case DOUBLE_TYPE:
            dataSize = sizeof(double);
            break;
        case STRING_TYPE:
            dataSize = strlen((char*) item->data) * sizeof(char);
            break;
        case BOOL_TYPE:
            dataSize = sizeof(_Bool);
            break;
        case STRUCT_TYPE:
            dataSize = sizeof(void *);
            break;
    }
    data = calloc(1 , dataSize);

    memcpy(data, item->data, dataSize);
    return data;
}

void itemDeleteData(ITEM *item) {
    free(item->data);
}

void itemPrint(const ITEM *item) {
    switch (item->type) {
        case INT_TYPE:
            printf("[%d] ", *((int*)item->data));
            break;
        case DOUBLE_TYPE:
            printf("[%lfs] ", *((double*)item->data));
            break;
        case STRING_TYPE:
            printf("[%s] ", (char*)item->data);
            break;
        case BOOL_TYPE:
            printf("[%s] ", *((_Bool*)item->data) ? "true" : "false");
            break;
        case STRUCT_TYPE:
            printf("[STRUCT]");
            break;
    }
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
        case STRUCT_TYPE:
            break;
    }
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
        case STRUCT_TYPE:
            break;
    }
}
