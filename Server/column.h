#ifndef SERVER_COLUMN_H
#define SERVER_COLUMN_H

#include "./structures/linked_list.h"
#include "../CMemLeak.h"

typedef struct column {
    enum type_tag type;
    LINKED_LIST* entry;
} COLUMN;

void columnInit(COLUMN* column, enum type_tag tag);

#endif //SERVER_COLUMN_H
