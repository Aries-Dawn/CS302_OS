#include "init.h"

void *reader(int *buffer){
    // Reader should read the value of buffer
    // Reader cannot start to work when there is any writer working
    // You should implement this using semaphore

    // You should output this just after this thread gets semaphore
    sem_wait(&rc);
    printf("Reader gets sem\n");
    if (readcount == 0)
    {
        sem_wait(&db);
    }
    readcount++;
    sem_post(&rc);
    printf("Reader reads %d and releases\n",*buffer);
    sem_wait(&rc);
    readcount--;
    if (readcount == 0)
    {
        sem_post(&db);
    }
    sem_post(&rc);

}

