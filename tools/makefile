CC = g++
COMOPT = -std=c++11
AR = ar

OUTPUT = libtools.a
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all := $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(AR) -surv $@ $^

%.o: %.cpp
	$(CC) $(COMOPT) -o $@ -c $<

clean:
	rm -f *.o
	rm -f $(OUTPUT)