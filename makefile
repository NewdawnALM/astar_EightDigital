CC = g++
COMOPT = -std=c++11

INCLUDEDIR = -I./tools

LIBDIR = -L./tools
LIBS = -ltools
LINK = $(LIBDIR) $(LIBS)

OUTPUT := game

all: $(OUTPUT)

game: main.o
	make -C tools
	$(CC) -o $@ $^ $(LINK)

%.o: %.cpp
	$(CC) -o $@ -c $< $(COMOPT) $(INCLUDEDIR)

clean:
	rm -f *.o
	rm -f $(OUTPUT)
