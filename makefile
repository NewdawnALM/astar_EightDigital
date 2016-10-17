CC = g++
COMOPT = -std=c++11

INCLUDEDIR = -I./tools

LIBDIR = -L./tools
LIBS = -ltools
LINK = $(LIBDIR) $(LIBS)

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

OUTPUT := game

all: $(OUTPUT)

game: $(OBJS)
	make -C tools
	$(CC) -o $@ $^ $(LINK)

%.o: %.cpp
	$(CC) -o $@ -c $< $(COMOPT) $(INCLUDEDIR)

clean:
	make clean -C tools
	rm -f $(OBJS)
	rm -f $(OUTPUT)
