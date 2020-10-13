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
    sem_t mutex;
    sem_t fill;
    sem_t empty;
} Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

#endif
