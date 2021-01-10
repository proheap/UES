#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "state.h"

#define BUFFER_LENGTH 100
#define INPUT_SIZE 50
#define TYPE_SIZE 10

extern STATE_MENU stateMenu;
extern STATE_READING stateReading;
extern bool reading;

void printBuffer(char* buffer);
void printColumnsTypeEntry(char* buffer);
void printTableHead(char* buffer);
void printTable(char* buffer, bool lastEntry);

int menu(char* buffer);

#endif //CLIENT_MENU_H
