///////////////////////////////////////////////////////////////////////////////
//
// Title:		537ps
// Filename:	queue.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include "statistics.h"

typedef struct
{
    char **stringArray;
    int size;
    int indexToInsert;
    int indexToRemove;
    int currentSize;
    QueueStats statistics;
    sem_t mutex; //lock
    sem_t fill; // consumer will use sem_wait on this to make sure the queue has something in it
                //before attempting to consume a buffer, sem_post called by producer to let consumer know
                // there is something in the buffer
    sem_t empty; //producer will cause sem_wait on this to make sure queue has an open spot
                // so it dosen't overwrite memory, sem_post called by consumer to let producer know
                // that there is an empty buffer/index to have another item placed into it
} Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

#endif
