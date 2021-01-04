#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

char *endMsg = ":end";

void data_init(DATA *data, const char* userName, const int socket) {
	data->socket = socket;
	data->stop = 0;
	data->userName[USER_LENGTH] = '\0';
	strncpy(data->userName, userName, USER_LENGTH);
	pthread_mutex_init(&data->mutex, NULL);
}

void data_destroy(DATA *data) {
	pthread_mutex_destroy(&data->mutex);
}

void data_stop(DATA *data) {
    pthread_mutex_lock(&data->mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->mutex);
}

int data_isStopped(DATA *data) {
    int stop;
    pthread_mutex_lock(&data->mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->mutex);
    return stop;
}

void *data_readData(void *data) {    
    DATA *pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
	buffer[BUFFER_LENGTH] = '\0';
    while(!data_isStopped(pdata)) {
		bzero(buffer, BUFFER_LENGTH);
		if (read(pdata->socket, buffer, BUFFER_LENGTH) > 0) {
			char *posSemi = strchr(buffer, ':');
			char *pos = strstr(posSemi + 1, endMsg);
			if (pos != NULL && pos - posSemi == 2 && *(pos + strlen(endMsg)) == '\0') {
				*(pos - 2) = '\0';
				printf("Pouzivatel %s ukoncil komunikaciu.\n", buffer);
				data_stop(pdata);
			}
			else {
				printf("%s\n", buffer);
			}			
		}
		else {
			data_stop(pdata);
		}
	}
	
	return NULL;
}

void *data_writeData(void *data) {
    DATA *pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
    buffer[0] = '\0';
    int userNameLength = strlen(pdata->userName);

    //pre pripad, ze chceme poslat viac dat, ako je kapacita buffra
    while(!data_isStopped(pdata)) {
        while (menu(buffer) == 1) {
            write(pdata->socket, buffer, strlen(buffer) + 1);
        }
        data_stop(pdata);
    }
	
	return NULL;
}

void printError(char *str) {
    if (errno != 0) {
		perror(str);
	}
	else {
		fprintf(stderr, "%s\n", str);
	}
    exit(EXIT_FAILURE);
}
