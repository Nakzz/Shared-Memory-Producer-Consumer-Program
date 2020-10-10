CC = gcc
CFLAGS = -Wall -pedantic -ggdb -Wextra -pthread
OBJECTS = main.o

prodcom: $(OBJECTS)
	$(CC) $(CFLAGS) -o prodcom ${OBJECTS}

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJECTS) prodcom
