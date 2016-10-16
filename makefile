CC = g++
COMOPT = -std=c++11

output := game

all: $(output)

game: main.o libgame.a
	$(CC) -o $@ $^

libgame.a: game.o chess.o
	ar -surv $@ $^

%.o: %.cpp
	$(CC) -o $@ -c $< $(COMOPT)

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(output)
