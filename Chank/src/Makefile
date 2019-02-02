#variable compilador
CC=g++
#optimizaciones
#CFLAGS=-DDEBUG -O3 #-D (pasar variables) -O[0,1,2,3](optimizacion)
CFLAGS=-g -DDEBUG -std=c++17
LDLIBS=-lstdc++fs
INCLUDE=-I. -I./include
EXEC=ChankCLI
OBJS=Chank.o Commands.o Node.o Terminal.o Tree.o Disk.o DiskBlock.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(EXEC) $(LDLIBS)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm *.o	
	rm $(EXEC)
