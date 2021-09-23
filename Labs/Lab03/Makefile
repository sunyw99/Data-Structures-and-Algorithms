CC = g++
MAINSRCS = 
OTHSRCS =
HEADERS = 
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = main
MEMCHECKARGS = 

CFLAGS = -g -Wall -O2

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all memcheck clean
