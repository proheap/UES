#include <stdlib.h>

#include "menu.h"

static void printMenu() {
    printf("UNIVERZALNY EVIDENCNY SYSTEM\n");
    printf("----------------------------\n");
    printf("1. Vytvorit tabulku\n");
    printf("2. Zrusit tabulku\n");
    printf("3. Pridat zaznam do tabulky\n");
    printf("4. Odstranit zaznam z tabulky\n");
    printf("5. Vypisat zaznamy tabulky\n");
    printf("6. Vypisat zaznamy tabulky obsahujuce retazec\n");
    printf("7. Utriedit tabulku podla stlpca\n");
    printf("0. Exit\n");
}

static void menuColumnType(char* buffer, int countColumns) {
    printf("");
    for (int i = 0; i < countColumns; i++) {
        int type;
        printf("Zadajte typ pre %d. stlpec (0 - INT, 1 - DOUBLE, 2 - STRING, 3 - BOOLEAN):\n", i + 1);
        do {
            scanf("%d", &type);
            getchar();
        } while (type < 0 && type > 3);
        *(buffer + 2 + i) = type + '0';
    }
}

static void menuCreateTable(char* buffer) {
    *buffer = '1';
    printf("VYTVORENIE TABULKY\n");
    printf("------------------\n");
    int countColumns;
    printf("Zadajte pocet stlpcov:\n");
    scanf("%d", &countColumns);
    getchar();
    *(buffer + 1) = countColumns + '0';

    menuColumnType(buffer, countColumns);
    *(buffer + countColumns + 2) = '\0';
}

static void menuRemoveTable() {
    printf("ODSTRANENIE TABULKY\n");
    printf("-------------------\n");

    printf("Zadajte, ktoru tabulku chcete odstranit.\n");

}

static void menuAddEntry() {
    printf("PRIDANIE ZAZNAMU DO TABULKY\n");
    printf("---------------------------\n");

    printf("Zadajte, do ktorej tabulky chcete pridat zaznam.\n");

}

static void menuRemoveEntry() {
    printf("ODSTRANENIE ZAZNAMU Z TABULKY\n");
    printf("-----------------------------\n");

    printf("Zadajte, z ktorej tabulky chcete odstranit zaznam.\n");

}

static void menuPrintTable() {
    printf("VYPISANIE ZAZNAMOV TABULKY\n");
    printf("--------------------------\n");

    printf("Zadajte, ktoru tabulku chcete vypisat.\n");


}

static void menuPrintTableString() {
    printf("VYPISANIE ZAZNAMOV TABULKY OBSAHUJUCE RETAZEC\n");
    printf("---------------------------------------------\n");

    printf("Zadajte, ktoru tabulku chcete vypisat.\n");


}

int menu(char* buffer) {
    char input[INPUT_SIZE];
    STATE_MENU state;

    printMenu();
    fgets(input, sizeof(input), stdin);
    char *pos = strchr(input, '\n');
    if (pos != NULL) {
        *pos = '\0';
    }

    if (strncmp(input, "1", INPUT_SIZE) == 0) {
        state = CREATE_TABLE;
    } else if (strncmp(input, "2", INPUT_SIZE) == 0) {
        state = REMOVE_TABLE;
    } else if (strncmp(input, "3", INPUT_SIZE) == 0) {
        state = ADD_ENTRY;
    } else if (strncmp(input, "4", INPUT_SIZE) == 0) {
        state = REMOVE_ENTRY;
    } else if (strncmp(input, "5", INPUT_SIZE) == 0) {
        state = PRINT_TABLE;
    } else if (strncmp(input, "6", INPUT_SIZE) == 0) {
        state = PRINT_TABLE_STRING;
    } else if (strncmp(input, "7", INPUT_SIZE) == 0) {
        state = SORT_TABLE;
    } else if (strncmp(input, "0", INPUT_SIZE) == 0) {
        return 0;
    }
    switch (state) {
        case CREATE_TABLE:
            menuCreateTable(buffer);
            state = START;
            break;
        case REMOVE_TABLE:
            menuRemoveTable();
            state = START;
            break;
        case ADD_ENTRY:
            menuAddEntry();
            state = START;
            break;
        case REMOVE_ENTRY:
            menuRemoveEntry();
            state = START;
            break;
        case PRINT_TABLE:
            menuPrintTable();
            state = START;
            break;
        case PRINT_TABLE_STRING:
            menuPrintTable();
            state = START;
            break;
    }
    return 1;
}