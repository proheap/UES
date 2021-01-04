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

static void menuCreateTable() {
    printf("VYTVORENIE TABULKY\n");
    printf("------------------\n");
    int countColumns;
    printf("Zadajte pocet stlpcov:\n");
    scanf("%d", &countColumns);

    for (int i = 0; i < countColumns; i++) {

    }
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

int menu() {
    char input[INPUT_SIZE];
    STATE_MENU state = START;

    int balance = 0;
    while(fgets(input, sizeof(input), stdin)) {
        switch (state) {
            case START:
                printMenu();
                if (strncmp(input, "1\n", INPUT_SIZE) == 0) {
                    state = CREATE_TABLE;
                } else if (strncmp(input, "2\n", INPUT_SIZE) == 0) {
                    state = REMOVE_TABLE;
                } else if (strncmp(input, "3\n", INPUT_SIZE) == 0) {
                    state = ADD_ENTRY;
                } else if (strncmp(input, "4\n", INPUT_SIZE) == 0) {
                    state = REMOVE_ENTRY;
                } else if (strncmp(input, "5\n", INPUT_SIZE) == 0) {
                    state = PRINT_TABLE;
                } else if (strncmp(input, "6\n", INPUT_SIZE) == 0) {
                    state = PRINT_TABLE_STRING;
                } else if (strncmp(input, "7\n", INPUT_SIZE) == 0) {
                    state = SORT_TABLE;
                } else if (strncmp(input, "0\n", INPUT_SIZE) == 0) {
                    return EXIT_SUCCESS;
                }
                break;
            case CREATE_TABLE:
                menuCreateTable();
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
    }
}