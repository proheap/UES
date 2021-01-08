#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

void data_init(DATA *data, const char* userName, const int socket) {
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

static void data_answer(void* data, char* buffer, EVIDENCE_SYSTEM* es) {
    char bufferSending[BUFFER_LENGTH + 1];
    switch (*buffer) {
        case '1':
            esCreateTable(es, *(buffer + 1) - '0', buffer);
            break;
        case '2':
            esRemoveTable(es);
            break;
        case '3':
            if(*(buffer + 1) == '0') {
                esGetColumnsType(es, bufferSending);
                data_writeData(data, bufferSending);
            } else {
                esAddEntry(es, buffer);
            }
            break;
        case '4':
            break;
        case '5':
            for (int i = 0; i < es->table->countEntries; i++) {
                strcpy(buffer,"\0");
                esGetTableEntry(es, i, bufferSending);
                data_writeData(data, bufferSending);
            }
            esPrintTable(es);
            break;
        case '6':
            esGetStringTableEntry(es, buffer + 1, bufferSending);
            esPrintStringTable(es, buffer + 1);
            break;
        case '7':
            esSortTable(es, *(buffer + 1), *(buffer + 2));
            break;
    }
}

void* data_readData(void* data, EVIDENCE_SYSTEM* es) {
    DATA* pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
	buffer[BUFFER_LENGTH] = '\0';
    while(!data_isStopped(pdata)) {
		bzero(buffer, BUFFER_LENGTH);
		if (read(pdata->socket, buffer, BUFFER_LENGTH) > 0) {
		    printf("%s\n", buffer);
		    data_answer(data, buffer, es);
		}
		else {
			data_stop(pdata);
		}
	}
	
	return NULL;
}

void* data_writeData(void* data, char* buffer) {
    DATA* pdata = (DATA *)data;
    write(pdata->socket, buffer, strlen(buffer) + 1);

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
