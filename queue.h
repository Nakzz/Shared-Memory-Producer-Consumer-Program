#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include "statistics.h"

    typedef struct{
        char ** stringArray;
        int size;
        int indexToInsert;
        int indexToRemove;
        int currentSize;
        QueueStats statistics;
        sem_t mutex;
        sem_t fill;
        sem_t empty;
    }Queue;

    Queue *CreateStringQueue(int size);

    void EnqueueString(Queue *q, char *string);

    char * DequeueString(Queue *q);

    void PrintQueueStats(Queue *q);

#endif

