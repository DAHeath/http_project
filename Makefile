CC = g++
DEBUG_FLAGS = -g -O0 -DDEBUG -std=c++11
CFLAGS = $(DEBUG_FLAGS) -Wall
RM = rm -f

all: web_client

web_client: web_client.o get_request.o my_lib.o socket.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	$(RM) *.o web_server web_client
