CC		= g++
SRCS		= main.c
OUT		= example
CFLAGS		= -g -Wall -std=c++11 -pthread -lrt -I./shmipc -I./src
LIBS		= 

all:
	rm -f $(OUT)
#	$(CC) $(CFLAGS) -c client.cpp -o client.o $(LIBS)
	$(CC) $(CFLAGS) -o $(OUT) $(SRCS) ./src/client.o ./shmipc/shmipc.o $(LIBS)
clean:
	rm -f $(OUT)