DAY=2
LIB=

SRC=main.c
BIN=day_$(DAY)
FLAGS=-W -Wall -g -ggdb
CC=gcc
PUZZLE=puzzle.sh
FORMAT=clang-format
FOO=/tmp/foo.h

all: sample_part1.h sample_part2.h puzzle.h $(BIN)

$(BIN): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(BIN) $(LIB)

sample_part2.h: sample_part2.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

sample_part1.h: sample_part1.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

puzzle.h: puzzle.txt $(PUZZLE)
	./$(PUZZLE) $< > $(FOO)
	$(FORMAT) $(FOO) > $@

clean:
	rm sample_part1.h
	rm sample_part2.h
	rm puzzle.h
	rm $(BIN)

.PHONY: sample puzzle
