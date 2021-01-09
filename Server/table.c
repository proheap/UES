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

bool tableRemoveEntry(TABLE* table, int indexEntry) {
    if (indexEntry < 0 || indexEntry >= table->countEntries) {
        return false;
    }
    for (int c = 0; c < table->countColumns; c++) {
        if (!columnRemoveEntry(table->columns[c], indexEntry)) {
            return false;
        }
    }
    table->countEntries--;
    return true;
}

bool tableGetEntry(const TABLE* table, const int indexEntry, char* buffer) {
    if (indexEntry < 0 || indexEntry >= table->countEntries) {
        return false;
    }

    *(buffer + 1) = '[';
    *(buffer + 2) = indexEntry + '0';
    *(buffer + 3) = ']';
    for (int c = 0; c < table->countColumns; c++) {
        void* data;
        if (!columnGetEntry(table->columns[c], indexEntry, &data)) {
            return false;
        }
        char strData[DATA_SIZE] = "";
        columnGetDataString(table->columns[c], data, strData);
        strncpy(buffer + strlen(buffer), strData, strlen(strData));
        if(c != table->countColumns - 1) {
            strcat(buffer, ":");
        }
        free(data);
    }
    return true;
}

bool tableGetStringEntry (const TABLE* table, const char* str, char* buffer) {
    if (strcmp(str, "") == 0) {
        return false;
    }
    for (int i = 0; i < table->countColumns; i++) {
        if(table->columns[i]->type == STRING_TYPE) {
            for (int j = 0; j < table->countEntries; j++) {
                void* data;
                columnGetEntry(table->columns[i], j, &data);
                if (itemCompareData(data, str, STRING_TYPE) == 0) {
                    *(buffer + strlen(buffer)) = '[';
                    *(buffer + strlen(buffer)) = j + '0';
                    *(buffer + strlen(buffer)) = ']';
                    free(data);
                    for (int c = 0; c < table->countColumns; c++) {
                        char strData[STRING_SIZE] = "";
                        columnGetEntry(table->columns[c], j, &data);
                        columnGetDataString(table->columns[c], data, strData);
                        strncat(buffer, strData, strlen((char*)strData));
                        if(c != table->countColumns - 1) {
                            strcat(buffer, ":");
                        } else {
                            strcat(buffer, "\n");
                        }
                        free(data);
                    }
                }
            }
        }
    }
    *(buffer + strlen(buffer) - 1) = '\0';
    return true;
}

bool tableSort(TABLE* table, const int indexColumn, const bool ascending) {
    if (indexColumn < 0 || indexColumn >= table->countColumns) {
        return false;
    }

    COLUMN* sortingColumn = table->columns[indexColumn];
    for (int i = 0; i < table->countEntries - 1; i++) {
        for (int j = i + 1; j < table->countEntries; j++) {
            void *data1;
            columnGetEntry(sortingColumn, i, &data1);
            void *data2;
            columnGetEntry(sortingColumn, j, &data2);
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
            free(data1);
            free(data2);
        }
    }
    return true;
}