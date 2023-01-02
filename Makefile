all: generate compile test clean

generate:
	./tools/generate_puzzle.sh

compile:
	./tools/compile.sh

test:
	./tools/test.sh

clean:
	./tools/clean.sh
