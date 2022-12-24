SRC+=main.c
BIN=aoc
FLAGS=-W -Wall -g -ggdb
DEBUG=-g -ggdb
OPTIM=-O3
CC=gcc
PUZZLE=puzzle.sh
FORMAT=clang-format
FOO=/tmp/foo.h

all: sample.h puzzle.h $(BIN)

$(BIN): $(SRC) sample.h puzzle.h
	$(CC) $(FLAGS) $(OPTIM) $(SRC) -o $(BIN) $(LIB)
	$(CC) $(FLAGS) $(DEBUG) $(SRC) -o $(BIN)_dbg $(LIB)

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
	rm -f $(BIN)_dbg
