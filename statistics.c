 #include "statistics.h"
 
 void initQueueStats(QueueStats *s){
        s->enqueueCount = 0;
        s->dequeueCount = 0;
        s->enqueueTime = 0;
        s->dequeueTime = 0;
    }

 void printQueueStats(QueueStats *s){
        printf("%s %i ", "Enqueue Count: ", s->enqueueCount );
        printf("%s %i ", "Dequeue Count: ", s->dequeueCount );
        printf("%s %d ", "Enqueue Time: ", s->enqueueTime );
        printf("%s %d ", "Dequeue Time: \n", s->dequeueTime );
    }