#variable compilador
CC=g++
#optimizaciones
#CFLAGS=-DDEBUG -O3 #-D (pasar variables) -O[0,1,2,3](optimizacion)
CFLAGS=-g -DDEBUG -std=c++17 -fopenmp
LDLIBS=
INCLUDE=-I. -I./include
EXEC=Chank
OBJS=Chank.o Commands.o Node.o Terminal.o Tree.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDLIBS) $(OBJS) -o $(EXEC)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	#para cada fichero.o busca su equivalente .cpp // -c para no linkar //$< = %.cpp //  $@ = %.o

clean:
	rm *.o	
	rm $(EXEC)