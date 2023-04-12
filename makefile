OBJS	= memsim.o
SOURCE	= memsim.cpp 
HEADER	= dataStructures.hpp
OUT	= memsim
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

memsim.o: memsim.cpp
	$(CC) $(FLAGS) memsim.cpp 

clean:
	rm -f $(OBJS) $(OUT)
