###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -O3 -Wall -std=c++11		# compilation flags: -g for debugging. Change to -O3 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = prog			# target executables (output)
SRCS =  buffer.cpp main.cpp     # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.
DEPS = $(SRCS:.cpp=.d)

all : $(PROG)

prog:  buffer.o main.o
	$(CC) -o prog buffer.o main.o $(LDFLAGS) $(LIB)


.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
# cleanup
clean:
	rm -f *.o $(PROG) 

# DO NOT DELETE
