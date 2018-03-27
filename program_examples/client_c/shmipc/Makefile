CC		= g++
SRCS		= shmipc.cpp main.cpp
OUT		= main
CFLAGS		= -g -lm -lrt -std=c++11
LIBS		= 

all:	shmipc.o
	rm -f $(OUT)
	$(CC) $(CFLAGS) -o $(OUT) main.cpp shmipc.o $(LIBS)
shmipc.o:	shmipc.cpp
	$(CC) $(CFLAGS) -c -o shmipc.o shmipc.cpp $(LIBS)
	
clean:
	rm -f $(OUT) *.o