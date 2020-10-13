///////////////////////////////////////////////////////////////////////////////
//
// Title:		537ps
// Filename:	queue.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "queue.h"

 /**
 * 
 * Constructor method for Queue
 * 
 * */
Queue *CreateStringQueue(int size){

    Queue *newQ = malloc(sizeof(Queue));
    if(newQ == NULL){
        fprintf(stderr,"Error: Bad Malloc");
        exit(-1);
    }
    newQ->size = size;
    newQ->currentSize = 0;
    newQ->stringArray = malloc(sizeof(char*) * size);
    if(newQ->stringArray == NULL){
        fprintf(stderr, "Error: Bad Malloc");
        exit(-1);
    }


    initQueueStats(&(newQ->statistics));
    sem_init( &(newQ->mutex), 0, 1);
    sem_init( &(newQ->empty), 0, size);
    sem_init( &(newQ->fill), 0, 0);
    return newQ;
}

 /**
 * 
 * Enqueue method for Queue
 * 
 * */
void EnqueueString(Queue *q, char *string){
   
    double elapsed;
    clock_t end;
    clock_t start = clock();
    if(start == ((clock_t) -1) ){
        fprintf(stderr,"%s\n", "ERROR: clock returned error value");
    }

    sem_wait(&(q->empty)); // empty meaning is this queue have an empty spot to put a string, semaphore starts at value that is max allowed in buffer
    sem_wait(&(q->mutex)); //lock only around atomic neccessary bits

    int index = q->indexToInsert;
    q->stringArray[index] = string;
  
    index = (index + 1) % q->size;
    q->indexToInsert = index;
    q->currentSize += 1;
    end = clock();
    if(end == ((clock_t) -1) ){
        fprintf(stderr,"%s\n", "ERROR: clock returned error value");
    }
    
    elapsed = (double) (end - start)/ CLOCKS_PER_SEC ;
    q->statistics.enqueueTime += elapsed;
    q->statistics.enqueueCount++;
    sem_post(&(q->mutex)); //unlock
    sem_post(&(q->fill)); // saying that there is something in the queue, so DequeueString won't be blocked if fill is 0
}

 /**
 * 
 * Dequeue method for Queue
 * 
 * */
char *DequeueString(Queue *q){
    char *toReturn;

    double elapsed;
    clock_t end;
    clock_t start = clock();
    if(start == ((clock_t) -1) ){
        fprintf(stderr,"%s\n", "ERROR: clock returned error value");
    }
    
    sem_wait(&(q->fill)); //checking if there is anything in queue, are any buffers full
    sem_wait(&(q->mutex)); //lock only around atomic neccessary bits

    int index = q->indexToRemove;
    toReturn = q->stringArray[index];
    index = (index + 1) % q->size;
    q->indexToRemove = index;
    q->currentSize -= 1;
    end = clock();
    if(end == ((clock_t) -1) ){
        fprintf(stderr, "%s\n", "ERROR: clock returned error value");
    }
    elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    q->statistics.dequeueTime += elapsed;
    q->statistics.dequeueCount++;

    sem_post(&(q->mutex)); //unlock
    sem_post(&(q->empty)); //incrementing empty means another string can be added to buffer

     return toReturn;
}

 /**
 * 
 * Printer method for Queue Stats
 * 
 * */
void PrintQueueStats( Queue *q){
    printQueueStats(&(q->statistics));
}