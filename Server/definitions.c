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
    char findString[DATA_SIZE];
    switch (*buffer) {
        case '1':
            esCreateTable(es, *(buffer + 1) - '0', buffer);
            break;
        case '2':
            esRemoveTable(es);
            break;
        case '3':
            if(*(buffer + 1) == '0') {
                if (es->table == NULL) {
                    strncpy(buffer,"Tabulka nie je vytvorena!", BUFFER_LENGTH);
                } else {
                    *buffer = '3';
                    esGetColumnsType(es, buffer);
                }
                data_writeData(data, buffer);
            } else {
                esAddEntry(es, buffer);
            }
            break;
        case '4':
            if (*(buffer + 1) == '1') {
                int indexEntry = *(buffer + 2) - '0';
                esRemoveEntry(es, indexEntry);
                break;
            }
        case '7':
            if (*(buffer + 1) == '1') {
                esSortTable(es, *(buffer + 2) - '0', *(buffer + 3) - '0');
                break;
            }
        case '5':
            *buffer = '5';
            if (es->table == NULL) {
                strncpy(buffer,"Tabulka nie je vytvorena!", BUFFER_LENGTH);
                data_writeData(data, buffer);
            } else if (es->table->countEntries == 0) {
                strncpy(buffer,"Tabulka je prazdna!", BUFFER_LENGTH);
                data_writeData(data, buffer);
            } else {
                esGetColumnsType(es, buffer);
                data_writeData(data, buffer);
                for (int i = 0; i < es->table->countEntries; i++) {
                    if (i != es->table->countEntries - 1) {
                        strncpy(buffer,"0", BUFFER_LENGTH);
                    } else {
                        strncpy(buffer,"1", BUFFER_LENGTH);
                    }
                    esGetTableEntry(es, i, buffer);
                    data_writeData(data, buffer);
                    sleep(0.2);
                }
            }
            break;
        case '6':
            strncpy(findString, buffer + 2, DATA_SIZE);
            strncpy(buffer, "61:", strlen(buffer));
            esGetStringTableEntry(es, findString, buffer);
            data_writeData(data, buffer);
            break;
        case '0':
            printf("Pouzivatel ukoncil komunikaciu.\n");
            esRemoveTable(es);
            data_stop(data);
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
		    printf("RECIEVED: %s\n", buffer);
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
    printf("SENDED: %s\n", buffer);
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
