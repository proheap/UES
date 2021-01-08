#include <stdlib.h>

#include "menu.h"

STATE_MENU stateMenu = START;
STATE_READING stateReading = BEFORE;
bool reading = false;

static void readStringInput(char* input) {
    fgets(input, INPUT_SIZE, stdin);
    char *pos = strchr(input, '\n');
    if (pos != NULL) {
        *pos = '\0';
    }
}

static int readIntegerInput() {
    int input;
    scanf("%d", &input);
    getchar();
    return input;
}

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

static void menuColumnType(char* buffer, const int countColumns) {
    int type;
    for (int i = 0; i < countColumns; i++) {
        printf("Zadajte typ pre %d. stlpec (0 - INT, 1 - DOUBLE, 2 - STRING, 3 - BOOLEAN):\n", i + 1);
        do {
            type = readIntegerInput();
        } while (type < 0 && type > 3);
        *(buffer + 2 + i) = type + '0';
    }
}

static void menuCreateTable(char* buffer) {
    *buffer = '1';
    printf("VYTVORENIE TABULKY\n");
    printf("------------------\n");
    printf("Zadajte pocet stlpcov:\n");
    int countColumns = readIntegerInput();
    *(buffer + 1) = countColumns + '0';

    menuColumnType(buffer, countColumns);
    *(buffer + countColumns + 2) = '\0';
}

static void menuRemoveTable(char* buffer) {
    int input;
    strncpy(buffer, "\0", strlen(buffer));
    printf("ODSTRANENIE TABULKY\n");
    printf("-------------------\n");
    printf("Naozaj chcete odstranit tabulku? (0 - NIE, 1 - ANO)\n");
    do {
        input = readIntegerInput();
    } while (input != 1 && input != 0);
    if (input == 1) {
        *buffer = '2';
        *(buffer + 1) = '\0';
    }
}

static void findColumnType(const char typeTag, char* strType) {
    switch (typeTag) {
        case '0':
            strncpy(strType, "INT", TYPE_SIZE);
            break;
        case '1':
            strncpy(strType, "DOUBLE", TYPE_SIZE);
            break;
        case '2':
            strncpy(strType, "STRING", TYPE_SIZE);
            break;
        case '3':
            strncpy(strType, "BOOLEAN", TYPE_SIZE);
            break;
    }
}

void printColumnsType(char* buffer) {
    int countColumns = *(buffer + 1) - '0';
    char bufferTypes[strlen(buffer)];
    strncpy(bufferTypes, buffer + 2, strlen(buffer));
    char type[TYPE_SIZE];

    printf("Zadajte zaznam v tvare: ");
    for (int i = 0; i < countColumns; i++) {
        findColumnType(*(bufferTypes + i), type);
        if (i != countColumns - 1) {
            printf("%s:", type);
        } else {
            printf("%s\n", type);
        }
    }
    stateReading = AFTER;
    reading = false;
}

static void menuAddEntry(char* buffer) {
    strncpy(buffer, "3", strlen(buffer));
    if (stateReading == BEFORE) {
        *(buffer + 1) = '0';
        *(buffer + 2) = '\0';
        printf("PRIDANIE ZAZNAMU DO TABULKY\n");
        printf("---------------------------\n");
        reading = true;
    } else {
        *(buffer + 1) = '1';
        *(buffer + 2) = ':';
        char entry[INPUT_SIZE];
        readStringInput(&entry);
        strcat(buffer, entry);
        stateReading = BEFORE;
        stateMenu = START;
    }
}

void printTable(char* buffer, const bool lastEntry) {
    printf("%s\n", buffer + 1);
    if (lastEntry) {
        reading = false;
        stateReading = AFTER;
    }
}

static void menuRemoveEntry(char* buffer) {
    *buffer = '4';
    if (stateReading == BEFORE) {
        *(buffer + 1) = '0';
        *(buffer + 2) = '\0';
        printf("ODSTRANENIE ZAZNAMU Z TABULKY\n");
        printf("-----------------------------\n");
        reading = true;
    } else {
        *(buffer + 1) = '1';
        printf("Zadajte ID zaznamu, Ktorý chcete z tabulky odstranit:\n");
        int indexEntry = readIntegerInput();
        *(buffer + 2) = indexEntry + '0';
        *(buffer + 3) = '\0';
        stateReading = BEFORE;
        stateMenu = START;
    }

}

