LIB=

SRC=main.c
BIN=aoc # advent of code
FLAGS=-W -Wall -g -ggdb
CC=gcc
PUZZLE=puzzle.sh
FORMAT=clang-format
FOO=/tmp/foo.h

all: sample.h puzzle.h $(BIN)

$(BIN): $(SRC) sample.h puzzle.h
	$(CC) $(FLAGS) $(SRC) -o $(BIN) $(LIB)

sample.h: sample.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

puzzle.h: puzzle.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

clean:
	rm -f sample.h
	rm -f puzzle.h
	rm -f $(BIN)
