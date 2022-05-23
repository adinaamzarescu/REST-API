CC=gcc
CFLAGS=-Wall -g
OBJECTS=client.o helpers.o requests.o buffer.o parson.o client_functions.o commands.o

build: client

client: $(OBJECTS)
	$(CC) $(CFLAGS) -o client $(OBJECTS)

client.o: ./clientdir/client.c ./clientdir/client.h
	$(CC) $(CFLAGS) -c ./clientdir/client.c

client_functions.o: ./clientdir/client_functions.c
	$(CC) $(CFLAGS) -c ./clientdir/client_functions.c

commands.o: ./clientdir/commands.c
	$(CC) $(CFLAGS) -c ./clientdir/commands.c

helpers.o: ./helpers/helpers.c ./helpers/helpers.h
	$(CC) $(CFLAGS) -c ./helpers/helpers.c

requests.o: ./requests/requests.c ./requests/requests.h
	$(CC) $(CFLAGS) -c ./requests/requests.c

buffer.o: ./buffer/buffer.c ./buffer/buffer.h
	$(CC) $(CFLAGS) -c ./buffer/buffer.c

parson.o: ./parson/parson.c ./parson/parson.h
	$(CC) $(CFLAGS) -c ./parson/parson.c

clean:
	rm client $(OBJECTS)