static void menuPrintTable(char* buffer) {
    strncpy(buffer, "\0", strlen(buffer));
    if (stateReading == BEFORE) {
        *buffer = '5';
        printf("VYPISANIE ZAZNAMOV TABULKY\n");
        printf("--------------------------\n");
        reading = true;
    } else {
        int input;
        printf("--------------------------\n");
        printf("0. Spat\n");
        do {
            input = readIntegerInput();
        } while (input != 0);
        stateReading = BEFORE;
        stateMenu = START;
    }
}

static void menuPrintTableString(char* buffer) {
    *buffer = '\0';
    if (stateReading == BEFORE) {
        char input[INPUT_SIZE];
        *buffer = '6';
        printf("VYPISANIE ZAZNAMOV TABULKY OBSAHUJUCE RETAZEC\n");
        printf("---------------------------------------------\n");
        printf("Zadajte hladany retazec:\n");
        readStringInput(input);
        strcat(buffer, input);
        reading = true;
    } else {
        int input;
        printf("---------------------------------------------\n");
        printf("0. Spat\n");
        do {
            input = readIntegerInput();
        } while (input != 0);
        stateReading = BEFORE;
        stateMenu = START;
    }
}

static void menuSortTable(char* buffer) {
    *buffer = '6';
    if (stateReading == BEFORE) {
        char input[INPUT_SIZE];
        *(buffer + 1) = '0';
        *(buffer + 2) = '\0';
        printf("UTRIEDENIE TABULKY\n");
        printf("------------------\n");
    } else {
        *(buffer + 1) = '1';
        int indexColumn;
        int ascending;
        printf("------------------\n");
        printf("Zadajte cislo stlpca, podla ktoreho chcete zoradit tabulku:\n");
        indexColumn = readIntegerInput();
        printf("Zadajte sposob zoradenia tabulky (0 - ZOSTUPNE, 1 - VZOSTUPNE):\n");
        do {
            ascending = readIntegerInput();
        } while (ascending != 1 && ascending != 0);

        *(buffer + 2) = indexColumn + '0';
        *(buffer + 3) = ascending + '1';
        *(buffer + 4) = '\0';
        stateReading = BEFORE;
        stateMenu = START;
    }
}

int menu(char* buffer) {
    char input[INPUT_SIZE];

    if(reading == false) {
        printMenu();
        readStringInput(input);

        if (strncmp(input, "1", INPUT_SIZE) == 0) {
            stateMenu = CREATE_TABLE;
        } else if (strncmp(input, "2", INPUT_SIZE) == 0) {
            stateMenu = REMOVE_TABLE;
        } else if (strncmp(input, "3", INPUT_SIZE) == 0) {
            stateMenu = ADD_ENTRY;
        } else if (strncmp(input, "4", INPUT_SIZE) == 0) {
            stateMenu = REMOVE_ENTRY;
        } else if (strncmp(input, "5", INPUT_SIZE) == 0) {
            stateMenu = PRINT_TABLE;
        } else if (strncmp(input, "6", INPUT_SIZE) == 0) {
            stateMenu = PRINT_TABLE_STRING;
        } else if (strncmp(input, "7", INPUT_SIZE) == 0) {
            stateMenu = SORT_TABLE;
        } else if (strncmp(input, "0", INPUT_SIZE) == 0) {
            return 0;
        }
    }

    while (reading);

    switch (stateMenu) {
        case CREATE_TABLE:
            menuCreateTable(buffer);
            stateMenu = START;
            break;
        case REMOVE_TABLE:
            menuRemoveTable(buffer);
            stateMenu = START;
            break;
        case ADD_ENTRY:
            menuAddEntry(buffer);
            break;
        case REMOVE_ENTRY:
            menuRemoveEntry(buffer);
            break;
        case PRINT_TABLE:
            menuPrintTable(buffer);
            break;
        case PRINT_TABLE_STRING:
            menuPrintTableString(buffer);
            break;
        case SORT_TABLE:
            menuSortTable(buffer);
            break;
    }
    return 1;
}