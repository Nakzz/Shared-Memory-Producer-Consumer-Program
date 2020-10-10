#include "main.h";

int main()
{

    reader();
}

char ** reader()
{
            printf("Before open file.\n");


    char filename[60];
    strcpy(filename, "/home/aj/classes/537/Shared-Memory-Producer-Consumer-Program/sample.txt");


    FILE *file = fopen(filename, 'r');

            printf("After open file.\n");


    char ch;

    do{
        ch = fgetc(file);

        fprintf("%c", ch);

    }while(ch != EOF);

    return NULL;
}