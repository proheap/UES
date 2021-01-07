#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "state.h"

#define INPUT_SIZE 10

extern bool reading;

void printColumnsType(char* buffer)
void printTable(char* buffer, bool lastEntry);

int menu(char* buffer);

#endif //CLIENT_MENU_H
