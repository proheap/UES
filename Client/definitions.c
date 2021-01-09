#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

void data_init(DATA* data, const char* userName, const int socket) {
	data->socket = socket;
	data->stop = 0;
	data->userName[USER_LENGTH] = '\0';
	strncpy(data->userName, userName, USER_LENGTH);
	pthread_mutex_init(&data->mutex, NULL);
}

void data_destroy(DATA* data) {
	pthread_mutex_destroy(&data->mutex);
}

void data_stop(DATA* data) {
    pthread_mutex_lock(&data->mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->mutex);
}

int data_isStopped(DATA* data) {
    int stop;
    pthread_mutex_lock(&data->mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->mutex);
    return stop;
}

static void data_answer(char* buffer) {
    switch (*buffer) {
        case '3':
            printColumnsTypeEntry(buffer);
            break;
        case '5':
            printTableHead(buffer);
            break;
        default:
            printTable(buffer, *buffer - '0');
    }
}

void* data_readData(void* data) {
    DATA* pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
	buffer[BUFFER_LENGTH] = '\0';

    while(!data_isStopped(pdata)) {
		bzero(buffer, BUFFER_LENGTH);
		if (read(pdata->socket, buffer, BUFFER_LENGTH) > 0) {
            data_answer(buffer);
		}
		else {
			data_stop(pdata);
		}
	}
	
	return NULL;
}

void* data_writeData(void* data) {
    DATA *pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';

    while(!data_isStopped(pdata)) {
        while (menu(buffer)) {
            if (*buffer != '\0') {
                write(pdata->socket, buffer, strlen(buffer) + 1);
                strncpy(buffer, "\0", BUFFER_LENGTH);
            }
        }
        write(pdata->socket, buffer, strlen(buffer) + 1);
        printf("Koniec komunikacie.\n");
        data_stop(pdata);
    }
	
	return NULL;
}

void printError(char* str) {
    if (errno != 0) {
		perror(str);
	}
	else {
		fprintf(stderr, "%s\n", str);
	}
    exit(EXIT_FAILURE);
}
