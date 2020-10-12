#include "queue.h"

Queue *CreateStringQueue(int size){

    Queue *newQ = malloc(sizeof(Queue));
    //printf("%s %p\n", "Initalized Queue struct Addr: ", newQ);

    if(newQ == NULL){
        printf("Error: Bad Malloc");
        exit(-1);
    }
    newQ->size = size;
    newQ->currentSize = 0;
    newQ->stringArray = malloc(sizeof(char*) * size);
    initQueueStats(&(newQ->statistics));
    sem_init( &(newQ->mutex), 0, 1);
    sem_init( &(newQ->empty), 0, size);
    sem_init( &(newQ->fill), 0, 0);
    return newQ;
}

void EnqueueString(Queue *q, char *string){
    //printf("%s %p\n", "Enqueue struct Addr: ", q);
    double start, end, elapsed;
    struct timeval timecheck;

    gettimeofday(&timecheck, NULL);
    start = (double)timecheck.tv_sec * 1000.0 + (double)timecheck.tv_usec / 1000.0;

    int *semVal = malloc(sizeof(int));
    sem_getvalue(&(q->empty), semVal);
    //printf("%s", "empty value before wait: ");
    //printf("%i\n", *semVal);
    sem_wait(&(q->empty));
    sem_getvalue(&(q->empty), semVal);
    //printf("%s", "empty value after wait: ");
   //printf("%i\n", *semVal);
    sem_wait(&(q->mutex));

    int index = q->indexToInsert;
    q->stringArray[index] = string;
    //printf("%s %i\n", "Enqueue Index: ", index );
    //printf("%s %s\n", "Enqueued String: ",  (q->stringArray[index]));
    index = (index + 1) % q->size;
    q->indexToInsert = index;
    q->currentSize += 1;

    gettimeofday(&timecheck, NULL);
    end = (double)timecheck.tv_sec * 1000.0 + (double)timecheck.tv_usec / 1000.0;
    elapsed = end - start;
    elapsed = elapsed / 1000.0;
    q->statistics.enqueueTime += elapsed;
    q->statistics.enqueueCount++;
    sem_post(&(q->mutex));
    sem_post(&(q->fill));
}

char *DequeueString(Queue *q){
    //printf("%s %p\n", "Dequeue struct Addr: ", q);
    char *toReturn;
    double start, end, elapsed;
    struct timeval timecheck;

    gettimeofday(&timecheck, NULL);
    start = (double)timecheck.tv_sec * 1000.0 + (double)timecheck.tv_usec / 1000.0;
    int *semVal = malloc(sizeof(int));
    sem_getvalue(&(q->fill), semVal);
    //printf("%s", "fill value before wait: ");
    //printf("%i\n", *semVal);
    sem_wait(&(q->fill));
    sem_getvalue(&(q->fill), semVal);
    //printf("%s", "fill value after wait: ");
    //printf("%i\n", *semVal);
    sem_wait(&(q->mutex));

    int index = q->indexToRemove;
    toReturn = q->stringArray[index];
    //printf("%s %i\n", "Dequeue Index: ", index );
    //printf("%s %s\n", "Dequeued String: ", toReturn);
    index = (index + 1) % q->size;
    q->indexToRemove = index;
    q->currentSize -= 1;

    gettimeofday(&timecheck, NULL);
    end = (double)timecheck.tv_sec * 1000.0 + (double)timecheck.tv_usec / 1000.0;
    elapsed = end - start;
    elapsed = elapsed / 1000.0;
    q->statistics.dequeueTime += elapsed;
    q->statistics.dequeueCount++;

    sem_post(&(q->mutex));
    sem_post(&(q->empty));

     return toReturn;
}

void PrintQueueStats( Queue *q){
    printQueueStats(&(q->statistics));
}