DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic -std=c++20

CC=g++ $(OPTS) -c
LN=g++

OBJS = project1.o

runMe: $(OBJS)
	$(LN) -o runMe $(OBJS)

proj1.o: project1.cpp
	$(CC) project1.cpp

clean:
	/bin/rm -rf *~ $(OBJS) proj1
