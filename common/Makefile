SRC+=main.c
BIN=aoc
FLAGS=-W -Wall -g -ggdb
DEBUG=-g -ggdb
OPTIM=-O3
CC=gcc
PUZZLE=puzzle.sh
FORMAT=clang-format
FOO=/tmp/foo.h

all: puzzle sample

puzzle: puzzle.h $(SRC)
	$(CC) $(FLAGS) -D PUZZLE $(OPTIM) $(SRC) -o $(BIN)_puzzle $(LIB)
	$(CC) $(FLAGS) -D PUZZLE $(DEBUG) $(SRC) -o $(BIN)_puzzle_dbg $(LIB)

sample: sample.h $(SRC)
	$(CC) $(FLAGS) -D SAMPLE $(OPTIM) $(SRC) -o $(BIN)_sample $(LIB)
	$(CC) $(FLAGS) -D SAMPLE $(DEBUG) $(SRC) -o $(BIN)_sample_dbg $(LIB)

sample.h: sample.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

puzzle.h: puzzle.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

clean:
	rm -f sample.h
	rm -f puzzle.h
	rm -f $(BIN)_puzzle
	rm -f $(BIN)_puzzle_dbg
	rm -f $(BIN)_sample
	rm -f $(BIN)_sample_dbg
