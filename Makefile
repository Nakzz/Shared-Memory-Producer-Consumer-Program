CC = gcc
CFLAGS = -Wall -pedantic -ggdb -Wextra -pthread
OBJECTS = main.o queue.o statistics.o 

prodcom: $(OBJECTS) 
	$(CC) $(CFLAGS) -o prodcom ${OBJECTS}

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h statistics.h
	$(CC) $(CFLAGS) -c queue.c 

statistics.o: statistics.c statistics.h
	$(CC) $(CFLAGS) -c statistics.c 

clean:
	rm -f $(OBJECTS) prodcom
