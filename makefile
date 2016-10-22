CC = g++
COMOPT = -std=c++11

INCLUDEDIR = -I./tools

LIBDIR = -L./tools
LIBS = -ltools
LINK = $(LIBDIR) $(LIBS)

# OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJS += chess.o astar.o state.o

OUTPUT += game rand_init

all: $(OUTPUT)

game: $(OBJS) main.o
	make -C tools
	$(CC) -o $@ $^ $(LINK)

rand_init: $(OBJS) rand_init.o
	make -C tools
	$(CC) -o $@ $^ $(LINK)

%.o: %.cpp
	$(CC) -o $@ -c $< $(COMOPT) $(INCLUDEDIR)

clean:
	make clean -C tools
	rm -f *.o
	rm -f $(OUTPUT)
