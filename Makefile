all: generate compile test clean

generate:
	./tests/generate_puzzle.sh

compile:
	./tests/compile.sh

test:
	./tests/test.sh

clean:
	./tests/clean.sh
