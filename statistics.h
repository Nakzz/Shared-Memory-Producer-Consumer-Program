#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>

    typedef struct{
        int enqueueCount;
        int dequeueCount;
        double enqueueTime;
        double dequeueTime;
    }QueueStats;

    void initQueueStats(QueueStats *s);

    void printQueueStats(QueueStats *s);
#endif