CC		= g++
SRCS		= ctcp.cpp main.cpp
OUT		= socket_server
CFLAGS		= -g -Wall -std=c++11 -pthread -lrt -I./shmipc
LIBS		= 

all:
	rm -f $(OUT)
	$(CC) $(CFLAGS) -o $(OUT) $(SRCS) ./shmipc/shmipc.o $(LIBS)
clean:
	rm -f $(OUT)