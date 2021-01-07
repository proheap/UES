#include <stdlib.h>

#include "menu.h"

bool reading = false;

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

static void menuRemoveTable(char* buffer) {
    printf("ODSTRANENIE TABULKY\n");
    printf("-------------------\n");
    printf("Naozaj chcete odstranit tabulku? (0 - NIE, 1 - ANO\n");
    int input;
    scanf("%d", &input);
    getchar();
    if (input == 1) {
        *buffer = '2';
        *(buffer + 1) = '\0';
    }
}

static void findColumnType(char* buffer, char* type) {
    switch (*(buffer + 1 + i)) {
        case '0':
            strcpy(type, "INT");
        case '1':
            strcpy(type, "DOUBLE");
        case '2':
            strcpy(type, "STRING");
        case '3':
            strcpy(type, "BOOLEAN");
    }
}

void printColumnsType(char* buffer) {
    int countColumns = *buffer - '0';
    char* type = "";
    char* input;
    for (int i = 0; i < countColumns; i++) {
        findColumnType(buffer, type);
        printf("Zadajte data pre %d. stlpec (typ %s):\n", i + 1, type);
        fgets(input, sizeof(input), stdin);
        char *pos = strchr(input, '\n');
        if (pos != NULL) {
            *pos = '\0';
        }
    }
    reading = false;
}

static void menuAddEntry() {
    printf("PRIDANIE ZAZNAMU DO TABULKY\n");
    printf("---------------------------\n");
    reading = true;
    while (!reading);

}

void printTable(char* buffer, bool lastEntry) {
    printf("%s\n", buffer);
    if (lastEntry) {
        reading = false;
    }
}

static void menuRemoveEntry() {
    printf("ODSTRANENIE ZAZNAMU Z TABULKY\n");
    printf("-----------------------------\n");
    reading = true;
    while (!reading);
    printf("Zadajte ID zaznamu tabulky, z ktorej chcete zaznam odstranit.\n");
    int input;
    scanf("%d", &input);
    getchar();
}

static void menuPrintTable() {
    printf("VYPISANIE ZAZNAMOV TABULKY\n");
    printf("--------------------------\n");
    reading = true;
    while (!reading);
    printf("--------------------------\n");
    printf("0. Spat\n");
    int input;
    do {
        scanf("%d", &input);
        getchar();
    } while (input != 0);
}

static void menuPrintTableString() {
    printf("VYPISANIE ZAZNAMOV TABULKY OBSAHUJUCE RETAZEC\n");
    printf("-----------------------------------------------\n");
    reading = true;
    while (!reading);
    printf("-----------------------------------------------\n");
    printf("0. Spat\n");
    int input;
    do {
        scanf("%d", &input);
        getchar();
    } while (input != 0);
}

static void menuSortTable() {
    printf("UTRIEDENIE TABULKY\n");
    printf("------------------\n");

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