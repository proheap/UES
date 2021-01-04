#ifndef CLIENT_STATE_H
#define CLIENT_STATE_H

#include <stdio.h>

typedef enum stateMenu {
    START,
    CREATE_TABLE,
    REMOVE_TABLE,
    ADD_ENTRY,
    REMOVE_ENTRY,
    PRINT_TABLE,
    PRINT_TABLE_STRING,
    SORT_TABLE
} STATE_MENU;

#endif //CLIENT_STATE_H
