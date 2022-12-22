DAY=1
LIB=

SRC=main.c
BIN=day_$(DAY)
FLAGS=-W -Wall -g -ggdb
CC=gcc
PUZZLE=puzzle.sh
FORMAT=clang-format
FOO=/tmp/foo.h

all: sample.h puzzle.h $(BIN)

$(BIN): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(BIN) $(LIB)

sample.h: sample.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

puzzle.h: puzzle.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

clean:
	rm sample.h
	rm puzzle.h
	rm $(BIN)

.PHONY: sample puzzle
