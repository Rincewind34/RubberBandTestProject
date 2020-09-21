CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++14 -Wno-unused-variable
SRCS = $(shell find . -type f -name '*.cpp')
HEDS = $(shell find . -type f -name '*.hpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = rubberbandtest

LIBS += -L../rubberband-1.9.0/lib -lrubberband

all: $(PROG)

.PHONY: clean all

$(PROG): .depend $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) $(LIBS)

clean: 
	rm -f $(PROG)
	rm -f $(OBJS)
	rm -f .depend
	rm -f test_out.wav

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# Compute header file dependencies 
.depend : $(SRCS)
	$(CC) $(CPPFLAGS) -MM $^ > .depend

# Respect header file dependencies
include .depend
