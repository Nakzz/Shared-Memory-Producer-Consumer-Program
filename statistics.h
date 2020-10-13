///////////////////////////////////////////////////////////////////////////////
//
// Title:		537ps
// Filename:	statistics.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>

typedef struct
{
    int enqueueCount;
    int dequeueCount;
    double enqueueTime;
    double dequeueTime;
} QueueStats;

void initQueueStats(QueueStats *s);

void printQueueStats(QueueStats *s);
#endif