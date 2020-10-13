# Shared-Memory-Producer-Consumer-Program

The goal of this assignment is to get experience in writing a program that actually runs in parallel on Linux using threads (pthreads) and synchronization.

The program creates multiple queues which is used to process strings and passed onto the later step of the program. This allows the program to run and process lines from standard input, while making changes to the line as soon as they
get loaded to the buffer memory. In the end the memory is freed as they are printed out to standard output.

To compile the code: make 
To run the program with sample input: ./prodcom < sample.txt 


