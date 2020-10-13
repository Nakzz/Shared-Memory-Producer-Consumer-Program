///////////////////////////////////////////////////////////////////////////////
//
// Title:		537ps
// Filename:	statistics.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "statistics.h"

/**
 * 
 * Constructor method for Statistics
 * 
 * */
void initQueueStats(QueueStats *s)
{
    s->enqueueCount = 0;
    s->dequeueCount = 0;
    s->enqueueTime = 0;
    s->dequeueTime = 0;
}

/**
 * 
 * Printer method for Statistics
 * 
 * */
void printQueueStats(QueueStats *s)
{
    printf("%s %i ", "Enqueue Count: ", s->enqueueCount);
    printf("%s %i ", "Dequeue Count: ", s->dequeueCount);
    printf("%s %f ", "Enqueue Time: ", s->enqueueTime);
    printf("%s %f \n", "Dequeue Time: ", s->dequeueTime);
}