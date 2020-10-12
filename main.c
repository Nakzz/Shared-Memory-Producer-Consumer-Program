#include "main.h"
#include "queue.h"

#define BUFFER_SIZE 10000
#define QUEUE_SIZE 10



int main()
{
    
     Queue **queues = malloc(sizeof(Queue*) * 3);

     for(int i=0; i<3; i++){
         queues[i] = CreateStringQueue(QUEUE_SIZE);
     }
    
    void *p = queues;

    pthread_t readerT, munch1T, munch2T, writeT;

    //init all the queues
    // q2 = CreateStringQueue(QUEUE_SIZE);
    // q3 = CreateStringQueue(QUEUE_SIZE);

    pthread_create(&readerT, NULL, &reader, p);
    pthread_create(&munch1T, NULL, &munch1, p);
    pthread_create(&munch2T, NULL, &munch2, p);
    pthread_create(&writeT, NULL, &writer, p);

    // pthread_join(readerT, NULL);
    pthread_join(munch1T, NULL);
    pthread_join(munch2T, NULL);
    pthread_join(writeT, NULL);

    // free
}

void *reader(void *p)
{
    Queue **queues = (Queue **) p;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *enqueLine;

    while ((read = getline(&line, &len, stdin)) != -1) //use sentinel value to signal EOF, so add a NULL pointer to the Queue when you detect an EOF
    {

        // printf("Retrieved line of length %zu :\n", read);

        if (read > BUFFER_SIZE)
        {
            fprintf(stderr, "Error: Line too long\n");
            continue;
        }

       enqueLine = malloc(len);
       
       strcpy(enqueLine, line);


        //pass the string to the queue
        EnqueueString(queues[0], enqueLine);
        // PrintQueueStats(q1);
    }
        EnqueueString(queues[0], NULL);     // Last Enqueue
    
    pthread_exit(NULL);
};

void *munch1(void *p)
{

    Queue ** queues = (Queue **) p;
    
    char *string= DequeueString(queues[0]);
    int first = 0;

    while(string != NULL){

        if (!first){
             first++;
        }else{
            string  = DequeueString(queues[0]);
        }

    //for testing
    // char *string = malloc(sizeof(char) * 20);
    // strcpy(string, "Hellow neiwFni cmnwieuc \0");
if(string){

    int index = 0;
    while (*(string + index) != '\0')
    {
        // printf("char: %c\n", string[index]);

        if (string[index] == ' ')
        {
            // printf("Found space: %c\n", string[index]);

            string[index] = '*';
        }
        index++;
    }
}
    EnqueueString(queues[1], string);
}
    pthread_exit(NULL);
}

void *munch2(void * p)
{

    Queue ** queues = (Queue **) p;
    char *string = DequeueString(queues[1]);

    int first = 0;
    while(string != NULL){
        if(!first){
             first++;
        }else{
             string  = DequeueString(queues[1]);
        }

if(string){

        int index = 0;
        while (*(string + index) != '\0')
        {
            // printf("char: %c\n", string[index]);

            if (string[index] >= 'a' && string[index] <= 'z')
            {
                // printf("Found lowercase: %c\n", string[index]);

                string[index] = string[index] - 32;
            }

            index++;
        }
    }
            EnqueueString(queues[2], string);
        }
    //  EnqueueString(queues[2], NULL);   
        pthread_exit(NULL);
}
    


void *writer(void * p){

      Queue ** queues = (Queue **) p;


    // char *string = DequeueString(q3);

    //for testing
    // char *string = malloc(sizeof(char) * 30);
    // strcpy(string, "Hellow*neiwfni*cmnwieuc*\0");

    char *string = DequeueString(queues[2]);
    int first = 0;
    while(string != NULL){
        if(!first){
             first++;
        }else{
             string  = DequeueString(queues[2]);
        }
    fprintf(stdout, "  FINAL RESULT: %s", string);
    }


    printf("%s result:%s \n", "Ending writer Thread", string);
        pthread_exit(NULL);

}