CC=g++
CFLAGS=-Wall -g --std=c++11
SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:.cpp=.o)

optimized: CFLAGS += -Ofast -march=native -mtune=native
optimized: sigmod16

debug: CFLAGS += -DDEBUG -g
debug: sigmod16

sigmod16: $(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

.cpp.o:
	    $(CC) $(CFLAGS) -c $<

clean:
	    rm -f sigmod16 $(OBJS)

.PHONY: all clean
