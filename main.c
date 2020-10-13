///////////////////////////////////////////////////////////////////////////////
//
// Title:		537ps
// Filename:	main.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "queue.h"

#define BUFFER_SIZE 10000 // Max line size
#define QUEUE_SIZE 10     //For testing

/**
 * 
 * Driver class for program
 * 
 * */
int main()
{

    Queue **queues = malloc(sizeof(Queue *) * 3);
        if (queues)
    {
        printf("%s\n", "Error: Bad Malloc");
        exit(-1);
    }


    for (int i = 0; i < 3; i++)
    {
        queues[i] = CreateStringQueue(QUEUE_SIZE); //Dynamically allocating
    }

    void *p = queues;
    int temp;

    //Starting Threads
    pthread_t readerT, munch1T, munch2T, writeT;
    temp = pthread_create(&readerT, NULL, &reader, p);

    if (temp)
    {
        printf("%s\n", "Error: Bad System Call");
        exit(-1);
    }

    temp = pthread_create(&munch1T, NULL, &munch1, p);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }
    temp = pthread_create(&munch2T, NULL, &munch2, p);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }
    temp = pthread_create(&writeT, NULL, &writer, p);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }

    //Making sure threads end
    temp = pthread_join(readerT, NULL);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }
    temp = pthread_join(munch1T, NULL);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }
    temp = pthread_join(munch2T, NULL);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }
    temp = pthread_join(writeT, NULL);
    if (temp)
    {
        printf("%s\n", "Error: Bad  System Call");
        exit(-1);
    }

    for (int i = 0; i < 3; i++)
    {
        free(queues[i]); //Free
    }

    exit(0);
}

/**
 * 
 * Reader function that reads lines from STDIN and adds to queue
 * 
 * */
void *reader(void *p)
{
    Queue **queues = (Queue **)p;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *enqueLine;

    while ((read = getline(&line, &len, stdin)) != -1) //use sentinel value to signal EOF
    {

        // printf("Retrieved line of length %zu :\n", read);

        if (read > BUFFER_SIZE)
        {
            fprintf(stderr, "Error: Line too long\n");
            continue;
        }

        enqueLine = malloc(len); // Will free this in Writer
        if (enqueLine == NULL)
        {
            printf("%s\n", "Error: Bad Malloc");
            exit(-1);
        }

        strcpy(enqueLine, line);

        //pass the string to the queue
        EnqueueString(queues[0], enqueLine);
        // PrintQueueStats(q1);
    }
    // printf("Retrieved line of length %zu :\n", read);

    EnqueueString(queues[0], NULL); // Last Enqueue, add a NULL pointer to the Queue when you detect an EOF

    pthread_exit(NULL);
};

/**
 * 
 * Function that processes lines from queue and adds to next queue
 * 
 * */
void *munch1(void *p)
{

    Queue **queues = (Queue **)p;

    char *string = DequeueString(queues[0]);
    int first = 0;

    while (string != NULL)
    {

        if (!first)
        {
            first++;
        }
        else
        {
            string = DequeueString(queues[0]);
        }

        if (string)
        {

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
            EnqueueString(queues[1], string);
        }
    }

    EnqueueString(queues[1], NULL);

    pthread_exit(NULL);
}

/**
 * 
 * Function that processes lines from queue and adds to next queue
 * 
 * */
void *munch2(void *p)
{

    Queue **queues = (Queue **)p;
    char *string = DequeueString(queues[1]);

    int first = 0;
    while (string != NULL)
    {
        if (!first)
        {
            first++;
        }
        else
        {
            string = DequeueString(queues[1]);
        }

        if (string)
        {

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
            EnqueueString(queues[2], string);
        }
    }

    EnqueueString(queues[2], NULL);
    pthread_exit(NULL);
}

/**
 * 
 * Function that prints out lines from last queue to Writer
 * 
 * */
void *writer(void *p)
{

    Queue **queues = (Queue **)p;

    char *string = DequeueString(queues[2]);
    int first = 0;
    int totalString = 0;
    while (string != NULL)
    {

        if (!first)
        {
            first++;
        }
        else
        {
            string = DequeueString(queues[2]);
        }

        if (string)
        {
            fprintf(stdout, "%s", string);
            totalString++;
            free(string);
        }
    }

    fprintf(stdout, "\n  Total strings processeded : %i\n", totalString);

    for (int i = 0; i < 3; i++)
    {
        PrintQueueStats(queues[i]);
    }

    // printf("%s result:%s \n", "Ending writer Thread", string);
    pthread_exit(NULL);
}