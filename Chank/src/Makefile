#variable compilador
CC=g++
#optimizaciones
#CFLAGS=-DDEBUG -O3 #-D (pasar variables) -O[0,1,2,3](optimizacion)
CFLAGS=-g -DDEBUG -std=c++17 -fopenmp
LDLIBS=-lstdc++fs
INCLUDE=-I. -I./include
EXEC=Chank
OBJS=Chank.o Commands.o Node.o Terminal.o Tree.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(EXEC) $(LDLIBS)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm *.o	
	rm $(EXEC)