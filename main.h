#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main();
void *reader(void * p);
void *munch1(void * p);
void *munch2(void * p);
void *writer(void * p);
int getSize(char *arr);
