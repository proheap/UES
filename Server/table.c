#include "table.h"

void tableInit(TABLE* table, int countColumns) {
    table->countColumns = countColumns;
    table->columns = (COLUMN**) malloc(countColumns * sizeof(COLUMN*));
    table->countEntries = 0;
}

void tableDispose(TABLE* table) {
    for (int i = 0; i < table->countColumns; i++) {
        columnDispose(table->columns[i]);
        free(table->columns[i]);
        table->columns[i] = NULL;
    }
    free(table->columns);
    table->columns = NULL;
    table->countColumns = 0;
    table->countEntries = 0;
}

void tableAddColumns(TABLE* table, char* buffer) {
    for (int i = 0; i < table->countColumns; i++) {
        COLUMN* column;
        column = (COLUMN*) malloc(sizeof(COLUMN));
        columnInit(column, *(buffer + 2 + i) - '0');
        table->columns[i] = column;
    }
}

bool tableGetColumnsType(const TABLE* table, char* buffer) {
    if (table->countColumns == 0) {
        return false;
    }
    *(buffer + 1) = table->countColumns + '0';
    for (int i = 0; i < table->countColumns; i++) {
        *(buffer + 2 + i) = table->columns[i]->type + '0';
    }
    return true;
}

bool tableAddEntry(TABLE* table, char* buffer) {
    char* p1 = strchr(buffer, ':');
    p1++;
    for (int c = 0; c < table->countColumns; c++) {
        char data[DATA_SIZE] = "\0";
        if (c != table->countColumns - 1) {
            char *p2 = strchr(p1, ':');
            strncpy(data, p1, p2 - p1);
            columnAddEntry(table->columns[c], data);
            p1 = p2 + 1;
        } else {
            strncpy(data, p1, strlen(p1));
            columnAddEntry(table->columns[c], data);
        }
    }
    table->countEntries++;
    return true;
}

bool tableGetEntry(const TABLE* table, const int indexEntry, char* buffer) {
    if (indexEntry < 0 || indexEntry >= table->countEntries) {
        return false;
    }

    void* data;
    for (int c = 0; c < table->countColumns; c++) {
        columnGetEntry(table->columns[c], indexEntry, data);
//        if (!columnGetEntry(table->columns[c], indexEntry, data)) {
//            return false;
//        }
        strcat(buffer, (char*)data);
        if(c != table->countColumns - 1) {
            strcat(buffer, ":");
        } else {
            strcat(buffer, "\n");
        }
    }
    return true;
}

void tablePrint(const TABLE* table) {
    printf("Zaznamy tabulky:\n");
    printf("----------------\n");
    for (int c = 0; c < table->countColumns; c++) {
        columnPrintType(table->columns[c]);
    }
    printf("\n");
    for (int i = 0; i < table->countEntries; i++) {
        for (int c = 0; c < table->countColumns; c++) {
            columnPrintData(table->columns[c], i);
        }
        printf("\n");
    }
}

bool tableGetStringEntry (const TABLE* table, const char* str, char* buffer) {
    if (strcmp(str, "") == 0) {
        return false;
    }
    void* data;
    for (int i = 0; i < table->countColumns; i++) {
        if(table->columns[i]->type == STRING_TYPE) {
            for (int j = 0; j < table->countEntries; j++) {
                columnGetEntry(table->columns[i], j, data);
                if (itemCompareData(data, str, STRING_TYPE) == 0) {
                    for (int c = 0; c < table->countColumns; c++) {
                        strcat(buffer, (char*)data);
                        if(c != table->countColumns - 1) {
                            strcat(buffer, ":");
                        } else {
                            strcat(buffer, "\n");
                        }
                    }
                }
            }
        }
    }
    return true;
}

void tableStringPrint(const TABLE* table, char* str) {
    void* data;
    printf("Tabulka obsahujúca retazec %s:\n", str);
    printf("------------------------------------------\n");
    for (int i = 0; i < table->countColumns; i++) {
        if(table->columns[i]->type == STRING_TYPE) {
            for (int j = 0; j < table->countEntries; j++) {
                columnGetEntry(table->columns[i], j, data);
                if (itemCompareData(data, str, STRING_TYPE) == 0) {
                    for (int c = 0; c < table->countColumns; c++) {
                        columnPrintData(table->columns[c], j);
                    }
                }
            }
        }
    }
}

bool tableSort(TABLE* table, const int indexColumn, const bool ascending) {
    if (indexColumn < 0 || indexColumn >= table->countColumns) {
        return false;
    }

    COLUMN* sortingColumn = table->columns[indexColumn];
    for (int i = 0; i < table->countEntries; i++) {
        for (int j = i; j < table->countEntries; j++) {
            void *data1, *data2;
            llTryGet(sortingColumn->entry, i, data1);
            llTryGet(sortingColumn->entry, j, data2);
            if(ascending) {
                if (itemCompareData(data1, data2, sortingColumn->type) > 0) {
                    for (int c = 0; c < table->countColumns; c++) {
                        columnSwapEntries(table->columns[c], i, j);
                    }
                }
            } else {
                if (itemCompareData(data1, data2, sortingColumn->type) < 0) {
                    for (int c = 0; c < table->countColumns; c++) {
                        columnSwapEntries(table->columns[c], j, i);
                    }
                }
            }
        }
    }
    return true;
}