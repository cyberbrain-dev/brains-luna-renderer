build:
	gcc -Wall -std=c99 src/*.c -o bin/luna -lSDL2 -lm

run:
	./bin/luna

clear:
	rm bin/luna