CC = g++
COMOPT = -std=c++11 -g
AR = ar

INCLUDES = -I../thrid_party

OUTPUT = libtools.a
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all := $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(AR) -surv $@ $^

%.o: %.cpp
	$(CC) $(COMOPT) -o $@ -c $< $(INCLUDES)

clean:
	rm -f *.o
	rm -f $(OUTPUT)